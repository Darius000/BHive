#include "SandBox2D.h"

SandBox2D::SandBox2D()
	:Layer("SandBox2D")
{
	BHive::Ref<BHive::PerspectiveCameraComponent> camera = std::make_shared<BHive::PerspectiveCameraComponent>(65.0f, (16.0f / 9.0f), .01f, 1000.f );
	m_OrthoCameraController = std::make_shared<BHive::PerspectiveCameraController>( camera , 16.0f / 9.0f);
}

void SandBox2D::OnAttach()
{
	m_Texture = BHive::Texture2D::Create("Assets/Textures/grass.png");
	BHive::Ref<BHive::Texture2D> m_Texture2 = BHive::Texture2D::Create("Assets/Textures/awesomeface.png");

	BHive::Timer time2("Sandbox");

	BHive::Actor* actor0 = BHive::SpawnActor<BHive::Actor>("Actor 0", BHive::Transform(BHive::Vector3(0.0f, 0.0f,-.5f), BHive::Rotator(0.0f)));

	BHive::Plane* plane = actor0->AddComponent<BHive::Plane>();
	plane->SetShader(BHive::ShaderLibrary::Get("Default"));
	plane->SetTexture(m_Texture);

	BHive::Plane* triangle = actor0->AddComponent<BHive::Plane>();
	triangle->SetShader(BHive::ShaderLibrary::Get("BoundingBox"));
	triangle->GetTransform().SetPosition(1.0f, 2.0f, -.5f);
	triangle->SetTexture(m_Texture2);


	//BHive::Entity* E0 = scene0->AddEntity<BHive::Entity>();

	//BHive::Ref<BHive::Entity> square = std::shared_ptr<BHive::Entity>(E0);

	//BHive::Plane* T1 = square->AddComponent<BHive::Plane>();
	//T1->SetShader(shader);
	//T1->SetTexture(m_Texture);

	//BHive::Renderer2D::AddScene(scene0);

	BHive::Renderer2D::Init();
}

void SandBox2D::OnUpdate(const BHive::Time& time)
{
	m_OrthoCameraController->OnUpdate(time);

	BHive::Renderer2D::Begin(*m_OrthoCameraController->GetCamera().get());
	BHive::Renderer2D::End();
}

void SandBox2D::OnImGuiRender()
{
	BHive::BString ImGUIName = m_DebugName + " Settings";
	ImGui::Begin(*ImGUIName);
	ImGui::End();
}

void SandBox2D::OnEvent(BHive::Event& event)
{
	m_OrthoCameraController->OnEvent(event);
}

void SandBox2D::OnDetach()
{
	BHive::Renderer2D::ShutDown();
}

