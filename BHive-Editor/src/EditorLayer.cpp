#include "EditorLayer.h"
#include "ImGui/ImGuiWrappers.h"
#include "ComponentDetails/DetailsCustomization.h"
#include "ComponentDetails/ComponentDetails.h"
#include "EditorClassRegistry.h"

namespace BHive
{ 
	EditorLayer::EditorLayer()
		:Layer("EditorLayer")
	{
		s_Instance = this;
	}


	EditorLayer::~EditorLayer()
	{
	}

	void EditorLayer::OnAttach()
	{
		FrameBufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;

		//Register Component Class Property Details
		EditorClassRegistry::RegisterClassDetails("TransformComponent", Make_Ref<TransformComponentDetails>());
		EditorClassRegistry::RegisterClassDetails("TagComponent", Make_Ref<TagComponentDetails>());
		EditorClassRegistry::RegisterClassDetails("DirectionalLightComponent", Make_Ref<DirectionalLightComponentDetails>());
		EditorClassRegistry::RegisterClassDetails("SpotLightComponent", Make_Ref<SpotLightComponentDetails>());
		EditorClassRegistry::RegisterClassDetails("PointLightComponent", Make_Ref<PointLightComponentDetails>());
		EditorClassRegistry::RegisterClassDetails("CameraComponent", Make_Ref<CameraComponentDetails>());
		EditorClassRegistry::RegisterClassDetails("RenderComponent", Make_Ref<RenderComponentDetails>());
		EditorClassRegistry::RegisterClassDetails("NativeScriptComponent", Make_Ref<NativeScriptComponentDetails>());
		ClassRegistry::RegisterClassName("TransformComponent");
		ClassRegistry::RegisterClassName("TagComponent");
		ClassRegistry::RegisterClassName("DirectionalLightComponent");
		ClassRegistry::RegisterClassName("PointLightComponent");
		ClassRegistry::RegisterClassName("CameraComponent");
		ClassRegistry::RegisterClassName("RenderComponent");
		ClassRegistry::RegisterClassName("NativeScriptComponent");
		EditorClassRegistry::RegisterEditorCustomizationDetailsForAsset("Texture2D", Make_Ref<TextureEditorCustomizationDetails>());
		EditorClassRegistry::RegisterEditorCustomizationDetailsForAsset("Material", Make_Ref<MaterialEditorCustomizationDetails>());
		EditorClassRegistry::RegisterEditorCustomizationDetailsForAsset("Mesh", Make_Ref<MeshEditorCustomizationDetails>());
		EditorClassRegistry::RegisterEditorCustomizationDetailsForAsset("Shader", Make_Ref<ShaderEditorCustomizationDetails>());

		Scene* scene = SceneManager::CreateScene("Default");

		m_Texture = AssetManager::Get<Texture2D>("folder");
		m_Texture2 = AssetManager::Get<Texture2D>("checkermap");

		Ref<PhongMaterial> DMaterial(new PhongMaterial());
		DMaterial->m_Properties.m_DiffuseTexture = AssetManager::Get<Texture2D>("checkermap");
		DMaterial->m_Name = DefaultMaterialName;
		AssetManager::CreateAsset<Material>(DMaterial);

		Ref<PhongMaterial> Material2(new PhongMaterial());
		Material2->m_Name = "Material2";
		AssetManager::CreateAsset<Material>(Material2);

		Ref<PhongMaterial> RedMaterial(new PhongMaterial());
		RedMaterial->m_Name = "RedMaterial";
		RedMaterial->m_Properties.m_Diffuse = LinearColor3(1.0, 0.0, 0.0);
		AssetManager::CreateAsset<Material>(RedMaterial);

		Ref<ToonMaterial> toonm = Make_Ref<ToonMaterial>();
		toonm->m_Name = "Toon Material";
		AssetManager::CreateAsset<Material>(toonm);

		Ref<Model> Shotgun	= Model::Import("Import/Meshes/Grenades.obj", false, true);
		AssetManager::Add(Model::Import("Import/Meshes/Shotgun.obj", false, true));
		Import("Import/Meshes/Cube.obj");
		Import("D:/Wallpaper/7_tornado.jpg");
		Import("Import/Textures/container.jpg");
		Import("Import/Textures/grass.png");
		Import("Import/Textures/matrix.jpg");
		Import("Import/Textures/smoke.png");
		Import("D:/Wallpaper/7_tornado.jpg");
		Import("Import/Meshes/Shotgun/SO_SG_Mat_normal.jpeg");
		Import("Import/Meshes/Shotgun/SO_SG_Mat_albedo.jpeg");
		Import("Import/Meshes/Frag1/Frag_1_M_A.png");
		Import("Import/Meshes/Frag2/Frag_2_M_A.png");
		Ref<Texture2D> m_Texture3 = AssetManager::Get<Texture2D>("7_tornado");
		

		Ref<Model> triangle = Renderer2D::Triangle(1.0f, 1.0f);
		Ref<Model> plane	= Renderer2D::Plane(5.0f, 5.0f);
		Ref<Model> lantern	= Model::Import("Import/Meshes/lantern.obj", false, true);

		AssetManager::Add(triangle);
		AssetManager::Add(plane);
		AssetManager::Add(Shotgun);
		AssetManager::Add(lantern);
		
		actor0 = scene->CreateEntity("Shotgun");
		actor0.AddComponent<RenderComponent>();
	
		auto& renderComponent = actor0.GetComponent<RenderComponent>();
		renderComponent.m_Model = Shotgun;

		tri = scene->CreateEntity("Triangle");
		tri.AddComponent<RenderComponent>();

		auto& renderComponent1 = tri.GetComponent<RenderComponent>();
		renderComponent1.m_Model = triangle;

		pl = scene->CreateEntity("Plane");
		auto& rendercomponent2 = pl.AddComponent<RenderComponent>();
		rendercomponent2.m_Model = AssetManager::Get<Model>("Plane");

		scene->CreateEntity("Directional Light").AddComponent<DirectionalLightComponent>();
		scene->CreateEntity("Directional Light2").AddComponent<DirectionalLightComponent>();

		scene->CreateEntity("Point Light").AddComponent<PointLightComponent>();
		scene->CreateEntity("Point Light2").AddComponent<PointLightComponent>();

		SceneManager::SetActiveScene("Default");
		Renderer2D::Init();

		m_Viewport = Make_Ref<Viewport>(fbSpec, SceneManager::GetActiveScene());
	
		m_ViewportPanel = new ViewportPanel(std::string("MainViewport"), m_Viewport);
		m_SceneHierarchyPanel = new SceneHierarchyPanel(SceneManager::GetActiveScene());
		m_AssetBrowserPanel = new AssetBrowserPanel(0 , ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_HorizontalScrollbar);

		OpenPanel(m_ViewportPanel);
		OpenPanel(m_SceneHierarchyPanel);
		OpenPanel(m_AssetBrowserPanel);
	}

