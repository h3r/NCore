#pragma once


#include "core/core.h"

namespace NC {

	class NC_API Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetRenderID() const = 0;

		virtual void SetData(void* _data, uint32_t _size) = 0;

		virtual void Bind(uint32_t _slot = 0) const = 0;

		virtual bool IsLoaded() const = 0;

		virtual bool operator==(const Texture& _other) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t _width, uint32_t _height);
		static Ref<Texture2D> Create(const std::string& _path);
	};

}
