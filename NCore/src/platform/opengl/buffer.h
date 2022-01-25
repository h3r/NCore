#include "render/buffer.h"

namespace NC {
  struct OpenGLVertexBuffer: public VertexBuffer {
    OpenGLVertexBuffer(float* vertices, size_t size);
    ~OpenGLVertexBuffer() override;
    void Bind() const override;
    void Unbind() const override;
    static OpenGLVertexBuffer* Create(float* vertices, size_t size);
  private:
    uint32_t m_render_id;
  };

  struct OpenGLIndexBuffer : public VertexBuffer {
    OpenGLIndexBuffer(uint32_t* vertices, size_t size);
    ~OpenGLIndexBuffer() override;
    void Bind() const override;
    void Unbind() const override;
    static OpenGLIndexBuffer* Create(uint32_t* vertices, size_t size);
  };
}