	void EditorLayer::OnUpdate(const Time& time)
	{
		BH_PROFILE_FUNCTION();

		m_Viewport->OnUpdate(time);
		//m_Viewport2->OnUpdate(time);
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
		
		size_t size = m_EditorStack.size();
		for (uint32 i = 0; i < size; i++)
		{
			m_EditorStack[i]->OnRender();

			if (!m_EditorStack[i]->m_isOpen)
			{
				m_EditorStack.ClosePanel(i);
			}
		}

		//ImGui::ShowDemoWindow();

		//End Dockspace
		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{	
		/*EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_ONE_PARAM(EditorLayer::OnMouseScrolled));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_ONE_PARAM(EditorLayer::OnMouseMoved));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_ONE_PARAM(EditorLayer::OnMouseButtonPressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_ONE_PARAM(EditorLayer::OnMouseButtonReleased));*/
	}


	void EditorLayer::OpenPanel(ImGuiPanel* panel)
	{
		m_EditorStack.OpenPanel(panel);
	}

	/*bool EditorLayer::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ViewportPanel->OnMouseScrolled(e);
		return false;
	}

	bool EditorLayer::OnMouseMoved(MouseMovedEvent& e)
	{
		m_ViewportPanel->OnMouseMoved(e);

		return false;
	}

	bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		m_ViewportPanel->OnMouseButtonPressed(e);
		
		return false;
	}

	bool EditorLayer::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		m_ViewportPanel->OnMouseButtonReleased(e);

		return false;
	}*/

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

	EditorLayer* EditorLayer::s_Instance;

	void EditorLayer::OnDetach()
	{
		if(SceneManager::GetActiveScene())
			SceneManager::GetActiveScene()->OnEnd();

		Renderer2D::ShutDown();
	}

}