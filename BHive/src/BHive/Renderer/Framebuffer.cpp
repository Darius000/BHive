#include "BHivePCH.h"
#include "Framebuffer.h"

#include "Bhive/Renderer/Renderer.h"
#include "BHive/Platforms/Opengl/OpenGlFramebuffer.h"

namespace BHive
{

	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: BH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return Make_Ref<OpenglFramebuffer>(spec);
		case RendererAPI::API::DirectX: break;
		}

		BH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	DepthFrameBuffer::DepthFrameBuffer(const FrameBufferSpecification& spec)
		:m_Specification(spec)
	{
		glCreateFramebuffers(1, &m_DepthID);
	}

	DepthFrameBuffer::~DepthFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_DepthID);
		glDeleteTextures(1, &m_DepthAttachment);
	}

	void DepthFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_DepthID);
		glViewport(0, 0, m_Specification.Width, m_Specification.Height);
	}

	void DepthFrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void DepthFrameBuffer::Resize(uint32 width, uint32 height)
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

	void DepthFrameBuffer::InValidate()
	{
		if (m_DepthID)
		{
			//glDeleteFramebuffers(1, &m_RendererID);
			//glDeleteFramebuffers(1, &m_MultiSampleRenderID);
			//glDeleteTextures(1, &m_multisampleAttachment);
			glDeleteTextures(1, &m_DepthAttachment);
		}

		//Create Depth Buffer
		glBindFramebuffer(GL_FRAMEBUFFER, m_DepthID);
		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);

		//glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, m_Specification.Width, m_Specification.Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment2);
		glBindTexture(GL_TEXTURE_2D, m_DepthAttachment2);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT24, m_Specification.Width, m_Specification.Height);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment2, 0);

		BH_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}