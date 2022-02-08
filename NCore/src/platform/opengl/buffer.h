#include "render/buffer.h"

namespace NC {
  struct OpenGLVertexBuffer: public VertexBuffer {
    OpenGLVertexBuffer(float* vertices, size_t size);
		virtual ~OpenGLVertexBuffer() override;
    virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void SetLayout(const BufferLayout& _layout) override { m_layout = _layout; }
		virtual const BufferLayout& GetLayout(const BufferLayout& _layout) const override { return m_layout; }
	  static OpenGLVertexBuffer* Create(float* vertices, size_t size);
  private:
    uint32_t m_render_id;
		BufferLayout m_layout;
  };

  struct OpenGLIndexBuffer : public IndexBuffer {
		OpenGLIndexBuffer(uint32_t* _indices, uint32_t _count);
		virtual ~OpenGLIndexBuffer() override;
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual uint32_t GetCount() const { return m_count; };
	  static OpenGLIndexBuffer* Create(uint32_t* indices, size_t size);
	private:
		uint32_t m_count;
		uint32_t m_render_id;
  };
}
