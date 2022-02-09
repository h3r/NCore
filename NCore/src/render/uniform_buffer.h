#pragma once

namespace NC
{
	class NC_API CUniformBuffer {
	public:
		void SetData(void* _data, size_t const _size)
		{
			memcpy(m_data, _data, _size);
		}
		void Bind() {}
		void Unbind() {}
	private:
		void* m_data;
	};
}
