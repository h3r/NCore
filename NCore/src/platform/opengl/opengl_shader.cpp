#include "ncpch.h"
#include "opengl_shader.h"
#include <shaderc/shaderc.hpp>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>

namespace NC
{
		namespace Utils {
			static GLenum ShaderTypeFromString(const std::string& type) {
				if (type == "vertex") return GL_VERTEX_SHADER;
				if (type == "fragment" || type == "pixel")return GL_FRAGMENT_SHADER;
				nc_fatal("Unknown shader type!");
				return 0;
			}

			static shaderc_shader_kind GLShaderStageToShaderC(GLenum stage) {
				switch (stage) {
					case GL_VERTEX_SHADER:   return shaderc_glsl_vertex_shader;
					case GL_FRAGMENT_SHADER: return shaderc_glsl_fragment_shader;
					default:
						nc_fatal("Unknown shader stage!");
						return (shaderc_shader_kind)0;
				}
			}

			static const char* GLShaderStageToString(GLenum stage) {
				switch (stage) {
					case GL_VERTEX_SHADER:   return "GL_VERTEX_SHADER";
					case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
					default:
						nc_fatal("Unknown shader stage!");
						return nullptr;
				}
			}

			static const char* GetCacheDirectory() {
				// TODO: make sure the assets directory is valid
				return "assets/cache/shader/opengl";
			}

			static void CreateCacheDirectoryIfNeeded() {
				std::string cacheDirectory = GetCacheDirectory();
				if (!std::filesystem::exists(cacheDirectory))
					std::filesystem::create_directories(cacheDirectory);
			}

			static const char* GLShaderStageCachedOpenGLFileExtension(uint32_t stage)
			{
				switch (stage) {
					case GL_VERTEX_SHADER:    return ".cached_opengl.vert";
					case GL_FRAGMENT_SHADER:  return ".cached_opengl.frag";
					default:
						nc_fatal("Unknown shader stage!");
						return "";
				}
			}

			static const char* GLShaderStageCachedVulkanFileExtension(uint32_t stage) {
				switch (stage) {
					case GL_VERTEX_SHADER:    return ".cached_vulkan.vert";
					case GL_FRAGMENT_SHADER:  return ".cached_vulkan.frag";
					default: 
						nc_fatal("Unknown shader stage!");
						return "";
				}
			}
		}


		COpenGLShader::COpenGLShader(const std::string& _filepath)
			: m_filepath(_filepath)
		{
			Utils::CreateCacheDirectoryIfNeeded();
			std::string source = ReadFile(_filepath);
			auto shader_sources = PreProcess(source);

			{
				CompileOrGetVulkanBinaries(shader_sources);
				CompileOrGetOpenGLBinaries();
				CreateProgram();
			}

			//extract name from filepath
			fs::path path(_filepath);
			m_name = path.filename().string();
		}

		COpenGLShader::COpenGLShader(const std::string& _name, const std::string& _vertex_source, const std::string& _fragment_source)
			: m_name(_name)
		{
			Utils::CreateCacheDirectoryIfNeeded();
			std::unordered_map<GLenum, std::string> sources;
			sources[GL_VERTEX_SHADER] = _vertex_source;
			sources[GL_FRAGMENT_SHADER] = _fragment_source;

			CompileOrGetVulkanBinaries(sources);
			CompileOrGetOpenGLBinaries();
			CreateProgram();
		}

		COpenGLShader::~COpenGLShader() {
			glDeleteProgram(m_handle);
		}

