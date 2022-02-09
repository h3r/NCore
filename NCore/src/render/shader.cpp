#include "ncpch.h"
#include "shader.h"
#include "platform/opengl/opengl_shader.h"
#include <glad/glad.h>

namespace NC {
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		return CreateRef<OpenGLShader>(filepath);
		/*switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:    nc_fatal("RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(filepath);
			default:nc_fatal("Unknown RendererAPI!");return nullptr;
		}*/
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);

		/*switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:    nc_fatal("RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
			default:
				nc_fatal("Unknown RendererAPI!");
				return nullptr;
		}*/
	}
}
