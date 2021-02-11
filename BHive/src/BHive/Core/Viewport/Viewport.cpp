#include "BHivePCH.h"
#include "Viewport.h"
#include "Renderer/Renderer2D.h"
#include "Platforms/Opengl/OpenglFramebuffer.h"
#include "Renderer/Model/Quad.h"

namespace BHive
{

	Viewport::Viewport(const FrameBufferSpecification& specs, Scene* scene)
		:m_Scene(scene)
	{
		GBufferAttribute albedoOpacAttr = {GL_RGBA, GL_RGBA, GL_FLOAT, 0};
		GBufferAttribute speculatAttr = {GL_RGBA, GL_RGBA, GL_FLOAT, 0};
		GBufferAttribute positionnormalAttr = { GL_RGBA16F, GL_RGBA, GL_FLOAT, 0 };


		m_GBufferAttributes = { 
			{GBufferType::SceneColor, positionnormalAttr},
			{GBufferType::Albedo, albedoOpacAttr},
			{GBufferType::Specular, speculatAttr},
			{GBufferType::Ambient, positionnormalAttr},
			{GBufferType::Emission, positionnormalAttr},
			{GBufferType::Normal, positionnormalAttr},
			{GBufferType::Position , positionnormalAttr},
			{GBufferType::TexCoord, positionnormalAttr},
		};

		m_QuadFrameBuffer = FrameBuffer::Create(specs);
		m_SceneFrameBuffer = FrameBuffer::Create(specs);
		m_PingPongFrameBuffer[0] = FrameBuffer::Create(specs);
		m_PingPongFrameBuffer[1] = FrameBuffer::Create(specs);

		Resize(specs.Width, specs.Height);

		quad = Make_Ref<Quad>();
		ppm = AssetManager::CreateAsset<Material>("PPM", AssetManager::Get<Shader>("PostProcessing"));
		quad->GetMesh(0)->SetMaterial(ppm);

		blurquad = Make_Ref<Quad>();
		blurppm = AssetManager::CreateAsset<Material>("BluePPM", AssetManager::Get<Shader>("BlurPostProcessing"));
		blurquad->GetMesh(0)->SetMaterial(blurppm);
	}

	Viewport::~Viewport()
	{
		if (m_SceneFrameBuffer && m_QuadFrameBuffer)
		{
			for (auto& GBufferAttr : m_GBufferAttributes)
			{
				glDeleteTextures(1, &GBufferAttr.second.m_Texture);
			}
			glDeleteTextures(1, &m_DepthAttachment);

			glDeleteRenderbuffers(1, &m_DepthID);
		}
	}

