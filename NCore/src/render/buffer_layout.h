#pragma once
#include "ncpch.h"

namespace NC {

	enum class ShaderDataType : uint8_t{
		None = 0,
		Boolean,
		Mat3, Mat4, 
		Int, Int2, Int3, Int4, 
		Float, Float2, Float3, Float4, 
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Boolean:	return 1;
			case ShaderDataType::Mat3		:	return 4 * 3 * 3;
			case ShaderDataType::Mat4		:	return 4 * 4 * 4;
			
			case ShaderDataType::Int		:	return 4;
			case ShaderDataType::Int2		:	return 4 * 2;
			case ShaderDataType::Int3		:	return 4 * 3;
			case ShaderDataType::Int4		:	return 4 * 4;

			case ShaderDataType::Float	:	return 4;
			case ShaderDataType::Float2	:	return 4 * 2;
			case ShaderDataType::Float3	:	return 4 * 3;
			case ShaderDataType::Float4	:	return 4 * 4;

			default: nc_fatal("Unknown ShaderDataType!"); return 0;
		}
	}

	struct BufferElement {
		std::string name;
		ShaderDataType type;
		uint32_t offset;
		uint32_t size;
		bool normalized;
		BufferElement(){}
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: name(name)
			, type(type)
			, size(ShaderDataTypeSize(type))
			, offset(0)
			, normalized(normalized)
		{}

		uint32_t GetCount() const {
			switch (type)
			{
				case ShaderDataType::Boolean:	return 1;
				case ShaderDataType::Mat3:	  return 3 * 3;
				case ShaderDataType::Mat4:	  return 4 * 4;

				case ShaderDataType::Int:	    return 1;
				case ShaderDataType::Int2:	  return 2;
				case ShaderDataType::Int3:	  return 3;
				case ShaderDataType::Int4:	  return 4;

				case ShaderDataType::Float:	  return 1;
				case ShaderDataType::Float2:	return 2;
				case ShaderDataType::Float3:	return 3;
				case ShaderDataType::Float4:	return 4;

				default: nc_fatal("Unknown ShaderDataType!"); return 0;
			}
		}
	};

	struct NC_API BufferLayout {
		BufferLayout() {}
		BufferLayout(std::vector<BufferElement> elements) {}
		BufferLayout(const std::initializer_list<BufferElement> &elements) 
		: m_elements(elements) 
		{
			CalculateOffsetsAndStride();
		}

		inline const uint32_t& GetStride() const { return m_stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_elements; }
		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end()   { return m_elements.end();   }

	private:
		std::vector<BufferElement> m_elements;
		uint32_t m_stride = 0;
		void CalculateOffsetsAndStride() {
			uint32_t offset = 0;
			m_stride = 0;
			for (auto& element : m_elements) {
				element.offset = offset;
				offset += element.size;
				m_stride += element.size;
			}
		}
	};

}
