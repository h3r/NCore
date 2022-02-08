#include "ncpch.h"
#include "buffer.h"
#include "renderer.h"
#include "platform/opengl/buffer.h"

namespace NC {
  VertexBuffer* VertexBuffer::Create(float* vertices, size_t size) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		nc_fatal("nullptr"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		default: nc_fatal("Unknown Renderer API"); return nullptr;
		}
  }
  
  IndexBuffer* IndexBuffer::Create(uint32_t* indices, size_t size) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		nc_fatal("nullptr"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
		default: nc_fatal("Unknown Renderer API"); return nullptr;
		}
  }
}
