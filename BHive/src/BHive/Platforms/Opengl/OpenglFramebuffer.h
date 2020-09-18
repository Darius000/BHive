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

		void Bind() override;
		void UnBind() override;
		void Resize(uint32 width, uint32 height) override;
	
		uint32 GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
		const FrameBufferSpecification& GetSpecification() const override { return m_Specification; }

	private:

		RendererID m_RendererID = 0;
		RendererID m_MultiSampleRenderID = 0;
		uint32 m_multisampleAttachment = 0;
		uint32 m_ColorAttachment = 0;
		uint32 m_DepthAttachment = 0;
		uint32 samples = 8;
		FrameBufferSpecification m_Specification;

		friend class Viewport;
	};
}