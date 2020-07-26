#include "SandBox2D.h"

SandBox2D::SandBox2D()
	:Layer("SandBox2D")
{
	
}

void SandBox2D::OnAttach()
{
	BHive::Ref<BHive::PerspectiveCameraComponent> camera = std::make_shared<BHive::PerspectiveCameraComponent>(65.0f, (16.0f / 9.0f), .01f, 1000.f);
	camera->GetTransform().SetPosition(0.0f, 0.0f, 1.0f);
	m_OrthoCameraController = std::make_shared<BHive::PerspectiveCameraController>(camera);
	BHive::Texture2D::Create("AwesomeFace", "Import/Textures/awesomeface.png");

	m_Texture = BHive::TextureManager::Get("grasspng");
	m_Texture2 = BHive::TextureManager::Get("AwesomeFace");

	BHive::TextureManager::PrintAssetNames();

	//BHive::Timer time2("Sandbox");

	BHive::Actor* actor0 = BHive::SpawnActor<BHive::Actor>("Actor 0", BHive::Transform(BHive::Vector3(0.0f, 0.0f,-.5f), BHive::Rotator(0.0f)));

	m_Plane = actor0->AddComponent<BHive::Plane>();
	m_Plane->SetShader(BHive::ShaderLibrary::Get("Default"));
	m_Plane->SetTexture(m_Texture2);

	
	triangle = actor0->AddComponent<BHive::Triangle>();
	triangle->SetShader(BHive::ShaderLibrary::Get("Default"));
	triangle->GetTransform().SetPosition(1.0f, 2.0f, -.5f);

	/*BHive::Ref<BHive::FMesh> GrenadeMesh = BHive::LoadFromFile("Import/Meshes/Grenades.obj");
	BHive::RenderComponent* Grenades = actor0->AddComponent<BHive::RenderComponent>();
	Grenades->SetMesh(GrenadeMesh);
	Grenades->SetShader(BHive::ShaderLibrary::Get("Default"));
	Grenades->GetShader()->SetFloat4("u_Color", 1.0f, 0.0f, 1.0f, 1.0f);
	Grenades->GetTransform().SetPosition(1.0f, -2.0f, -.5f);*/
	//Grenades->SetTexture(m_Texture);

	BH_TRACE("{0}", m_Texture.use_count());

	BHive::ConstructObject<BHive::Object>("1st Object");
	BHive::ConstructObject<BHive::Object>("2nd Object");

	//BHive::Entity* E0 = scene0->AddEntity<BHive::Entity>();

	//BHive::Ref<BHive::Entity> square = std::shared_ptr<BHive::Entity>(E0);

	//BHive::Plane* T1 = square->AddComponent<BHive::Plane>();
	//T1->SetShader(shader);
	//T1->SetTexture(m_Texture);

	//BHive::Renderer2D::AddScene(scene0);

	BHive::ActorManager::Start();


	BHive::Renderer2D::Init();
}

void SandBox2D::OnUpdate(const BHive::Time& time)
{
	BH_PROFILE_FUNCTION();

	m_OrthoCameraController->OnUpdate(time);

	BHive::Renderer2D::Begin(*m_OrthoCameraController->GetCamera().get());
	BHive::ActorManager::Update(time);
	BHive::ObjectManager::CheckPendingDestroy();
	BHive::Renderer2D::End();
}

void SandBox2D::OnImGuiRender()
{	
	ImGui::Begin("Transform");
	BHive::Vector3<float> Position = triangle->GetTransform().GetPosition();
	if (ImGui::InputFloat3("Position", *Position, 2))
	{
		triangle->GetTransform().SetPosition(Position);
	}

	ImGui::End();
}

void SandBox2D::OnEvent(BHive::Event& event)
{
	m_OrthoCameraController->OnEvent(event);
}

void SandBox2D::OnDetach()
{
	BHive::ActorManager::Shutdown();

	BHive::Renderer2D::ShutDown();
}

