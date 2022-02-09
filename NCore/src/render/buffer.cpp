#include "ncpch.h"
#include "buffer.h"
#include "renderer.h"
#include "platform/opengl/buffer.h"

namespace NC {
  VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		nc_fatal("nullptr"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		default: nc_fatal("Unknown Renderer API"); return nullptr;
		}
  }
  
  IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		nc_fatal("nullptr"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
		default: nc_fatal("Unknown Renderer API"); return nullptr;
		}
  }
}
