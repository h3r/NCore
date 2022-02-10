#pragma once

#include "render/framebuffer.h"

namespace NC {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t _width, uint32_t _height) override;
		virtual int ReadPixel(uint32_t _attachment_index, int _x, int _y) override;

		virtual void ClearAttachment(uint32_t _attachment_index, int _value) override;

		virtual uint32_t GetColorAttachmentRenderID(uint32_t index = 0) const override { nc_assert(index < m_color_attachments.size(),""); return m_color_attachments[index]; }

		virtual const FramebufferSpecification& GetSpecification() const override { return m_specification; }
	private:
		uint32_t m_render_id = 0;
		FramebufferSpecification m_specification;

		std::vector<FramebufferTextureSpecification> m_color_attachment_specifications;
		FramebufferTextureSpecification m_depth_attachment_specification = FramebufferTextureFormat::None;

		std::vector<uint32_t> m_color_attachments;
		uint32_t m_depth_attachment = 0;
	};

}
