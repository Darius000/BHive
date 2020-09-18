#include "EditorLayer.h"
#include "Editors/TextureEditor.h"
#include "ImGui/ImGuiWrappers.h"
#include "BHive/Core/ComponentDetails/DetailsCustomization.h"
#include "BHive/Core/ComponentDetails/ComponentDetails.h"

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

		//Register Component Class Property Details
		ClassPropertyRegistry::RegisterClassDetails("TransformComponent", MakeInstance<TransformComponentDetails>());
		ClassPropertyRegistry::RegisterClassDetails("TagComponent", MakeInstance<TagComponentDetails>());
		ClassPropertyRegistry::RegisterClassDetails("DirectionalLightComponent", MakeInstance<DirectionalLightComponentDetails>());
		ClassPropertyRegistry::RegisterClassDetails("SpotLightComponent", MakeInstance<SpotLightComponentDetails>());
		ClassPropertyRegistry::RegisterClassDetails("PointLightComponent", MakeInstance<PointLightComponentDetails>());
		ClassPropertyRegistry::RegisterClassDetails("CameraComponent", MakeInstance<CameraComponentDetails>());
		ClassPropertyRegistry::RegisterClassDetails("RenderComponent", MakeInstance<RenderComponentDetails>());

		Scene* scene = SceneManager::CreateScene("Default");
		Scene* scene2 = SceneManager::CreateScene("New Scene");

		m_Texture = AssetManager::Get<Texture2D>("folder");
		m_Texture2 = AssetManager::Get<Texture2D>("checkermap");

		//m_Camera = scene->CreateEntity("Camera");
		//m_Camera.AddComponent<CameraComponent>();
		//m_Camera.GetComponent<CameraComponent>().m_Camera.SetPerspective({35.0f, .01f, 1000.0f});

		/*Camera2 = scene->CreateEntity("Camera2");
		Camera2.AddComponent<CameraComponent>();
		Camera2.GetComponent<CameraComponent>().m_Camera.SetOrthographic({1.0f, -1.0f, 1.0f});*/

		Ref<Model> Shotgun	= Model::Import("Import/Meshes/Grenades.obj", false);
		Import("D:/Wallpaper/7_tornado.jpg");
		Ref<Texture2D> m_Texture3 = AssetManager::Get<Texture2D>("7_tornado");
		//Ref<Material> material = Shotgun->GetMesh(0)->GetMaterial();
		//dynamic_cast<PhongMaterial*>(material.get())->m_DiffuseTexture = TextureManager::Get("SO_SG_Mat_albedo");
		Ref<Model> triangle = Renderer2D::Triangle(1.0f, 1.0f);
		Ref<Model> plane	= Renderer2D::Plane(5.0f, 5.0f);
		//Ref<Model> lantern	= Model::Import("Import/Meshes/lantern.obj");

		AssetManager::Add<Model>(triangle);
		AssetManager::Add<Model>(plane);
		AssetManager::Add<Model>(Shotgun);
		
		actor0 = scene2->CreateEntity("Shotgun");
		actor0.AddComponent<RenderComponent>();
	
		auto& renderComponent = actor0.GetComponent<RenderComponent>();
		renderComponent.m_Model = Shotgun;
		//renderComponent.m_Model->GetMesh(0)->GetMaterial()->m_Texture = m_Texture2;
		renderComponent.m_Model->GetMesh(0)->SetMaterial(Ref<PhongMaterial>(new PhongMaterial()));
			
		tri = scene->CreateEntity("Triangle");
		tri.AddComponent<RenderComponent>();

		auto& renderComponent1 = tri.GetComponent<RenderComponent>();
		renderComponent1.m_Model = triangle;
		//renderComponent1.m_Model->GetMaterial()->m_Texture = m_Texture2;
	
		pl = scene->CreateEntity("Plane");
		auto& rendercomponent2 = pl.AddComponent<RenderComponent>();
		rendercomponent2.m_Model = plane;
		//plane->GetMesh(0)->SetMaterial(Make_Ref<GridMaterial>());
		//rendercomponent2.m_Model->GetMesh(0)->GetMaterial()->m_Texture = m_Texture2;
	
		Light = scene->CreateEntity("Directional Light");
		Light.AddComponent<DirectionalLightComponent>();
		//Light.AddComponent<NativeScriptComponent>().Bind<Player>();

		Entity PointLight = scene->CreateEntity("Point Light");
		PointLight.AddComponent<PointLightComponent>();

		Entity PointLight2 = scene->CreateEntity("Point Light2");
		PointLight2.AddComponent<PointLightComponent>();

		Entity SpotLight = scene->CreateEntity("Spot Light");
		SpotLight.AddComponent<SpotLightComponent>();


		SceneManager::SetActiveScene("Default");
		Renderer2D::Init();

		m_Viewport = new Viewport(fbSpec, SceneManager::GetActiveScene());
		

		m_ViewportPanel = new ViewportPanel("MainViewport", m_Viewport);
		m_SceneHierarchyPanel = new SceneHierarchyPanel(SceneManager::GetActiveScene());
		m_AssetBrowserPanel = new AssetBrowserPanel(0 , ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_HorizontalScrollbar);
		//m_StyleEditorPanel = new StyleEditorPanel();
		//m_DemoWindowPanel = new DemoWindowPanel();

		FrameBufferSpecification spec2;
		spec2.Width = 800;
		spec2.Height = 600;
		m_Viewport2 = new Viewport(spec2, scene2);
		m_ViewportPanel2 = new ViewportPanel("ViewPort2", m_Viewport2);

		
	}

	void EditorLayer::OnUpdate(const Time& time)
	{
		BH_PROFILE_FUNCTION();

		m_Viewport->OnUpdate(time);
		m_Viewport2->OnUpdate(time);
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

		DisplayMenuBar();
		EditorStack::OnImGuiRender();

		//End Dockspace
		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{	
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_ONE_PARAM(EditorLayer::OnMouseScrolled));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_ONE_PARAM(EditorLayer::OnMouseMoved));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_ONE_PARAM(EditorLayer::OnMouseButtonPressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_ONE_PARAM(EditorLayer::OnMouseButtonReleased));
	}

	bool EditorLayer::OnMouseScrolled(MouseScrolledEvent& e)
	{
		//m_ViewportPanel->OnMouseScrolled(e);
		return false;
	}

	bool EditorLayer::OnMouseMoved(MouseMovedEvent& e)
	{
		//m_ViewportPanel->OnMouseMoved(e);

		return false;
	}

	bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		//m_ViewportPanel->OnMouseButtonPressed(e);
		
		return false;
	}

	bool EditorLayer::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		//m_ViewportPanel->OnMouseButtonReleased(e);

		return false;
	}

	void EditorLayer::DisplayMenuBar()
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File##Editor"))
			{
				if (ImGui::MenuItem("Exit##Editor")) BHive::Application::Get().Close();

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View"))
			{
				//if (ImGui::MenuItem("Style Customization Window")) m_ShowStyleEditor = true;
				//if (ImGui::MenuItem("Content Browser")) m_ShowContentBrowser = true;
				//if (ImGui::MenuItem("Viewport")) m_ShowViewport = true;
				//if (ImGui::MenuItem("Details Panel")) m_ShowDetailsPanel = true;
				//if (ImGui::MenuItem("Show ImGui Demo Window")) m_ShowDemoWindow = true;
				//if (ImGui::MenuItem("Show Scene Hierarchy Panel")) m_SceneHierarchyPanel->m_isOpen = true;

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Renderer"))
			{
				if(ImGui::MenuItem("Enable Back Face Culling")) RenderCommands::SetEnableBackfaceCulling(true);
				if(ImGui::MenuItem("Disable Back Face Culling")) RenderCommands::SetEnableBackfaceCulling(false);

				ImGui::EndMenu();
			}

			uint32 playbuttonID = AssetManager::Get<Texture2D>("back")->GetRendererID();
			if (ImGui::Button("play"))
			{

			}
			if (ImGui::Button("pause"))
			{

			}
			if (ImGui::Button("stop"))
			{

			}

			ImGui::EndMenuBar();
		}
	}

	void EditorLayer::OnDetach()
	{
		if(SceneManager::GetActiveScene())
			SceneManager::GetActiveScene()->OnEnd();

		Renderer2D::ShutDown();
	}

}