#pragma once

#include "render/texture.h"

#include <glad/glad.h>

namespace NC {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t _width, uint32_t _height);
		OpenGLTexture2D(const std::string& _path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_width; }
		virtual uint32_t GetHeight() const override { return m_height; }
		virtual uint32_t GetRenderID() const override { return m_render_id; }

		virtual void SetData(void* _data, uint32_t _size) override;

		virtual void Bind(uint32_t _slot = 0) const override;

		virtual bool IsLoaded() const override { return m_is_loaded; }

		virtual bool operator==(const Texture& _other) const override {
			return m_render_id == ((OpenGLTexture2D&)_other).m_render_id;
		}
	private:
		std::string m_path;
		bool m_is_loaded = false;
		uint32_t m_width, m_height;
		uint32_t m_render_id;
		GLenum m_internal_format, m_data_format;
	};

}
