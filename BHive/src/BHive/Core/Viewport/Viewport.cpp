#include "BHivePCH.h"
#include "Viewport.h"
#include "Renderer/Renderer2D.h"
#include "Platforms/Opengl/OpenglFramebuffer.h"

namespace BHive
{

	Viewport::Viewport(const FrameBufferSpecification& specs, Scene* scene)
		:m_FramebufferSpecs(specs) ,m_Scene(scene)
	{
		m_Framebuffer = FrameBuffer::Create(m_FramebufferSpecs);
		m_Framebuffer->Bind();
		((OpenglFramebuffer*)m_Framebuffer.get())->m_InternalFormat = GL_RGBA16F;
		((OpenglFramebuffer*)m_Framebuffer.get())->m_Type = GL_FLOAT;
		((OpenglFramebuffer*)m_Framebuffer.get())->Invalidate();
		m_Framebuffer->UnBind();

		m_SceneFramebuffer = FrameBuffer::Create(m_FramebufferSpecs);

		m_Camera = m_Scene->CreateEntity("Camera");
		m_Camera.AddComponent<CameraComponent>();
		m_Camera.GetComponent<CameraComponent>().m_Camera.SetPerspective({ 35.0f, .01f, 1000.0f });
		m_Camera.GetComponent<CameraComponent>().m_PrimaryCamera = true;
		m_Camera.GetComponent<TransformComponent>().m_Transform.SetPosition({ 0.0f, 0.0f, 10.0f });

		quad = Renderer2D::Quad();
		ppm = Make_Ref<PostProcessingMaterial>();
		ppm->m_Name = "PPM";
		quad->GetMesh(0)->SetMaterial(ppm);
	}

	void Viewport::OnUpdate(const Time& time)
	{
		//render scene
		m_Framebuffer->Bind();
		RenderCommands::EnableDepthTest();
		Renderer2D::Begin();
		m_Scene->OnUpdate(time);
		Renderer2D::End();
		m_Framebuffer->UnBind();
		
		//render quad
		m_SceneFramebuffer->Bind();
		RenderCommands::DisableDepthTest();
		Renderer2D::Begin();	
		auto ppshader = quad->GetMesh(0)->GetMaterial()->GetShader();
		ppshader->Bind();
		ppshader->SetInt("hdrtexture", 6);
		ppshader->SetBool("hdr", m_HDR);
		ppshader->SetFloat("exposure", m_Exposure);
		RenderCommands::BindTexture(6, m_Framebuffer->GetColorAttachmentRendererID());
		quad->Render();
		RenderCommands::UnBindTexture(6);
		Renderer2D::End();
		m_SceneFramebuffer->UnBind();
	}
}