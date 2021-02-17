#include "BHivePCH.h"
#include "OpenGLMultiSampleFrameBuffer.h"

namespace BHive
{

	OpenGLMultiSampleFrameBuffer::OpenGLMultiSampleFrameBuffer(const std::string& name, const FrameBufferSpecification& spec)
		:OpenglFramebuffer(name, spec)
	{
		glCreateFramebuffers(1, &m_MultiSampledFBO);
	}

	OpenGLMultiSampleFrameBuffer::~OpenGLMultiSampleFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_MultiSampledFBO);
		glDeleteTextures(1, &m_MultiSampledColorAttachment);
	}

	void OpenGLMultiSampleFrameBuffer::InValidate()
	{
		if (m_RendererID && m_MultiSampledFBO)
		{
			glDeleteTextures(1, &m_MultiSampledColorAttachment);
			glDeleteTextures(1, &m_ColorAttachment);
		}

		//Create MSAA framebuffer
		//----------------------------------
		glBindFramebuffer(GL_FRAMEBUFFER, m_MultiSampledFBO);

		//Color texture
		glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &m_MultiSampledColorAttachment);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_MultiSampledColorAttachment);

		//Set multi sample texture data
		glTexImage2DMultisample(
			GL_TEXTURE_2D_MULTISAMPLE,
			m_Specification.Samples,
			m_MultiSampleInternalFormat,
			m_Specification.Width,
			m_Specification.Height,
			GL_TRUE);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_MultiSampledColorAttachment, 0);

		CheckFrameBufferStatus();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);


		//Create Screen FrameBuffer
		//-----------------------------
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Specification.Width,
			m_Specification.Height, 0, m_Format, m_Type, nullptr);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

	
		CheckFrameBufferStatus();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLMultiSampleFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_MultiSampledFBO);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_RendererID );
		glBlitFramebuffer(0, 0, m_Specification.Width, m_Specification.Height, 0, 0 ,
		m_Specification.Width, m_Specification.Height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	}
}