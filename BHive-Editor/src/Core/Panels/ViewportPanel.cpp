#include "ViewportPanel.h"
#include "imgui_internal.h"
#include "SceneHierarchyPanel.h"
#include "ImGuizmo/ImGuizmo.h"

namespace BHive
{

	ViewportPanel::ViewportPanel(const std::string& label, Ref<Viewport> viewport, uint64 id)
		:ImGuiPanel(label, 0, id), m_Viewport(viewport)
	{

		m_WindowPadding = {0 , 0};
		//m_FramePadding = {0, 0};

		if (viewport && viewport->m_Scene)
		{
			auto& camTransform = viewport->m_Scene->m_DefaultSceneView.m_Transform;
			m_CameraDistance = camTransform.GetPosition().GetMagnitude();
			Yaw = camTransform.GetRotation().yaw;
			Pitch = camTransform.GetRotation().pitch;
		}	
	}	

	void ViewportPanel::OnRenderMenuBar()
	{
		
	}

	void ViewportPanel::OnRenderWindow()
	{		
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

		if (m_ViewportSize != *((FVector2*)&viewportPanelSize) && viewportPanelSize.x > 0 && viewportPanelSize.y > 0)
		{

			m_Viewport->Resize((uint32)viewportPanelSize.x, (uint32)viewportPanelSize.y);
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
			m_Viewport->m_Scene->OnViewportResize((uint32)m_ViewportSize.x, (uint32)m_ViewportSize.y);
		}


		auto FrameBuffer = m_Viewport->m_MultiSampledFrameBuffer;

		float windowWidth = (float)ImGui::GetWindowWidth();
		float windowHeight = (float)ImGui::GetWindowHeight();

		//ImGui::SetCursorPos({0.0f, 0.0f});
		ImGui::BeginGroup();
		ImGui::Image((void*)*FrameBuffer, ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));

		RenderGizmoButtons();
		//Gizmos
		RenderGizmo({ImGui::GetWindowPos().x, ImGui::GetWindowPos().y}, {windowWidth, windowHeight});

		//Settings
		RenderSettingsChildWindow();

		ImGui::EndGroup();

