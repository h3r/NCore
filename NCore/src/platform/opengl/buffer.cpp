#include "ncpch.h"
#include "buffer.h"
#include <glad/glad.h>

namespace NC {
  OpenGLVertexBuffer::OpenGLVertexBuffer(float* _vertices, size_t _size){
    glCreateBuffers(1, &m_render_id);
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

  /*OpenGLVertexBuffer* OpenGLVertexBuffer::Create(float* _vertices, size_t _size) {

  }*/


  OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* vertices, size_t size) {

  }

  OpenGLIndexBuffer::~OpenGLIndexBuffer() {

  }

  void OpenGLIndexBuffer::Bind() const {

  }

  void OpenGLIndexBuffer::Unbind() const {

  }

  /*OpenGLIndexBuffer* OpenGLIndexBuffer::Create(uint32_t* vertices, size_t size) {

  }*/
}
