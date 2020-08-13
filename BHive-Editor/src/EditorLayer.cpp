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

		

		m_Texture = BHive::TextureManager::Get("folder");
		m_Texture2 = BHive::TextureManager::Get("checkermap");

		Camera = scene->CreateEntity("Camera");
		Camera.AddComponent<CameraComponent>();
		Camera.GetComponent<CameraComponent>().m_Camera.SetPerspective({35.0f, .01f, 1000.0f});

		Camera2 = scene->CreateEntity("Camera2");
		Camera2.AddComponent<CameraComponent>();
		Camera2.GetComponent<CameraComponent>().m_Camera.SetOrthographic({1.0f, -1.0f, 1.0f});


		Ref<Model> Shotgun	= Model::Import("Import/Meshes/Shotgun/Shotgun.obj");
		Ref<Material> material = Shotgun->GetMesh(0)->GetMaterial();
		dynamic_cast<PhongMaterial*>(material.get())->m_DiffuseTexture = TextureManager::Get("SO_SG_Mat_albedo");
		Ref<Model> triangle = Renderer2D::Triangle(1.0f, 1.0f);
		Ref<Model> plane	= Renderer2D::Plane(5.0f, 5.0f);
		Ref<Model> lantern	= Model::Import("Import/Meshes/lantern.obj");
		
		actor0 = scene->CreateEntity("Shotgun");
		actor0.AddComponent<RenderComponent>();
	
		auto& renderComponent = actor0.GetComponent<RenderComponent>();
		renderComponent.m_Model = triangle;
		//renderComponent.m_Model->GetMesh(0)->GetMaterial()->m_Texture = m_Texture2;
		//renderComponent.m_Model->GetMesh(0)->SetMaterial(Ref<PhongMaterial>(new PhongMaterial()));
			
		tri = scene->CreateEntity("Triangle");
		tri.AddComponent<RenderComponent>();

		auto& renderComponent1 = tri.GetComponent<RenderComponent>();
		renderComponent1.m_Model = Shotgun;
		//renderComponent1.m_Model->GetMaterial()->m_Texture = m_Texture2;
	
		pl = scene->CreateEntity("Plane");
		auto& rendercomponent2 = pl.AddComponent<RenderComponent>();
		rendercomponent2.m_Model = plane;
		plane->GetMesh(0)->SetMaterial(Ref<GridMaterial>(new GridMaterial()));
		//rendercomponent2.m_Model->GetMesh(0)->GetMaterial()->m_Texture = m_Texture2;
	
		Light = scene->CreateEntity("Directional Light");
		Light.AddComponent<DirectionalLightComponent>();
		//Light.AddComponent<NativeScriptComponent>().Bind<Player>();

		SceneManager::SetActiveScene("Default");
		Renderer2D::Init();
	}

	void EditorLayer::OnUpdate(const Time& time)
	{
		BH_PROFILE_FUNCTION();

		m_Framebuffer->Bind();

		m_DeltaTime = time.GetDeltaTime();

		Renderer2D::Begin();	
		SceneManager::GetActiveScene()->OnUpdate(time);		
		Renderer2D::End();

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

		DisplayEditorLayout();

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
		if (e.GetMouseButton() == MouseButton::Middle)
		{
			m_bMiddleMouseButtonPressed = true;
		}
		else if (e.GetMouseButton() == MouseButton::Left)
		{
			m_bLeftMouseButtonPressed = true;
		}

		return false;
	}


	bool EditorLayer::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		if (e.GetMouseButton() == MouseButton::Middle)
		{
			m_bMiddleMouseButtonPressed = false;
		}
		else if (e.GetMouseButton() == MouseButton::Last)
		{
			m_bLeftMouseButtonPressed = false;
		}

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
				if (ImGui::MenuItem("Style Customization Window")) showStyleEditor = true;
				if (ImGui::MenuItem("Content Browser")) showContentBrowser = true;
				if (ImGui::MenuItem("Viewport")) showViewport = true;
				if (ImGui::MenuItem("Details Panel")) showDetailsPanel = true;
				if (ImGui::MenuItem("Show ImGui Demo Window")) showDemoWindow = true;

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Renderer"))
			{
				if(ImGui::MenuItem("Enable Back Face Culling")) RenderCommands::SetEnableBackfaceCulling(true);
				if(ImGui::MenuItem("Disable Back Face Culling")) RenderCommands::SetEnableBackfaceCulling(false);

				ImGui::EndMenu();
			}

			uint32 playbuttonID = TextureManager::Get("back")->GetRendererID();
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


	void EditorLayer::DisplayViewPort(bool* IsOpen)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0});
		ImGui::Begin("Viewport", IsOpen);
			
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(m_ViewportFocused && m_ViewportHovered);
		if ((!m_ViewportFocused || !m_ViewportHovered) && (m_bLeftMouseButtonPressed || m_bMiddleMouseButtonPressed))
		{
			m_bLeftMouseButtonPressed = false;
			m_bMiddleMouseButtonPressed = false;
		}

		if (m_ViewportSize != *((FVector2*)&viewportPanelSize) && viewportPanelSize.x > 0 && viewportPanelSize.y > 0)
		{

			m_Framebuffer->Resize((uint32)viewportPanelSize.x, (uint32)viewportPanelSize.y);
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
			SceneManager::GetActiveScene()->OnViewportResize((uint32)m_ViewportSize.x, (uint32)m_ViewportSize.y);
		}

		uint32 textureID = m_Framebuffer->GetColorAttachmentRendererID();

		ImGui::Image((void*)textureID, ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));

		
		ImGui::End();
		ImGui::PopStyleVar();
	}

	void EditorLayer::DisplayContentBrowser(bool* IsOpen)
	{
		//Content Browser NOTE: Textures for now
		if (ImGui::Begin("Content Browser", IsOpen, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_HorizontalScrollbar))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(100.0f, 50.0f));
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 1.0f, 0.5f, 1.0f));
			if (ImGui::BeginMenuBar())
			{
		
				if (ImGui::Button("Import"))
				{
					showFileBrowser = true;
				}
				
				
				ImGui::EndMenuBar();
				
			}
			ImGui::PopStyleColor(1);
			ImGui::PopStyleVar(ImGuiStyleVar_WindowPadding);

			ImVec2 ContentBrowserSize = ImGui::GetContentRegionAvail();
			int32 RowSize = (int32)ContentBrowserSize.x / 120;
			int32 i = -1;
			for (auto& texture : TextureManager::GetAssets())
			{
				i++;
				if (i <= RowSize) ImGui::SameLine();
				if (i > RowSize) i = 0;
				ImGui::PushID(i);
				ImGui::Image((void*)texture.second->GetRendererID(), ImVec2(100.0f, 100.0f), ImVec2(0, 1), ImVec2(1, 0));
				if (ImGui::BeginPopupContextItem("Asset Popup"))
				{
					if (ImGui::MenuItem("Edit"))
					{
						TextureEditorLayer::ShowEditor(texture.second);
					}

					ImGui::EndPopup();
				}
				ImGui::PopID();
			}
		}

		ImGui::End();
	}


	void EditorLayer::DisplayStyleEditor(bool* IsOpen)
	{		
		if (ImGui::Begin("Style Editor##Editor", IsOpen))
		{
			ImGui::ShowStyleEditor();
			ImGui::End();
		}
	}


	void EditorLayer::DisplayDetailsPanel(bool* IsOpen)
	{
		ImGui::Begin("Details Panel", IsOpen);

		ImGui::End();
	}

	void EditorLayer::DisplayEditorLayout()
	{
		DisplayMenuBar(); // Always shown
		if(showViewport) DisplayViewPort(&showViewport);
		if(showContentBrowser) DisplayContentBrowser(&showContentBrowser);
		if(showStyleEditor) DisplayStyleEditor(&showStyleEditor);
		if(showDetailsPanel) DisplayDetailsPanel(&showDetailsPanel);
		if(showDemoWindow) ImGui::ShowDemoWindow(&showDemoWindow);
		if(showFileBrowser) DisplayFileDialogBrowser("File Browser", &showFileBrowser, WinPath("..\\BHive\\Assets"));
		if(showNodeEditor) DisplayNodeEditor(&showNodeEditor);
	}


	void EditorLayer::DisplayNodeEditor(bool* IsOpen)
	{

		ImGui::SetNextWindowSize(ImVec2(700, 600), ImGuiCond_FirstUseEver);
		if (!ImGui::Begin("Example: Custom Node Graph", IsOpen))
		{
			ImGui::End();
			return;
		}

		// Dummy
		struct Node
		{
			int     ID;
			char    Name[32];
			ImVec2  Pos, Size;
			float   Value;
			ImVec4  Color;
			int     InputsCount, OutputsCount;

			Node(int id, const char* name, const ImVec2& pos, float value, const ImVec4& color, int inputs_count, int outputs_count) { ID = id; strcpy(Name, name); Pos = pos; Value = value; Color = color; InputsCount = inputs_count; OutputsCount = outputs_count; }

			ImVec2 GetInputSlotPos(int slot_no) const { return ImVec2(Pos.x, Pos.y + Size.y * ((float)slot_no + 1) / ((float)InputsCount + 1)); }
			ImVec2 GetOutputSlotPos(int slot_no) const { return ImVec2(Pos.x + Size.x, Pos.y + Size.y * ((float)slot_no + 1) / ((float)OutputsCount + 1)); }
		};
		struct NodeLink
		{
			int     InputIdx, InputSlot, OutputIdx, OutputSlot;

			NodeLink(int input_idx, int input_slot, int output_idx, int output_slot) { InputIdx = input_idx; InputSlot = input_slot; OutputIdx = output_idx; OutputSlot = output_slot; }
		};

		// State
		static ImVector<Node> nodes;
		static ImVector<NodeLink> links;
		static ImVec2 scrolling = ImVec2(0.0f, 0.0f);
		static bool inited = false;
		static bool show_grid = true;
		static int node_selected = -1;

		// Initialization
		ImGuiIO& io = ImGui::GetIO();
		if (!inited)
		{
			nodes.push_back(Node(0, "MainTex", ImVec2(40, 50), 0.5f, ImColor(255, 100, 100), 1, 1));
			nodes.push_back(Node(1, "BumpMap", ImVec2(40, 150), 0.42f, ImColor(200, 100, 200), 1, 1));
			nodes.push_back(Node(2, "Combine", ImVec2(270, 80), 1.0f, ImColor(0, 200, 100), 2, 2));
			links.push_back(NodeLink(0, 0, 2, 0));
			links.push_back(NodeLink(1, 0, 2, 1));
			inited = true;
		}

		// Draw a list of nodes on the left side
		bool open_context_menu = false;
		int node_hovered_in_list = -1;
		int node_hovered_in_scene = -1;
		ImGui::BeginChild("node_list", ImVec2(100, 0));
		ImGui::Text("Nodes");
		ImGui::Separator();
		for (int node_idx = 0; node_idx < nodes.Size; node_idx++)
		{
			Node* node = &nodes[node_idx];
			ImGui::PushID(node->ID);
			if (ImGui::Selectable(node->Name, node->ID == node_selected))
				node_selected = node->ID;
			if (ImGui::IsItemHovered())
			{
				node_hovered_in_list = node->ID;
				open_context_menu |= ImGui::IsMouseClicked(1);
			}
			ImGui::PopID();
		}
		ImGui::EndChild();

		ImGui::SameLine();
		ImGui::BeginGroup();

		const float NODE_SLOT_RADIUS = 4.0f;
		const ImVec2 NODE_WINDOW_PADDING(8.0f, 8.0f);

		// Create our child canvas
		ImGui::Text("Hold middle mouse button to scroll (%.2f,%.2f)", scrolling.x, scrolling.y);
		ImGui::SameLine(ImGui::GetWindowWidth() - 100);
		ImGui::Checkbox("Show grid", &show_grid);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(60, 60, 70, 200));
		ImGui::BeginChild("scrolling_region", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);
		ImGui::PopStyleVar(); // WindowPadding
		ImGui::PushItemWidth(120.0f);

		const ImVec2 offset = ImGui::GetCursorScreenPos() + scrolling;
		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		// Display grid
		if (show_grid)
		{
			ImU32 GRID_COLOR = IM_COL32(200, 200, 200, 40);
			float GRID_SZ = 64.0f;
			ImVec2 win_pos = ImGui::GetCursorScreenPos();
			ImVec2 canvas_sz = ImGui::GetWindowSize();
			for (float x = fmodf(scrolling.x, GRID_SZ); x < canvas_sz.x; x += GRID_SZ)
				draw_list->AddLine(ImVec2(x, 0.0f) + win_pos, ImVec2(x, canvas_sz.y) + win_pos, GRID_COLOR);
			for (float y = fmodf(scrolling.y, GRID_SZ); y < canvas_sz.y; y += GRID_SZ)
				draw_list->AddLine(ImVec2(0.0f, y) + win_pos, ImVec2(canvas_sz.x, y) + win_pos, GRID_COLOR);
		}

		// Display links
		draw_list->ChannelsSplit(2);
		draw_list->ChannelsSetCurrent(0); // Background
		for (int link_idx = 0; link_idx < links.Size; link_idx++)
		{
			NodeLink* link = &links[link_idx];
			Node* node_inp = &nodes[link->InputIdx];
			Node* node_out = &nodes[link->OutputIdx];
			ImVec2 p1 = offset + node_inp->GetOutputSlotPos(link->InputSlot);
			ImVec2 p2 = offset + node_out->GetInputSlotPos(link->OutputSlot);
			draw_list->AddBezierCurve(p1, p1 + ImVec2(+50, 0), p2 + ImVec2(-50, 0), p2, IM_COL32(200, 200, 100, 255), 3.0f);
		}

		// Display nodes
		for (int node_idx = 0; node_idx < nodes.Size; node_idx++)
		{
			Node* node = &nodes[node_idx];
			ImGui::PushID(node->ID);
			ImVec2 node_rect_min = offset + node->Pos;

			// Display node contents first
			draw_list->ChannelsSetCurrent(1); // Foreground
			bool old_any_active = ImGui::IsAnyItemActive();
			ImGui::SetCursorScreenPos(node_rect_min + NODE_WINDOW_PADDING);
			ImGui::BeginGroup(); // Lock horizontal position
			ImGui::Text("%s", node->Name);
			ImGui::SliderFloat("##value", &node->Value, 0.0f, 1.0f, "Alpha %.2f");
			ImGui::ColorEdit3("##color", &node->Color.x);
			ImGui::EndGroup();

			// Save the size of what we have emitted and whether any of the widgets are being used
			bool node_widgets_active = (!old_any_active && ImGui::IsAnyItemActive());
			node->Size = ImGui::GetItemRectSize() + NODE_WINDOW_PADDING + NODE_WINDOW_PADDING;
			ImVec2 node_rect_max = node_rect_min + node->Size;

			// Display node box
			draw_list->ChannelsSetCurrent(0); // Background
			ImGui::SetCursorScreenPos(node_rect_min);
			ImGui::InvisibleButton("node", node->Size);
			if (ImGui::IsItemHovered())
			{
				node_hovered_in_scene = node->ID;
				open_context_menu |= ImGui::IsMouseClicked(1);
			}
			bool node_moving_active = ImGui::IsItemActive();
			if (node_widgets_active || node_moving_active)
				node_selected = node->ID;
			if (node_moving_active && ImGui::IsMouseDragging(0))
				node->Pos = node->Pos + io.MouseDelta;

			ImU32 node_bg_color = (node_hovered_in_list == node->ID || node_hovered_in_scene == node->ID || (node_hovered_in_list == -1 && node_selected == node->ID)) ? IM_COL32(75, 75, 75, 255) : IM_COL32(60, 60, 60, 255);
			draw_list->AddRectFilled(node_rect_min, node_rect_max, node_bg_color, 4.0f);
			draw_list->AddRect(node_rect_min, node_rect_max, IM_COL32(100, 100, 100, 255), 4.0f);
			for (int slot_idx = 0; slot_idx < node->InputsCount; slot_idx++)
				draw_list->AddCircleFilled(offset + node->GetInputSlotPos(slot_idx), NODE_SLOT_RADIUS, IM_COL32(150, 150, 150, 150));
			for (int slot_idx = 0; slot_idx < node->OutputsCount; slot_idx++)
				draw_list->AddCircleFilled(offset + node->GetOutputSlotPos(slot_idx), NODE_SLOT_RADIUS, IM_COL32(150, 150, 150, 150));

			ImGui::PopID();
		}
		draw_list->ChannelsMerge();

		// Open context menu
		if (ImGui::IsMouseReleased(1))
			if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup) || !ImGui::IsAnyItemHovered())
			{
				node_selected = node_hovered_in_list = node_hovered_in_scene = -1;
				open_context_menu = true;
			}
		if (open_context_menu)
		{
			ImGui::OpenPopup("context_menu");
			if (node_hovered_in_list != -1)
				node_selected = node_hovered_in_list;
			if (node_hovered_in_scene != -1)
				node_selected = node_hovered_in_scene;
		}

		// Draw context menu
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));
		if (ImGui::BeginPopup("context_menu"))
		{
			Node* node = node_selected != -1 ? &nodes[node_selected] : NULL;
			ImVec2 scene_pos = ImGui::GetMousePosOnOpeningCurrentPopup() - offset;
			if (node)
			{
				ImGui::Text("Node '%s'", node->Name);
				ImGui::Separator();
				if (ImGui::MenuItem("Rename..", NULL, false, false)) {}
				if (ImGui::MenuItem("Delete", NULL, false, false)) {}
				if (ImGui::MenuItem("Copy", NULL, false, false)) {}
			}
			else
			{
				if (ImGui::MenuItem("Add")) { nodes.push_back(Node(nodes.Size, "New node", scene_pos, 0.5f, ImColor(100, 100, 200), 2, 2)); }
				if (ImGui::MenuItem("Paste", NULL, false, false)) {}
			}
			ImGui::EndPopup();
		}
		ImGui::PopStyleVar();

		// Scrolling
		if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging(2, 0.0f))
			scrolling = scrolling + io.MouseDelta;

		ImGui::PopItemWidth();
		ImGui::EndChild();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::EndGroup();

		ImGui::End();
	}

	void EditorLayer::DisplayFileDialogBrowser(const char* label, bool* IsOpen, WinPath& startDir)
	{
		ImGui::Begin(label, IsOpen, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize);
		ImGui::BeginChild("Files", ImVec2(500,200), true, ImGuiWindowFlags_HorizontalScrollbar);
		auto& it = fs::directory_iterator(*startDir);

		if (it->exists())
		{
			static int index = 0;
			for (auto& item : it)
			{
				WinPath subPath(item.path().string().c_str());
				if (ImGui::Selectable(subPath.GetName(), index))
				{
					bool bIsDirectory = subPath.IsDirectory();
				}
			}
		}

		ImGui::EndChild();
		ImGui::BeginChild("File Path", ImVec2(500, 75), true);
		ImGui::Columns(2);
		static char buffer[256] = "";
		ImGui::Text("File"); ImGui::SameLine();
		ImGui::InputText("", buffer, IM_ARRAYSIZE(buffer));
		ImGui::NextColumn();
		static int item = 0;
		const char* exts = "All";
		ImGui::Combo("", &item, exts);
		ImGui::Button("Open"); ImGui::SameLine();
		if(ImGui::Button("Cancel")) { showFileBrowser = false; }
		ImGui::EndChild();

		ImGui::End();
	}

	void EditorLayer::OnDetach()
	{
		if(SceneManager::GetActiveScene())
			SceneManager::GetActiveScene()->OnEnd();

		BHive::Renderer2D::ShutDown();
	}

}