		//Add Button Overlay
		/*ImGui::SetCursorPos({windowWidth - (6 * 16 * 2), 75.0f});
		ImGui::BeginGroup();
		ImGui::PushMultiItemsWidths(6, ImGui::CalcItemWidth());
		if (ImGui::ImageButton((void*)*AssetManager::Get<Texture2D>("selection"), { 16, 16 }))
			m_GizmoType = -1;
		ImGui::SameLine();
		if(ImGui::ImageButton((void*)*AssetManager::Get<Texture2D>("move"), {16, 16}))
			m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
		ImGui::SameLine();
		if(ImGui::ImageButton((void*)*AssetManager::Get<Texture2D>("refresh"), { 16, 16 }))
			m_GizmoType = ImGuizmo::OPERATION::ROTATE;
		ImGui::SameLine();
		if(ImGui::ImageButton((void*)*AssetManager::Get<Texture2D>("scale"), { 16, 16 }))
			m_GizmoType = ImGuizmo::OPERATION::SCALE;
		ImGui::SameLine();
		if (ImGui::ImageButton((void*)*AssetManager::Get<Texture2D>("refresh"), { 16, 16 }))
			m_GizmoMode = ImGuizmo::MODE::LOCAL;
		ImGui::SameLine();
		if (ImGui::ImageButton((void*)*AssetManager::Get<Texture2D>("refresh"), { 16, 16 }))
			m_GizmoMode = ImGuizmo::MODE::WORLD;
		ImGui::PopItemWidth();
		ImGui::EndGroup();*/
	}

	void ViewportPanel::RenderGizmoButtons()
	{
		const ImVec2 padding = {5, 5};
		const ImVec2 buttonSize = ImVec2(30.0f, 30.0f);
		const int32 numButtons = 4;
		const ImVec2 windowSize = ImVec2(buttonSize.x + padding.x * 2.0f, 
			buttonSize.y * numButtons + (padding.y * 2.0f * numButtons));
		const ImVec2 mainWindowpadding = ImGui::GetCurrentWindow()->WindowPadding;

		ImGui::SetCursorPos({ mainWindowpadding.x  + padding.x, m_ViewportSize.y * .5f - (windowSize. y * .5f) });

		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.6f, 0.6f, 0.6f, .8f));
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 2);

		ImGui::BeginChild("Buttons", windowSize,   false);
		
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,0));
		if (ImGui::ImageButton((void*)*AssetManager::Get<Texture2D>("selection"), buttonSize, ImVec2(0, 1), ImVec2(1,0)))
			m_GizmoType = -1;

		if (ImGui::ImageButton((void*)*AssetManager::Get<Texture2D>("move"), buttonSize, ImVec2(0, 1), ImVec2(1, 0)))
			m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;

		if (ImGui::ImageButton((void*)*AssetManager::Get<Texture2D>("refresh"), buttonSize, ImVec2(0, 1), ImVec2(1, 0)))
			m_GizmoType = ImGuizmo::OPERATION::ROTATE;

		if (ImGui::ImageButton((void*)*AssetManager::Get<Texture2D>("scale"), buttonSize, ImVec2(0, 1), ImVec2(1, 0)))
			m_GizmoType = ImGuizmo::OPERATION::SCALE;

		ImGui::PopStyleVar();

		ImGui::EndChild();

		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
	}

	void ViewportPanel::RenderGizmo(const FVector2& windowPos, const FVector2& windowSize)
	{
		Entity SelectedEntity = SceneHierarchyPanel::GetSelectedEntity();
		if (SelectedEntity && m_GizmoType != -1)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();

			ImGuizmo::SetRect(windowPos.x, windowPos.y, windowSize.x, windowSize.y);

			auto cameraTransform = m_Viewport->m_Scene->m_DefaultSceneView.m_Transform;
			const auto& camera = m_Viewport->m_Scene->m_DefaultSceneView.m_Camera;
			glm::mat4 cameraMatrix = cameraTransform.GetMatrix();
			glm::mat4 cameraView = glm::inverse(cameraMatrix);
			const glm::mat4& cameraProjection = camera.GetProjection();

			auto& tc = SelectedEntity.GetComponent<TransformComponent>();
			glm::mat4 transform = tc.m_Transform.GetMatrix();

			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection)
				, (ImGuizmo::OPERATION)m_GizmoType, (ImGuizmo::MODE)m_GizmoMode, glm::value_ptr(transform));

			m_IsUsingGizmo = ImGuizmo::IsUsing();
			if (m_IsUsingGizmo)
			{
				//Take the new transform and get the position, scale and rotation (using quaternions)
				glm::vec3 translation, scale, skew;
				glm::vec4 perspective;
				glm::quat orientation;
				if(glm::decompose(transform, scale, orientation, translation, skew, perspective))
				{ 
					auto angles = glm::eulerAngles(orientation);

					Rotator rotation;
					rotation.roll = MathLibrary::ToDegrees(angles.x);
					rotation.yaw = MathLibrary::ToDegrees(angles.y);
					rotation.pitch = MathLibrary::ToDegrees(angles.z);

					FVector3 newposition = {translation.x, translation.y, translation.z};
					FVector3 newscale = {scale.x, scale.y, scale.z};

					Rotator deltaRotation = rotation - tc.m_Transform.GetRotation();
					Rotator newRotation = tc.m_Transform.GetRotation() + deltaRotation;
					tc.m_Transform = Transform(newposition, newRotation, newscale);		
				}
			}
		}
	}

	void ViewportPanel::RenderSettingsChildWindow()
	{
		auto arrowtexture = AssetManager::Get<Texture2D>("LeftArrow");

		const float maxSize = 400.0f;
		const float collapsebuttonSize = 20.0f;
		static float percentage = 0.0f;
		static bool isCollapsed = true;
		const ImVec2 currentSize = {maxSize * percentage, m_ViewportSize.y * .95f};
		const ImVec2 mainWindowpadding = ImGui::GetCurrentWindow()->WindowPadding;

		ImGui::SetCursorPos({ (m_ViewportSize.x + mainWindowpadding.x) - (currentSize.x + 
			(collapsebuttonSize * (1.0f - percentage) )) ,
			m_ViewportSize.y - (currentSize.y + mainWindowpadding.y) + 10.0f});

		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.0f, 0.0f, 0.0f , 0.0f));

		ImGui::BeginChild("Settings", currentSize, false);
			
		//Draw collapse button image	
		if (ImGui::ImageButton((void*)*arrowtexture, { collapsebuttonSize , collapsebuttonSize },
			{ 0,1 }, { 1,0 }, 0))
		{
			//Start transition 
			percentage = isCollapsed ? 1.0f : 0.0f;
			isCollapsed = !isCollapsed;
		}
	
		//Draw settings window
		ImGui::SetCursorPos(ImVec2(collapsebuttonSize, 0.0f));

		ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_WindowPadding, ImVec2(10,10));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(.1f, .1f, .1f, 1.0f));
		ImGui::BeginChild("Settings##Viewport", ImGui::GetContentRegionAvail(), false, ImGuiWindowFlags_AlwaysUseWindowPadding);
		
		if(ImGui::TreeNodeEx("HDR", ImGuiTreeNodeFlags_OpenOnArrow))
		{ 
			ImGui::Checkbox("Enabled", &m_Viewport->m_HDR);
			ImGui::SliderFloat("Exposure", &m_Viewport->m_Exposure, 0.01f, 1.0f, "%.3f");
			ImGui::TreePop();
		}
		ImGui::Separator();
		
		if (ImGui::TreeNodeEx("Bloom", ImGuiTreeNodeFlags_OpenOnArrow))
		{
			ImGui::Checkbox("Enabled", &m_Viewport->m_Bloom);
			ImGui::TreePop();
		}
		ImGui::Separator();

		if (ImGui::TreeNodeEx("MultiSampling", ImGuiTreeNodeFlags_OpenOnArrow))
		{
			static int samples = (int)m_Viewport->m_NumSamples;
			if(ImGui::InputInt("Samples", &samples))
			{
				m_Viewport->m_NumSamples = (uint32)MathLibrary::Clamp(samples, 0, samples);
			}
			ImGui::TreePop();
		}
		ImGui::Separator();
		
		if (ImGui::TreeNodeEx("Camera", ImGuiTreeNodeFlags_OpenOnArrow))
		{
			ImGui::DragFloat("Pan Speed", &m_PanSpeed);
			ImGui::DragFloat("Zoom Speed", &m_ZoomSpeed);
			ImGui::DragFloat("Orbital Speed", &m_OrbitalSpeed);
			ImGui::TreePop();
		}
		ImGui::Separator();
		if (ImGui::TreeNodeEx("Grid", ImGuiTreeNodeFlags_OpenOnArrow))
		{
			ImGui::DragFloat("Scale", &m_Viewport->m_GridSettings.m_Scale);
			ImGui::ColorEdit4("Color", *m_Viewport->m_GridSettings.m_Color);
			ImGui::TreePop();
		}
		ImGui::Separator();
	
		ImGui::PopStyleVar();

		ImGui::EndChild();
		
		ImGui::PopStyleColor();
			
		ImGui::EndChild();
	
		ImGui::PopStyleColor();
	}

	bool ViewportPanel::OnMouseScrolled(MouseScrolledEvent& e)
	{
		Zoom(e.GetYOffset() * m_ZoomSpeed);
		
		return true;
	}

	bool ViewportPanel::OnMouseMoved(MouseMovedEvent& e)
	{
		if (m_AltPressed)
		{
			auto deltaX = m_OldMousePos.x - e.GetX();
			auto deltaY = e.GetY() - m_OldMousePos.y;

			float percentageX = MathLibrary::Normalize(deltaX, 0.0f, m_ViewportSize.x);
			float percentageY = MathLibrary::Normalize(deltaY, 0.0f, m_ViewportSize.y);

			if (m_bMiddleMouseButtonPressed)
			{
				Pan(percentageX* m_PanSpeed, percentageY * m_PanSpeed);		
			}

			if (m_bLeftMouseButtonPressed)
			{
				//Rotate
				Orbit(percentageX, percentageY );
			}

		}

		m_OldMousePos = FVector2(e.GetX(), e.GetY());

		return true;
	}

	bool ViewportPanel::OnMouseButtonPressed(MouseButtonPressedEvent& e)
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

	bool ViewportPanel::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		if (e.GetMouseButton() == MouseButton::Middle)
		{
			m_bMiddleMouseButtonPressed = false;
		}
		else if (e.GetMouseButton() == MouseButton::Left)
		{
			m_bLeftMouseButtonPressed = false;
		}

		return false;
	}

	bool ViewportPanel::OnKeyPressed(KeyPressedEvent& e)
	{
		KeyCode key = e.GetKeyCode();
		switch(key)
		{
			case KeyCode::Left_alt:
			case KeyCode::Right_alt:
				m_AltPressed = true;
				return false;
			case KeyCode::F:
				FocusOnEntity();
				return true;
		}


		//Gizmo's Hot keys
		if(!m_IsUsingGizmo)
		{ 
			switch (key)
			{
				case KeyCode::Q:
					m_GizmoType = -1;
					return true;
				case KeyCode::W:
					m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
					return true;
				case KeyCode::R:
					m_GizmoType = ImGuizmo::OPERATION::SCALE;
					return true;
				case KeyCode::E:
					m_GizmoType = ImGuizmo::OPERATION::ROTATE;
					return true;
			}	
		}

		return false;
	}

	bool ViewportPanel::OnKeyReleased(KeyReleasedEvent& e)
	{
		KeyCode key = e.GetKeyCode();
		if (key == KeyCode::Left_alt || key == KeyCode::Right_alt)
		{
			m_AltPressed = false;
		}

		return false;
	}

	void ViewportPanel::OnUnFocused()
	{
		m_AltPressed = false;
		m_bLeftMouseButtonPressed = false;
		m_bMiddleMouseButtonPressed = false;
	}

	void ViewportPanel::FocusOnEntity()
	{
		auto& selectedEntity = SceneHierarchyPanel::GetSelectedEntity();
		
		if (selectedEntity)
		{ 
			m_FocusedPosition = selectedEntity.GetComponent<TransformComponent>().m_Transform.GetPosition();
			m_Viewport->m_Scene->m_DefaultSceneView.m_Transform.LookAt(m_FocusedPosition);
		}
	}

	void ViewportPanel::Zoom(float offset)
	{
		auto& CamTransform = m_Viewport->m_Scene->m_DefaultSceneView.m_Transform;
		FVector3 CamForward = CamTransform.GetForward();
		FVector3 CamPosition = CamTransform.GetPosition();
		FVector3 NewCamPosition = CamPosition + (CamForward * offset);
		CamTransform.SetPosition(NewCamPosition);
		m_CameraDistance = CamTransform.GetPosition().GetMagnitude();
	}

	void ViewportPanel::Pan(float xOffset, float yOffset)
	{
		auto& CamTransform = m_Viewport->m_Scene->m_DefaultSceneView.m_Transform;
		auto CamPosition = CamTransform.GetPosition();
		auto NewCamPosition = CamPosition  + (CamTransform.GetRight() * xOffset) + (CamTransform.GetUp() * yOffset);
		CamTransform.SetPosition(NewCamPosition);
		m_CameraDistance = CamTransform.GetPosition().GetMagnitude();
	}

	void ViewportPanel::Orbit(float yaw, float pitch)
	{
#if DEGREE_ANGLES
		float offYaw = yaw;
		float offPitch = pitch;

#else 
	offYaw = MathLibrary::ToRadians(yaw);
	offPitch = MathLibrary::ToRadians(pitch);
#endif

		Yaw += offYaw * m_OrbitalSpeed;
		Pitch += offPitch * m_OrbitalSpeed;

		//Get distance form focal point in this case for now {0,0,0}
		auto& camTransform = m_Viewport->m_Scene->m_DefaultSceneView.m_Transform;

#if DEGREE_ANGLES
		float x = MathLibrary::CosD(Yaw) * MathLibrary::CosD(Pitch) * m_CameraDistance;
		float y = MathLibrary::SinD(Pitch) * m_CameraDistance;
		float z = (MathLibrary::SinD(Yaw) * MathLibrary::CosD(Pitch)) * m_CameraDistance;
#else
		float x = MathLibrary::Cos(Yaw) * MathLibrary::Cos(Pitch) * m_CameraDistance;
		float y = MathLibrary::Sin(Pitch) * m_CameraDistance;
		float z = (MathLibrary::Sin(Yaw) * MathLibrary::Cos(Pitch)) * m_CameraDistance;
#endif

		auto newPos = FVector3(x, y, z);
		camTransform.SetPosition(newPos);
		camTransform.LookAt(m_FocusedPosition);
	}
}