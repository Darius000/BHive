#include "EditorLayer.h"


namespace BHive
{ 
EditorLayer::EditorLayer()
		:Layer("EditorLayer")
	{
	
	}

	void EditorLayer::OnAttach()
	{
		FrameBufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = BHive::FrameBuffer::Create(fbSpec);

		Scene* scene = SceneManager::CreateScene("Default");
		SceneManager::SetActiveScene("Default");

		m_Texture = BHive::TextureManager::Get("folder");
		m_Texture2 = BHive::TextureManager::Get("checkermap");

		Camera = scene->CreateEntity("Camera");
		Camera.AddComponent<CameraComponent>(Projection::Perspective);
		Camera.GetComponent<CameraComponent>().m_Camera.SetPerspective({35.0f, FVector2(16.0f , 9.0f), .01f, 1000.0f});

		Ref<Model> Shotgun = Model::Import("Import/Meshes/Shotgun/Shotgun.obj");
		Ref<Model> triangle = Renderer2D::Triangle(1.0f, 1.0f);
		Ref<Model> plane = Renderer2D::Plane(1.0f, 1.0f);

		
		actor0 = scene->CreateEntity("Shotgun");
		actor0.AddComponent<RenderComponent>();
		TransformComponent* transformComponent = &actor0.GetComponent<TransformComponent>();
		transformComponent->m_Transform.SetPosition(FVector3(0.0f, 0.0f , 0.0f));
	
		auto& renderComponent = actor0.GetComponent<RenderComponent>();
		renderComponent.m_Model = Shotgun;
		renderComponent.m_Texture = m_Texture2;
			
		Entity tri = scene->CreateEntity("Triangle");
		auto& renderComponent1 = tri.AddComponent<RenderComponent>();
		renderComponent1.m_Model = triangle;
		renderComponent1.m_Texture = m_Texture2;
	
		Entity pl = scene->CreateEntity("Plane");
		auto& rendercomponent2 = pl.AddComponent<RenderComponent>();
		rendercomponent2.m_Model = plane;
		rendercomponent2.m_Texture = m_Texture2;
	

		BHive::Renderer2D::Init();
	}

	void EditorLayer::OnUpdate(const Time& time)
	{
		BH_PROFILE_FUNCTION();

		m_Framebuffer->Bind();

		m_DeltaTime = time.GetDeltaTime();

		BHive::Renderer2D::Begin();	
		SceneManager::GetActiveScene()->OnUpdate(time);		
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

		ImGui::Begin("Details Panel");

		{
			actor0.OnImGuiRender();
			actor0.GetComponent<TransformComponent>().OnImGuiRender(actor0.GetName());
			actor0.GetComponent<RenderComponent>().OnImguiRender();
		}

		{
			Camera.OnImGuiRender();
			Camera.GetComponent<TransformComponent>().OnImGuiRender(Camera.GetName());
			Camera.GetComponent<CameraComponent>().OnImGuiRender();
			//CameraSystem::m_ActiveCamera->m_Camera.OnImguiRender();
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

		ImGui::Begin("Content Browser");
		for (const auto& texture : TextureManager::GetAssets())
		{
			ImGui::ImageButton((void*)texture.second->GetRendererID(), ImVec2(100.0f, 100.0f), ImVec2(0, 1), ImVec2(1, 0), 0, ImVec4(0,0,0,0));
		}
		ImGui::End();

		ImGui::ShowDemoWindow();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		if (m_ViewportFocused)
		{
			EventDispatcher dispatcher(event);
			dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_ONE_PARAM(EditorLayer::OnMouseScrolled));
			dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_ONE_PARAM(EditorLayer::OnMouseMoved));
			dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_ONE_PARAM(EditorLayer::OnMouseButtonPressed));
			dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_ONE_PARAM(EditorLayer::OnMouseButtonReleased));
		}
	}


	bool EditorLayer::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel = e.GetYOffset() * m_ZoomSpeed;
		m_CameraPosition.z += m_ZoomLevel;
		Camera.GetComponent<TransformComponent>().m_Transform.SetPosition(m_CameraPosition);
		return false;
	}


	bool EditorLayer::OnMouseMoved(MouseMovedEvent& e)
	{
		FVector2 MousePos = FVector2(e.GetX(), e.GetY());
		FVector2 DeltaMousePos = MousePos - m_OldMousePos;
		m_OldMousePos = MousePos;
		DeltaMousePos.Normalize();

		if (m_bMiddleMouseButtonPressed)
		{
			m_CameraPosition.x -= m_CameraSpeed * DeltaMousePos.x * m_DeltaTime;
			m_CameraPosition.y += m_CameraSpeed * DeltaMousePos.y * m_DeltaTime;
			Camera.GetComponent<TransformComponent>().m_Transform.SetPosition(m_CameraPosition);
		}

		if (m_bLeftMouseButtonPressed)
		{
			//ADD ROTATION HERE
		}

		return false;
	}


	bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == BH_MOUSE_BUTTON_MIDDLE)
		{
			m_bMiddleMouseButtonPressed = true;
		}
		else if (e.GetMouseButton() == BH_MOUSE_BUTTON_LEFT)
		{
			m_bLeftMouseButtonPressed = true;
		}

		return false;
	}


	bool EditorLayer::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		if (e.GetMouseButton() == BH_MOUSE_BUTTON_MIDDLE)
		{
			m_bMiddleMouseButtonPressed = false;
		}
		else if (e.GetMouseButton() == BH_MOUSE_BUTTON_LEFT)
		{
			m_bLeftMouseButtonPressed = false;
		}

		return false;
	}

	void EditorLayer::OnDetach()
	{
		BHive::Renderer2D::ShutDown();
	}

}