#pragma once

namespace NC {
  struct VertexBuffer {
    virtual ~VertexBuffer() {}
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    static VertexBuffer* Create(float* vertices, size_t size);
  };

  struct IndexBuffer {
    virtual ~IndexBuffer() {}
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    static IndexBuffer* Create(uint32_t* vertices, size_t size);
  };
}