		std::string COpenGLShader::ReadFile(const std::string& filepath) {
			std::string result;
			std::ifstream in(filepath, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII
			if (!in) {nc_fatal("Could not open file '{0}'", filepath);}
			else
			{
				in.seekg(0, std::ios::end);
				size_t size = in.tellg();
				if (size == -1) {nc_fatal("Could not read from file '{0}'", filepath);}
				else 
				{
					result.resize(size);
					in.seekg(0, std::ios::beg);
					in.read(&result[0], size);
				}
			}

			return result;
		}


		std::unordered_map<GLenum, std::string> COpenGLShader::PreProcess(const std::string& _source)
		{
			std::unordered_map<GLenum, std::string> shaderSources;

			const char* typeToken = "#type";
			size_t typeTokenLength = strlen(typeToken);
			size_t pos = _source.find(typeToken, 0);

			while (pos != std::string::npos)
			{
				size_t eol = _source.find_first_of("\r\n", pos);
				nc_assert(eol != std::string::npos, "Syntax error");
				size_t begin = pos + typeTokenLength + 1;
				std::string type = _source.substr(begin, eol - begin);

				size_t nextLinePos = _source.find_first_of("\r\n", pos);
				nc_assert(eol != std::string::npos, "Syntax error");
				pos = _source.find(typeToken, nextLinePos);

				shaderSources[Utils::ShaderTypeFromString(type)] = (pos == std::string::npos)
					? _source.substr(nextLinePos, nextLinePos)
					: _source.substr(nextLinePos, pos - nextLinePos);
			}

			return shaderSources;
		}

		void COpenGLShader::CreateProgram() {
			GLuint program = glCreateProgram();

			std::vector<GLuint> shaderIDs;
			for (auto&& [stage, spirv] : m_opengl_spirv)
			{
				GLuint shaderID = shaderIDs.emplace_back(glCreateShader(stage));
				glShaderBinary(1, &shaderID, GL_SHADER_BINARY_FORMAT_SPIR_V, spirv.data(), spirv.size() * sizeof(uint32_t));
				glSpecializeShader(shaderID, "main", 0, nullptr, nullptr);
				glAttachShader(program, shaderID);
			}

			glLinkProgram(program);

			GLint isLinked;
			glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
			if (isLinked == GL_FALSE) {
				GLint maxLength;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());
				nc_fatal("Shader linking failed ({0}):\n{1}", m_filepath, infoLog.data());

				glDeleteProgram(program);
				for (auto id : shaderIDs)
					glDeleteShader(id);
			}

			for (auto id : shaderIDs) {
				glDetachShader(program, id);
				glDeleteShader(id);
			}

			m_handle = program;
		}


		void COpenGLShader::CompileOrGetVulkanBinaries(const std::unordered_map<uint32_t, std::string>& _shader_sources)
		{
			GLuint program = glCreateProgram();

			shaderc::Compiler compiler;
			shaderc::CompileOptions options;
			options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
			//options.AddMacroDefinition("OPENGL");
			const static bool optimize = true;
			if (optimize) 
				options.SetOptimizationLevel(shaderc_optimization_level_performance);

			fs::path cacheDir = Utils::GetCacheDirectory();

			auto& shaderData = m_vulkan_spirv;
			shaderData.clear();
			for (auto&& [stage, source] : _shader_sources)
			{
				fs::path cachedPath = cacheDir / (m_name + Utils::GLShaderStageCachedVulkanFileExtension(stage));

				std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
				if (in.is_open())
				{
					in.seekg(0, std::ios::end);
					auto size = in.tellg();
					in.seekg(0, std::ios::beg);

					auto& data = shaderData[stage];
					data.resize(size / sizeof(uint32_t));
					in.read((char*)data.data(), size);
				}
				else
				{
					shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, Utils::GLShaderStageToShaderC(stage), m_filepath.c_str(), options);
					if (module.GetCompilationStatus() != shaderc_compilation_status_success)
						nc_fatal(module.GetErrorMessage());

					shaderData[stage] = std::vector<uint32_t>(module.cbegin(),module.cend());

					std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
					if (out.is_open()) {
						auto& data = shaderData[stage];
						out.write((char*)data.data(), data.size() * sizeof(uint32_t));
						out.flush();
						out.close();
					}

				}
			}

