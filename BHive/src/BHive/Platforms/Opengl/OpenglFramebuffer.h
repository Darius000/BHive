#pragma once

#include "BHive/Renderer/Framebuffer.h"


namespace BHive
{
	enum class EFrameBufferStatus : int
	{
		Complete = GL_FRAMEBUFFER_COMPLETE,
		InComplete_Attachment = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
		Missing_Attachment = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
		UnSupported = GL_FRAMEBUFFER_UNSUPPORTED,
		IncompleteDimensions = 36057
	};

	static std::unordered_map<EFrameBufferStatus, const char*> FrameBufferToStrings = {
		{EFrameBufferStatus::Complete , "Complete"},
		{EFrameBufferStatus::InComplete_Attachment, "InComplete_Attachment"},
		{EFrameBufferStatus::Missing_Attachment, "Missing_Attachment"},
		{EFrameBufferStatus::UnSupported, "UnSupported"},
		{EFrameBufferStatus::IncompleteDimensions, "IncompleteDimensions"}
	};

	using RendererID = uint32;

	class OpenglFramebuffer : public FrameBuffer
	{
	public:
		OpenglFramebuffer(const std::string& name, const FrameBufferSpecification& spec);
		virtual ~OpenglFramebuffer();

		void InValidate() override;

		void Bind() override;
		void UnBind() override;
		void Resize(uint32 width, uint32 height) override;
	
		void CheckFrameBufferStatus() const override;
		uint32 GetRenderID() const override { return m_RendererID; }
		uint32 GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
		const FrameBufferSpecification& GetSpecification() const override { return m_Specification; }

		int32 m_InternalFormat = GL_RGBA8;
		uint32 m_Format = GL_RGBA;
		uint32 m_Type = GL_UNSIGNED_BYTE;


	protected:
		RendererID m_RendererID = 0;
		
		uint32 m_ColorAttachment = 0;

		std::string m_Name;
		
		FrameBufferSpecification m_Specification;

		friend class Viewport;
	};

	
}