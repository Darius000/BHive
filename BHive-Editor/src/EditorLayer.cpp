#include "EditorLayer.h"
#include "ImGui/ImGuiWrappers.h"
#include "ComponentDetails/DetailsCustomization.h"
#include "ComponentDetails/ComponentDetails.h"
#include "EditorClassRegistry.h"
#include "Factory/Factory.h"
#include "BHive/Components/Component.h"
#include "Editors/EditorStack.h"


namespace BHive
{ 

	class MoveCubeScript : public ScriptEntity
	{
	public:
		MoveCubeScript() = default;

		void OnCreate()
		{
			GetComponent<TransformComponent>().m_Transform.SetRotation(0.0f, 0.0f, 0.0f);
		}

		void OnUpdate(const Time& time)
		{
			auto& transform = GetComponent<TransformComponent>().m_Transform;
			auto pos = transform.GetPosition();
			auto forw = transform.GetForward();
			pos += forw * 1.0f * time.GetDeltaTime();
			transform.SetPosition(pos);
		}
	};

	EditorLayer::EditorLayer()
		:Layer("EditorLayer")
	{
		//s_Instance = this;
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
		EditorClassRegistry::RegisterEditorCustomizationDetailsForAsset("Model", Make_Ref<MeshEditorCustomizationDetails>());
		EditorClassRegistry::RegisterEditorCustomizationDetailsForAsset("Shader", Make_Ref<ShaderEditorCustomizationDetails>());
		EditorClassRegistry::RegisterEditorCustomizationDetailsForAsset("FontFamily", Make_Ref<FontEditorCustomizationDetails>());

		Scene* scene = SceneManager::CreateScene("Default");

		m_Texture = AssetManager::Get<Texture2D>("folder");
		m_Texture2 = AssetManager::Get<Texture2D>("checkermap");


		AssetManager::CreateAsset<Material>(DefaultMaterialName, AssetManager::Get<Shader>("BlinnPhong"));
		AssetManager::CreateAsset<Material>("Material2", AssetManager::Get<Shader>("BlinnPhong"));
		AssetManager::CreateAsset<Material>("Toon Mat Test", AssetManager::Get<Shader>("Toon"));

		std::array<WinPath, 6> faces = 
		{
			"Import/skybox/right.jpg",
			"Import/skybox/left.jpg",
			"Import/skybox/top.jpg",
			"Import/skybox/bottom.jpg",
			"Import/skybox/front.jpg",
			"Import/skybox/back.jpg"
		};

		//CubeMap
		AssetManager::Add<CubeTexture>("Cube Map", CubeTexture::Create(faces));
		AssetManager::CreateAsset<Material>("CubeMapMaterial", AssetManager::Get<Shader>("CubeMap"));

		Import("Import/Meshes/Cube.obj");
		Import("Import/Meshes/CubeFlipped.obj");
		Import("Import/Textures/container.jpg");
		Import("Import/Textures/grass.png");
		Import("Import/Textures/matrix.jpg");
		Import("Import/Textures/smoke.png");
		Import("Import/Meshes/Shotgun/SO_SG_Mat_normal.jpeg");
		Import("Import/Meshes/Shotgun/SO_SG_Mat_albedo.jpeg");
		Import("Import/Meshes/Frag1/Frag_1_M_A.png");
		Import("Import/Meshes/Frag2/Frag_2_M_A.png");
		Import("Import/Meshes/lantern.obj");
		Import("Import/Meshes/Grenades.obj");
		Import("Import/Meshes/Shotgun.obj");

		AssetManager::Add("Triangle" , Renderer2D::Triangle(1.0f, 1.0f));
		AssetManager::Add("Plane" , Renderer2D::Plane(5.0f, 5.0f));

		actor0 = scene->CreateEntity("Shotgun");

		tri = scene->CreateEntity("Triangle");
		tri.AddComponent<RenderComponent>();

		auto& renderComponent1 = tri.GetComponent<RenderComponent>();
		renderComponent1.m_Model = AssetManager::Get<Model>("Triangle");

		pl = scene->CreateEntity("Plane");
		auto& rendercomponent2 = pl.AddComponent<RenderComponent>();
		rendercomponent2.m_Model = AssetManager::Get<Model>("Cube");
		auto& script = pl.AddComponent<NativeScriptComponent>();
		script.Bind<MoveCubeScript>();

		scene->CreateEntity("Directional Light").AddComponent<DirectionalLightComponent>();

		scene->CreateEntity("Point Light").AddComponent<PointLightComponent>();

		SceneManager::SetActiveScene("Default");
		Renderer2D::Init();

		m_Viewport = Make_Ref<Viewport>(fbSpec, SceneManager::GetActiveScene());
	
		//Open the default panels
		EditorStack::Get()->OpenPanel<ViewportPanel>(std::string("MainViewport"), m_Viewport);
		EditorStack::Get()->OpenPanel<SceneHierarchyPanel>(SceneManager::GetActiveScene());
		EditorStack::Get()->OpenPanel<AssetBrowserPanel>(0, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_HorizontalScrollbar);
		EditorStack::Get()->OpenPanel<PropertiesPanel>();
	}

	void EditorLayer::OnUpdate(const Time& time)
	{
		BH_PROFILE_FUNCTION();

		m_Viewport->OnUpdate(time);
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
		if (opt_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockSpaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Dockspace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float windowMinSize = style.WindowMinSize.x;
		style.WindowMinSize.x = 150.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
		}

		style.WindowMinSize.x = windowMinSize;

		DisplayMenuBar();
		
		EditorStack::Get()->Update();

		if(b_ShowDemoWindow) ImGui::ShowDemoWindow(&b_ShowDemoWindow);
		
		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{	
		EditorStack::Get()->ExecutePanelEvents(event);
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
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Renderer"))
			{
				if(ImGui::MenuItem("Enable Back Face Culling")) RenderCommands::SetEnableBackfaceCulling(true);
				if(ImGui::MenuItem("Disable Back Face Culling")) RenderCommands::SetEnableBackfaceCulling(false);

				ImGui::EndMenu();
			}


			//Window Views
			if (ImGui::BeginMenu("View"))
			{
				if (ImGui::MenuItem("Viewport")) 
					EditorStack::Get()->OpenPanel<ViewportPanel>("Viewport", m_Viewport);

				if (ImGui::MenuItem("Hierarchy")) 
					EditorStack::Get()->OpenPanel<SceneHierarchyPanel>(SceneManager::GetActiveScene());
				
				if (ImGui::MenuItem("Content Browser"))
					EditorStack::Get()->OpenPanel<AssetBrowserPanel>();

				if (ImGui::MenuItem("Properties"))
					EditorStack::Get()->OpenPanel<PropertiesPanel>();

				if (ImGui::MenuItem("ImGui Demo Window"))
					b_ShowDemoWindow = true;

				ImGui::EndMenu();
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