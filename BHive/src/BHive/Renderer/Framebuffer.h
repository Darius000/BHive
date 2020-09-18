#pragma once

namespace BHive
{
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
	
		virtual uint32 GetColorAttachmentRendererID() const = 0;
		virtual void Resize(uint32 width, uint32 height) = 0;
	
		//virtual FrameBufferSpecification& GetSpecification() = 0;
		virtual const FrameBufferSpecification& GetSpecification() const = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);

		operator void*() const { return (void*)GetColorAttachmentRendererID(); }
	};
}