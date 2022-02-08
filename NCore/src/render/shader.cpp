#include "ncpch.h"
#include "shader.h"
#include "platform/opengl/opengl_shader.h"
#include <glad/glad.h>

namespace NC {
	Ref<CShader> CShader::Create(const std::string& filepath)
	{
		return CreateRef<COpenGLShader>(filepath);
		/*switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:    nc_fatal("RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<COpenGLShader>(filepath);
			default:nc_fatal("Unknown RendererAPI!");return nullptr;
		}*/
	}

	Ref<CShader> CShader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		return CreateRef<COpenGLShader>(name, vertexSrc, fragmentSrc);

		/*switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:    nc_fatal("RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<COpenGLShader>(name, vertexSrc, fragmentSrc);
			default:
				nc_fatal("Unknown RendererAPI!");
				return nullptr;
		}*/
	}
}