			for (auto&& [stage, data] : shaderData)
				Reflect(stage, data);

		}


		void COpenGLShader::CompileOrGetOpenGLBinaries()
		{
			auto& shaderData = m_opengl_spirv;

			shaderc::Compiler compiler;
			shaderc::CompileOptions options;
			options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);
			const bool optimize = false;
			if (optimize)
				options.SetOptimizationLevel(shaderc_optimization_level_performance);

			std::filesystem::path cacheDirectory = Utils::GetCacheDirectory();

			shaderData.clear();
			m_opengl_sourcecode.clear();
			for (auto&& [stage, spirv] : m_vulkan_spirv)
			{
				std::filesystem::path cachedPath = cacheDirectory / (m_name + Utils::GLShaderStageCachedOpenGLFileExtension(stage));

				std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
				if (in.is_open())
				{
					in.seekg(0, std::ios::end);
					auto size = in.tellg();
					in.seekg(0, std::ios::beg);

					auto& data = shaderData[stage];
					data.resize(size / sizeof(uint32_t));
					in.read((char*)data.data(), size);
				}
				else
				{
					spirv_cross::CompilerGLSL glslCompiler(spirv);
					m_opengl_sourcecode[stage] = glslCompiler.compile();
					auto& source = m_opengl_sourcecode[stage];

					shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, Utils::GLShaderStageToShaderC(stage), m_filepath.c_str());
					if (module.GetCompilationStatus() != shaderc_compilation_status_success)
						nc_fatal(module.GetErrorMessage());

					shaderData[stage] = std::vector<uint32_t>(module.cbegin(), module.cend());

					std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
					if (out.is_open())
					{
						auto& data = shaderData[stage];
						out.write((char*)data.data(), data.size() * sizeof(uint32_t));
						out.flush();
						out.close();
					}
				}
			}
		}

		void COpenGLShader::Reflect(GLenum stage, const std::vector<uint32_t>& _shaderData)
		{
			spirv_cross::Compiler compiler(_shaderData);
			spirv_cross::ShaderResources resources = compiler.get_shader_resources();

			log_trace("OpenGLShader::Reflect - {} {}", Utils::GLShaderStageToString(stage), m_filepath);
			log_trace("    {0} uniform buffers", resources.uniform_buffers.size());
			log_trace("    {0} resources", resources.sampled_images.size());
			log_trace("Uniform Buffers:");
			for (const auto& resource : resources.uniform_buffers)
			{
				const auto& buffer_type = compiler.get_type(resource.base_type_id);
				uint32_t buffer_size = compiler.get_declared_struct_size(buffer_type);
				uint32_t binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
				size_t member_count = buffer_type.member_types.size();

				log_trace("  {}", resource.name);
				log_trace("    Size = {}", buffer_size);
				log_trace("    Binding = {}", binding);
				log_trace("    Members = {}", member_count);
			}
		}

		void COpenGLShader::Bind() const {
			glUseProgram(m_handle);
		}

		void COpenGLShader::Unbind() const {
			glUseProgram(0);
		}

		void COpenGLShader::SetInt(   const std::string& name, int value) {              UploadUniformInt(name, value);    }
		void COpenGLShader::SetFloat( const std::string& name, float value) {            UploadUniformFloat(name, value);  }
		void COpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value) { UploadUniformFloat2(name, value); }
		void COpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value) { UploadUniformFloat3(name, value); }
		void COpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value) { UploadUniformFloat4(name, value); }
		void COpenGLShader::SetMat4(  const std::string& name, const glm::mat4& value) { UploadUniformMat4(name, value);   }
		void COpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count) { 
																																										 UploadUniformIntArray(name, values, count);
		}
		void COpenGLShader::UploadUniformInt(const std::string& name, int value) {
			GLint location = glGetUniformLocation(m_handle, name.c_str());
			glUniform1i(location, value);
		}

		void COpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count) {
			GLint location = glGetUniformLocation(m_handle, name.c_str());
			glUniform1iv(location, count, values);
		}

		void COpenGLShader::UploadUniformFloat(const std::string& name, float value) {
			GLint location = glGetUniformLocation(m_handle, name.c_str());
			glUniform1f(location, value);
		}

		void COpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value) {
			GLint location = glGetUniformLocation(m_handle, name.c_str());
			glUniform2f(location, value.x, value.y);
		}

		void COpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value) {
			GLint location = glGetUniformLocation(m_handle, name.c_str());
			glUniform3f(location, value.x, value.y, value.z);
		}

		void COpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value) {
			GLint location = glGetUniformLocation(m_handle, name.c_str());
			glUniform4f(location, value.x, value.y, value.z, value.w);
		}

		void COpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix) {
			GLint location = glGetUniformLocation(m_handle, name.c_str());
			glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
		}

		void COpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
		{
			GLint location = glGetUniformLocation(m_handle, name.c_str());
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
		}
	}
