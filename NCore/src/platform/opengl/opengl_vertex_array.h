#pragma once
#include "render/vertex_array.h"

namespace NC {

	class OpenGLVertexArray : public VertexArray
	{
	public: 
		OpenGLVertexArray();
		~OpenGLVertexArray();
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& _vertex_buffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& _index_buffer) override; 
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_index_buffer; };
		virtual const std::vector< Ref<VertexBuffer> >& GetVertexBuffers() const override { return m_vertex_buffers; };

	private:
		uint32_t m_render_id;
		Ref<IndexBuffer> m_index_buffer;
		std::vector<Ref<VertexBuffer>> m_vertex_buffers;
	};

}

