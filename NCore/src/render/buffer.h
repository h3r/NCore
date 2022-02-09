#pragma once
#include "buffer_layout.h"

namespace NC {
  struct NC_API VertexBuffer {
    virtual ~VertexBuffer() {}
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
		virtual void SetLayout(const BufferLayout& _layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;
    static VertexBuffer* Create(float* vertices, uint32_t size);
  };

  struct NC_API IndexBuffer {
    virtual ~IndexBuffer() {}
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
		virtual uint32_t GetCount() const = 0;
    static IndexBuffer* Create(uint32_t* indices, uint32_t count);
  };
}
