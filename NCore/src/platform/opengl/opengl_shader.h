#pragma once
#include "render/shader.h"
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace NC {

	class NC_API COpenGLShader : public CShader
	{
	public:
		COpenGLShader(const std::string& filepath);
		COpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~COpenGLShader();

		virtual const std::string& GetName() const override { return m_name; }

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		//Sounds about resource related data -> move to resource
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& _source);
		void Reflect(GLenum stage, const std::vector<uint32_t>& shaderData);
		void CreateProgram();
		void CompileOrGetOpenGLBinaries();
		void CompileOrGetVulkanBinaries(const std::unordered_map<uint32_t, std::string>& _shader_sources);

	private:
		uint32_t m_handle;
		std::string m_name;
		std::string m_filepath;

		std::unordered_map<GLenum, std::vector<uint32_t>> m_vulkan_spirv;
		std::unordered_map<GLenum, std::vector<uint32_t>> m_opengl_spirv;

		std::unordered_map<GLenum, std::string> m_opengl_sourcecode;
	};
}
