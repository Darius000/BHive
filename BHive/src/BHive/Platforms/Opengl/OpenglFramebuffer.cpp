#include "BHivePCH.h"
#include "OpenglFramebuffer.h"

#include <Glad/glad.h>

namespace BHive
{
	static const uint32 s_MaxFramebufferSize = 8192;

	OpenglFramebuffer::OpenglFramebuffer(const FrameBufferSpecification& spec)
		:m_Specification(spec)
	{
		glCreateFramebuffers(1, &m_RendererID);
		
		Invalidate();	

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	OpenglFramebuffer::~OpenglFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteTextures(1, &m_DepthAttachment);

	}

	void OpenglFramebuffer::Invalidate()
	{

		if (m_RendererID)
		{
			//glDeleteFramebuffers(1, &m_RendererID);
			//glDeleteFramebuffers(1, &m_MultiSampleRenderID);
			//glDeleteTextures(1, &m_multisampleAttachment);
			glDeleteTextures(1, &m_ColorAttachment);
			glDeleteTextures(1, &m_DepthAttachment);
		}


		//Create mulitsample framebuffer
		/*glCreateFramebuffers(1, &m_MultiSampleRenderID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_MultiSampleRenderID);

		glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &m_multisampleAttachment);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_multisampleAttachment);
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGBA, m_Specification.Width, m_Specification.Height, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_multisampleAttachment, 0);

		BH_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Multisample Framebuffer is incomplete");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);*/

		//Create screen framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);

		glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Specification.Width, 
			m_Specification.Height , 0, m_Format, m_Type, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);
	

		//Create Depth Buffer
		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

		BH_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete");
		
		
	}

	void OpenglFramebuffer::Bind()
	{
		//glBindFramebuffer(GL_READ_FRAMEBUFFER, m_MultiSampleRenderID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		//glBlitFramebuffer(0, 0, m_Specification.Width, m_Specification.Height, 0, 0, m_Specification.Width, m_Specification.Height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
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

		Invalidate();
	}
}