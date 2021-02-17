#pragma once

#include "OpenglFramebuffer.h"

namespace BHive
{
	class OpenGLMultiSampleFrameBuffer : public OpenglFramebuffer
	{
	public:
		OpenGLMultiSampleFrameBuffer(const std::string& name, const FrameBufferSpecification& spec);
		~OpenGLMultiSampleFrameBuffer();

		void InValidate() override;

		uint32 m_MultiSampledColorAttachment = -1;
		RendererID m_MultiSampledFBO = -1;

		GLenum m_MultiSampleInternalFormat = GL_RGBA4;

		void Bind() override;
	};
}