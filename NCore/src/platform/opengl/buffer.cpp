#include "ncpch.h"
#include "buffer.h"
#include <glad/glad.h>

namespace NC {
  OpenGLVertexBuffer::OpenGLVertexBuffer(float* _vertices, uint32_t _size){
    glCreateBuffers(1, &m_render_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_render_id);
    glBufferData(GL_ARRAY_BUFFER, _size, _vertices, GL_STATIC_DRAW);
  }

  OpenGLVertexBuffer::~OpenGLVertexBuffer() {
    glDeleteBuffers(1, &m_render_id);
  }

  void OpenGLVertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_render_id);
  }

  void OpenGLVertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  OpenGLVertexBuffer* OpenGLVertexBuffer::Create(float* _vertices, uint32_t _size) {
		return new OpenGLVertexBuffer(_vertices, _size);
  }





	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* _indices, uint32_t _count)
		: m_count(_count)
	{
		glCreateBuffers(1, &m_render_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_render_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _count * sizeof(uint32_t), _indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		glDeleteBuffers(1, &m_render_id);
	}

	void OpenGLIndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_render_id);
	}

	void OpenGLIndexBuffer::Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	OpenGLIndexBuffer* OpenGLIndexBuffer::Create(uint32_t* _indices, uint32_t _count) {
		return new OpenGLIndexBuffer(_indices, _count);
	}
}
