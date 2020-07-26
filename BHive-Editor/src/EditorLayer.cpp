#include "EditorLayer.h"

namespace BHive
{ 
EditorLayer::EditorLayer()
		:Layer("EditorLayer"), triangle(nullptr), m_Plane(nullptr)
	{
	
	}

	void EditorLayer::OnAttach()
	{
		FrameBufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = BHive::FrameBuffer::Create(fbSpec);

		Ref<PerspectiveCameraComponent> camera = std::make_shared<BHive::PerspectiveCameraComponent>(65.0f, (16.0f / 9.0f), .01f, 1000.f);
		camera->GetTransform().SetPosition(0.0f, 0.0f, 1.0f);
		m_OrthoCameraController = std::make_shared<BHive::PerspectiveCameraController>(camera);
		//Texture2D::Create("CheckerMap", "Import/Textures/checkermap.png");

		m_Texture = BHive::TextureManager::Get("grasspng");
		m_Texture2 = BHive::TextureManager::Get("checkermap");

		//BHive::TextureManager::PrintAssetNames();

		//BHive::Timer time2("Sandbox");

		BHive::Actor* actor0 = BHive::SpawnActor<BHive::Actor>("Actor 0", BHive::Transform(BHive::Vector3(0.0f, 0.0f,-.5f), BHive::Rotator(0.0f)));

		m_Plane = actor0->AddComponent<BHive::Plane>();
		m_Plane->SetShader(BHive::ShaderLibrary::Get("Default"));
		m_Plane->SetTexture(m_Texture2);

	
		triangle = actor0->AddComponent<BHive::Triangle>();
		triangle->SetShader(BHive::ShaderLibrary::Get("Default"));
		triangle->GetTransform().SetPosition(1.0f, 2.0f, -.5f);
		triangle->SetTexture(m_Texture2);

		/*BHive::Ref<BHive::FMesh> GrenadeMesh = BHive::LoadFromFile("Import/Meshes/Grenades.obj");
		BHive::RenderComponent* Grenades = actor0->AddComponent<BHive::RenderComponent>();
		Grenades->SetMesh(GrenadeMesh);
		Grenades->SetShader(BHive::ShaderLibrary::Get("Default"));
		Grenades->GetShader()->SetFloat4("u_Color", 1.0f, 0.0f, 1.0f, 1.0f);
		Grenades->GetTransform().SetPosition(1.0f, -2.0f, -.5f);*/
		//Grenades->SetTexture(m_Texture);

		//BH_TRACE("{0}", m_Texture.use_count());

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

	void EditorLayer::OnUpdate(const BHive::Time& time)
	{
		BH_PROFILE_FUNCTION();

		m_Framebuffer->Bind();

		if(m_ViewportFocused)
			m_OrthoCameraController->OnUpdate(time);

		BHive::Renderer2D::Begin(*m_OrthoCameraController->GetCamera().get());
		BHive::ActorManager::Update(time);
		BHive::ObjectManager::CheckPendingDestroy();
		BHive::Renderer2D::End();

		m_Framebuffer->UnBind();
	}

	void EditorLayer::OnImGuiRender()
	{	
		static bool dockSpaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
		bool opt_fullscreen = opt_fullscreen_persistant;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruDockspace, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (opt_flags & ImGuiDockNodeFlags_PassthruDockspace)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockSpaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Dockspace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
		}


		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit")) BHive::Application::Get().Close();

				ImGui::EndMenu();
			}
		
			ImGui::EndMenuBar();
		}

		ImGui::Begin("Transform");
		BHive::Vector3<float> Position = triangle->GetTransform().GetPosition();
		if (ImGui::InputFloat3("Position", *Position, 2))
		{
			triangle->GetTransform().SetPosition(Position);
		}
		ImGui::End();

		//Viewport Window
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0});
		ImGui::Begin("Viewport");
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(m_ViewportFocused && m_ViewportHovered);

		//BH_WARN("Is Viewport Focused: {0}", m_ViewportFocused);

		if (m_ViewportSize != *((FVector2*)&viewportPanelSize) && viewportPanelSize.x > 0 && viewportPanelSize.y > 0)
		{
			
			m_Framebuffer->Resize((uint32)viewportPanelSize.x, (uint32)viewportPanelSize.y);
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
		}
		
		uint32 textureID = m_Framebuffer->GetColorAttachmentRendererID();
		//BH_WARN("Viewport Size: {0}, {1}", viewportPanelSize.x, viewportPanelSize.y);
		ImGui::Image((void*)textureID, ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0,1), ImVec2(1,0));
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(BHive::Event& event)
	{
		if(m_ViewportFocused)
			m_OrthoCameraController->OnEvent(event);
	}

	void EditorLayer::OnDetach()
	{
		BHive::ActorManager::Shutdown();

		BHive::Renderer2D::ShutDown();
	}

}