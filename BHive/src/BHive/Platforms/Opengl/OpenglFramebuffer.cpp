#include "BHivePCH.h"
#include "OpenglFramebuffer.h"

#include <Glad/glad.h>

namespace BHive
{

	OpenglFramebuffer::OpenglFramebuffer(const std::string& name, const FrameBufferSpecification& spec)
		:m_Specification(spec), m_Name(name)
	{
		glCreateFramebuffers(1, &m_RendererID);
	}

	OpenglFramebuffer::~OpenglFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_ColorAttachment);
	}

	void OpenglFramebuffer::InValidate()
	{
		if (m_RendererID)
		{
			glDeleteTextures(1, &m_ColorAttachment);
		}

		//Create screen framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		//Color texture
		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Specification.Width, 
			m_Specification.Height , 0, m_Format, m_Type, nullptr);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

		CheckFrameBufferStatus();

	}

	void OpenglFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		glViewport(0, 0, m_Specification.Width, m_Specification.Height);	
	}

	void OpenglFramebuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenglFramebuffer::Resize(uint32 width, uint32 height)
	{
		if (width == 0 || height == 0 || width > s_MaxFramebufferSize || height > s_MaxFramebufferSize)
		{
			BH_CORE_WARN("Attemped to resize framebuffer to {0}, {1}", width, height);
			return;
		}

		m_Specification.Width = width;
		m_Specification.Height = height;

		InValidate();
	}

	void OpenglFramebuffer::CheckFrameBufferStatus() const
	{
		EFrameBufferStatus status = (EFrameBufferStatus)glCheckFramebufferStatus(GL_FRAMEBUFFER);

		if ( status != EFrameBufferStatus::Complete)
		{
			BH_CORE_ERROR("{0} Framebuffer Status {1} , ID = {2}", m_Name, FrameBufferToStrings[status], m_RendererID );
			return;
		}

		BH_CORE_INFO("{0} Framebuffer Status {1} , ID = {2}",m_Name, FrameBufferToStrings[status], m_RendererID);
	}

}