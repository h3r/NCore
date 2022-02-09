#include "ncpch.h"
#include "vertex_array.h"
#include "render/renderer.h"
#include "platform/opengl/opengl_vertex_array.h"

namespace NC {

	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI())
		{
			case RendererAPI::OpenGL: return new OpenGLVertexArray();
			case RendererAPI::None:
			default: nc_fatal("Unknown Renderer API"); return nullptr;
		}
	}

}

