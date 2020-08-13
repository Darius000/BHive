#pragma once

#include "BHive/Renderer/Framebuffer.h"

namespace BHive
{
	using RendererID = uint32;

	class OpenglFramebuffer : public FrameBuffer
	{
	public:
		OpenglFramebuffer(const FrameBufferSpecification& spec);
		virtual ~OpenglFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void UnBind() override;
		void Resize(uint32 width, uint32 height) override;

		virtual uint32 GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
		virtual const FrameBufferSpecification& GetSpecification() const { return m_Specification; }

	private:
		RendererID m_RendererID = 0;
		RendererID m_MultiSampleRenderID = 0;
		uint32 m_multisampleAttachment = 0;
		uint32 m_ColorAttachment = 0;
		uint32 m_DepthAttachment = 0;
		uint32 samples = 8;
		FrameBufferSpecification m_Specification;
	};
}