#include "ncpch.h"
#include "opengl_vertex_array.h"
#include <glad/glad.h>

namespace NC {

	namespace {
		static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Boolean:	return GL_BOOL;
			case ShaderDataType::Mat3:	  return GL_FLOAT;
			case ShaderDataType::Mat4:	  return GL_FLOAT;

			case ShaderDataType::Int:	    return GL_INT;
			case ShaderDataType::Int2:	  return GL_INT;
			case ShaderDataType::Int3:	  return GL_INT;
			case ShaderDataType::Int4:	  return GL_INT;

			case ShaderDataType::Float:	  return GL_FLOAT;
			case ShaderDataType::Float2:	return GL_FLOAT;
			case ShaderDataType::Float3:	return GL_FLOAT;
			case ShaderDataType::Float4:	return GL_FLOAT;

			default: nc_fatal("Unknown ShaderDataType!"); return 0;
			}
		}
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &m_render_id);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_render_id);
	}
	
	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_render_id);
	}

	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& _vertex_buffer) {
		glBindVertexArray(m_render_id);
		_vertex_buffer->Bind();

		uint32_t index = 0;
		BufferLayout layout = _vertex_buffer->GetLayout();
		nc_assert(layout.GetElements().size(), "Vertex layout is not set!")
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetCount(),
				ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.offset
			);
			++index;
		}

		m_vertex_buffers.push_back(_vertex_buffer);

	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& _index_buffer) {
		glBindVertexArray(m_render_id);
		_index_buffer->Bind();
		m_index_buffer = _index_buffer;
	}
}