	void Viewport::OnUpdate(const Time& time)
	{
		
		//render scene
		RenderCommands::EnableDepthTest();
		m_SceneFrameBuffer->Bind();
		Renderer2D::Begin({0.1f, 0.1f, 0.1f, 1.0f});
		m_Scene->OnUpdateRuntime(time);
		Renderer2D::End();
		m_SceneFrameBuffer->UnBind();
	
		RenderCommands::DisableDepthTest();
		bool horizontal = true, first_iteration = true;
		int amount = 10;
		for (int i = 0; i < amount; i++)
		{
			m_PingPongFrameBuffer[horizontal]->Bind();
			Renderer2D::Begin({0.0, 0.0, 0.0, 0.0});
			auto blurppm = blurquad->GetMesh(0)->GetMaterial()->GetShader();
			blurppm->Bind();
			blurppm->SetBool("horizontal", horizontal);
			blurppm->SetInt("image", 8);
			RenderCommands::BindTexture(8, first_iteration ? m_GBufferAttributes[GBufferType::Emission].m_Texture : m_PingPongFrameBuffer[!horizontal]->GetColorAttachmentRendererID()/*m_PingPongBlur[!horizontal]*/);
			blurquad->Render();
			horizontal = !horizontal;
			if(first_iteration)
				first_iteration = false;
			RenderCommands::UnBindTexture(8);
			Renderer2D::End();
			
		}
		m_PingPongFrameBuffer[0]->UnBind();
		m_PingPongFrameBuffer[1]->UnBind();

		//render quad
		RenderCommands::DisableDepthTest();
		m_QuadFrameBuffer->Bind();
		Renderer2D::Begin({0.0, 0.0, 0.0, 0.0});	
		auto ppshader = quad->GetMesh(0)->GetMaterial()->GetShader();
		ppshader->Bind();
		ppshader->SetInt("albedocolor", 6);
		ppshader->SetInt("specularcolor", 7);
		ppshader->SetInt("ambientcolor", 8);
		ppshader->SetInt("emissioncolor", 9);
		ppshader->SetInt("normalcolor", 10);
		ppshader->SetInt("positioncolor", 11);
		ppshader->SetInt("bloomtexture", 12);
		ppshader->SetInt("environmentColor", 13);
		ppshader->SetBool("hdr", m_HDR);
		ppshader->SetBool("bloom", m_Bloom);
		ppshader->SetFloat("exposure", m_Exposure);
		RenderCommands::BindTexture(6, m_GBufferAttributes[GBufferType::Albedo].m_Texture);
		RenderCommands::BindTexture(7, m_GBufferAttributes[GBufferType::Specular].m_Texture);
		RenderCommands::BindTexture(8, m_GBufferAttributes[GBufferType::Ambient].m_Texture);
		RenderCommands::BindTexture(9, m_GBufferAttributes[GBufferType::Emission].m_Texture);
		RenderCommands::BindTexture(10, m_GBufferAttributes[GBufferType::Normal].m_Texture);
		RenderCommands::BindTexture(11, m_GBufferAttributes[GBufferType::Position].m_Texture);
		RenderCommands::BindTexture(12, m_PingPongFrameBuffer[!horizontal]->GetColorAttachmentRendererID());
		RenderCommands::BindTexture(13, (uint32)AssetManager::Get<CubeTexture>("Cube Map")->GetRendererID());
		quad->Render();
		RenderCommands::UnBindTexture(6);
		RenderCommands::UnBindTexture(7);
		Renderer2D::End();
		m_QuadFrameBuffer->UnBind();
	}

	void Viewport::Resize(uint32 width, uint32 height)
	{
		m_FramebufferSpecs.Width = width;
		m_FramebufferSpecs.Height = height;

		m_QuadFrameBuffer->Resize(width, height);
		m_SceneFrameBuffer->Resize(width, height);

		if(m_SceneFrameBuffer && m_QuadFrameBuffer)
		{ 
		
			for (auto& GBufferAttr : m_GBufferAttributes)
			{
				glDeleteTextures(1, &GBufferAttr.second.m_Texture);
			}
			glDeleteTextures(1, &m_DepthAttachment);

			glDeleteRenderbuffers(1, &m_DepthID);
		}

		glCreateRenderbuffers(1, &m_DepthID);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);

		std::vector<unsigned int> attachments;
		int  i= 0;
		for (auto& GBufferAttr : m_GBufferAttributes)
		{
			glCreateTextures(GL_TEXTURE_2D, 1, &GBufferAttr.second.m_Texture);
			glBindTexture(GL_TEXTURE_2D, GBufferAttr.second.m_Texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GBufferAttr.second.m_InternalFormat, m_FramebufferSpecs.Width, m_FramebufferSpecs.Height, 0,GBufferAttr.second.m_Format, GBufferAttr.second.m_Type, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_2D, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, GBufferAttr.second.m_Texture, 0);
			attachments.push_back(GL_COLOR_ATTACHMENT0  + i);
			i++;
		};

		glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_FramebufferSpecs.Width, m_FramebufferSpecs.Height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);


		glDrawBuffers((GLsizei)m_GBufferAttributes.size(), attachments.data());

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			BH_CORE_ERROR("Framebuffer is incomplete");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		m_PingPongFrameBuffer[0]->Resize(width, height);
		m_PingPongFrameBuffer[1]->Resize(width, height);
	}

}