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

		m_Camera = m_Scene->CreateEntity("Camera");
		m_Camera.AddComponent<CameraComponent>();
		m_Camera.GetComponent<CameraComponent>().m_Camera.SetPerspective({ 35.0f, .01f, 1000.0f });
		m_Camera.GetComponent<CameraComponent>().m_PrimaryCamera = true;
		m_Camera.GetComponent<TransformComponent>().m_Transform.SetPosition({ 0.0f, 0.0f, 10.0f });
	}

	void Viewport::OnUpdate(const Time& time)
	{
		m_Framebuffer->Bind();

		Renderer2D::Begin();
		m_Scene->OnUpdate(time);
		Renderer2D::End();

		glBindFramebuffer(GL_FRAMEBUFFER, ((OpenglFramebuffer*)(m_Framebuffer.get()))->m_RendererID);
		//glReadBuffer(GL_COLOR_ATTACHMENT0);
		glReadPixels(0, 0, 800, 600, GL_RGBA, GL_UNSIGNED_BYTE, m_Data);

		AssetManager::Add<Texture2D>(Texture2D::Create("FrameBufferX", 800, 600,
			GL_RGBA8, GL_RGBA, (void*)m_Data));

		m_Framebuffer->UnBind();
	}
}