#include "ViewportPanel.h"
#include "imgui_internal.h"
#include "SceneHierarchyPanel.h"
#include "ImGuizmo/ImGuizmo.h"

namespace BHive
{

	ViewportPanel::ViewportPanel(const std::string& label, Ref<Viewport> viewport, uint64 id)
		:ImGuiPanel(label, ImGuiWindowFlags_MenuBar, id), m_Viewport(viewport)
	{
		m_CameraPosition = m_Viewport->m_Scene->m_DefaultSceneView.m_Transform.GetPosition();
	}	

	void ViewportPanel::OnRenderMenuBar()
	{
		ImGui::DragFloat("Exposure", &m_Viewport->m_Exposure);
		ImGui::SameLine();
		ImGui::Checkbox("HDR", &m_Viewport->m_HDR);
		ImGui::SameLine();
		ImGui::Checkbox("Bloom", &m_Viewport->m_Bloom);
	}

	void ViewportPanel::OnRenderWindow()
	{		
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

		if (m_ViewportSize != *((FVector2*)&viewportPanelSize) && viewportPanelSize.x > 0 && viewportPanelSize.y > 0)
		{

			m_Viewport->Resize((uint32)viewportPanelSize.x, (uint32)viewportPanelSize.y);
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
			m_Viewport->m_Scene->OnViewportResize((uint32)m_ViewportSize.x, (uint32)m_ViewportSize.y);
		}


		auto QuadFrameBuffer = m_Viewport->m_QuadFrameBuffer;

		float windowWidth = (float)ImGui::GetWindowWidth();
		float windowHeight = (float)ImGui::GetWindowHeight();

		//ImGui::SetCursorPos({0.0f, 0.0f});
		ImGui::BeginGroup();
		ImGui::Image((void*)*QuadFrameBuffer, ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));

		//Gizmos

		RenderGizmo({ImGui::GetWindowPos().x, ImGui::GetWindowPos().y}, {windowWidth, windowHeight});
	
		//uint32 finalcolor = m_Viewport->m_QuadColorAttachment;
		//uint32 depthcolors = m_Viewport->m_DepthAttachment;
		
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

		/*int32 i = 0;
		for (auto& GBuffer: m_Viewport->m_GBufferAttributes)
		{
			ImGui::BeginGroup();
			ImGui::Text("%s", GBufferTypeNames[(size_t)GBuffer.first]);
			ImGui::Image((void*)GBuffer.second.m_Texture, ImVec2(m_ViewportSize.x / 2.0f, m_ViewportSize.y / 2.0f), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::EndGroup();
			if (i % 2 == 0)
			{
				ImGui::SameLine();
			}
			i++;
		}

		for (uint32 i : m_Viewport->m_PingPongBlur)
		{
			ImGui::BeginGroup();
			ImGui::Text("PingPong %d", i);
			ImGui::Image((void*)i, ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::EndGroup();
		}

		ImGui::BeginGroup();
		ImGui::Text("Depth");
		ImGui::Image((void*)depthcolors, ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::EndGroup();*/

		ImGui::PopStyleVar();
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
				FVector3 translation = {};
				Rotator rotation = {};
				FVector3 scale = {};
				if (MatrixLibrary::DecomposeMatrixToTransform(transform, translation, rotation, scale))
				{
					Rotator deltaRotation = rotation - tc.m_Transform.GetRotation();
					Rotator newRotation = tc.m_Transform.GetRotation() + deltaRotation;
					tc.m_Transform = Transform(translation, newRotation, scale);
				}
			}
		}
	}

	bool ViewportPanel::OnMouseScrolled(MouseScrolledEvent& e)
	{
		Zoom(e.GetYOffset());
		
		return true;
	}

	bool ViewportPanel::OnMouseMoved(MouseMovedEvent& e)
	{
		if (m_AltPressed)
		{
			if (m_bMiddleMouseButtonPressed)
			{
				auto deltaX = e.GetX() - m_OldMousePos.x;
				auto deltaY = e.GetY() - m_OldMousePos.y; 

				deltaX = MathLibrary::Normalize(deltaX, 0.0f, m_ViewportSize.x);
				deltaY = MathLibrary::Normalize(deltaY, 0.0f, m_ViewportSize.y);

				Pan(deltaX, 0.0f);

				m_OldMousePos = FVector2(e.GetX(), e.GetY());
			}

			if (m_bLeftMouseButtonPressed)
			{
				//Rotate
			}

		}

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
				m_CameraPosition = FVector3(0.0f, 0.0f, 10.0f);
				m_CameraRotation = { 0.0f };
				m_Viewport->m_Scene->m_DefaultSceneView.m_Transform.SetPosition(m_CameraPosition);
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

	void ViewportPanel::Zoom(float offset)
	{
		auto& CamTransform = m_Viewport->m_Scene->m_DefaultSceneView.m_Transform;
		FVector3 CamForward = CamTransform.GetForward();
		FVector3 CamPosition = CamTransform.GetPosition();
		FVector3 NewCamPosition = CamPosition + (CamForward * offset);
		CamTransform.SetPosition(NewCamPosition);

		BH_CORE_INFO("camera position: {0}, Camera For : {1}", NewCamPosition, m_Viewport->m_Scene->m_DefaultSceneView.m_Transform.GetForward());
	}

	void ViewportPanel::Pan(float xOffset, float yOffset)
	{
		auto& CamTransform = m_Viewport->m_Scene->m_DefaultSceneView.m_Transform;
		auto CamPosition = CamTransform.GetPosition();
		auto NewCamPosition = CamPosition  + (CamTransform.GetRight() * xOffset) + (CamTransform.GetUp() * yOffset);
		CamTransform.SetPosition(NewCamPosition);

		BH_CORE_INFO("{0}{1}, camera position: {2}", xOffset, yOffset, NewCamPosition);
	}

}