#pragma once

namespace BHive
{
	static const uint32 s_MaxFramebufferSize = 8192;

	struct FrameBufferSpecification
	{
		uint32 Width = 0, Height = 0;
		uint32 Samples = 1;

		bool SwapChainTarget = false;
	};

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer(){}
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
	
		virtual uint32 GetRenderID() const = 0;
		virtual uint32 GetColorAttachmentRendererID() const = 0;
		virtual void Resize(uint32 width, uint32 height) = 0;
		virtual void CheckFrameBufferStatus() const = 0;
	
		//virtual FrameBufferSpecification& GetSpecification() = 0;
		virtual const FrameBufferSpecification& GetSpecification() const = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);

		operator void*() const { return (void*)(uintPtr)GetColorAttachmentRendererID(); }
	};

	class DepthFrameBuffer : public FrameBuffer
	{
	public:
		DepthFrameBuffer(const FrameBufferSpecification& spec);
		virtual ~DepthFrameBuffer();

		void Bind() override;
		void UnBind() override;
		void Resize(uint32 width, uint32 height) override;
		void InValidate();
		uint32 GetColorAttachmentRendererID() const override { return m_DepthAttachment; }
		const FrameBufferSpecification& GetSpecification() const override { return m_Specification; }

		uint32 m_DepthID = 0;
		uint32 m_DepthAttachment = 0;
		uint32 m_DepthAttachment2 = 0;
		FrameBufferSpecification m_Specification;

		friend class Viewport;
	};
}