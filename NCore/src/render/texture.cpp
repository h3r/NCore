#include "ncpch.h"
#include "texture.h"
#include "renderer.h"
#include "platform/opengl/opengl_texture.h"

namespace NC {

	Ref<Texture2D> Texture2D::Create(uint32_t _width, uint32_t _height) {
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:    nc_fatal("RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL:  return CreateRef<OpenGLTexture2D>(_width, _height);
			default: nc_fatal("Unknown RendererAPI!"); return nullptr;
		}
	}

	Ref<Texture2D> Texture2D::Create(const std::string& _path) {
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:    nc_fatal("RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL:  return CreateRef<OpenGLTexture2D>(_path);
			default: nc_fatal("Unknown RendererAPI!");return nullptr;
		}

	}

}
