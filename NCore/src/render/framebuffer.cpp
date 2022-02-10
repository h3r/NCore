#include "ncpch.h"
#include "render/renderer.h"
#include "render/framebuffer.h"
#include "platform/opengl/opengl_framebuffer.h"

namespace NC {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:    nc_fatal("RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
		default: nc_fatal("Unknown RendererAPI!"); return nullptr;
		}

	}

}
