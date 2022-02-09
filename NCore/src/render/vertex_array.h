#pragma once
#include "render/buffer.h"
namespace NC
{

	class VertexArray
	{
	public: ~VertexArray() {}
				virtual void Bind() const = 0;
				virtual void Unbind() const = 0;

				virtual void SetIndexBuffer( const Ref<IndexBuffer>&  _index_buffer)  = 0;
				virtual void AddVertexBuffer(const Ref<VertexBuffer>& _vertex_buffer) = 0;
				virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
				virtual const std::vector< Ref<VertexBuffer> >& GetVertexBuffers() const = 0;

				static VertexArray* Create();
	};

}

