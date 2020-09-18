#include "ViewportPanel.h"

namespace BHive
{

	ViewportPanel::ViewportPanel(const char* label, Viewport* viewport)
		:ImGuiPanel(label), m_Viewport(viewport)
	{
		
	}	

	void ViewportPanel::OnImGuiRender()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin(m_Label, &m_isOpen);

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

			m_Viewport->m_Framebuffer->Resize((uint32)viewportPanelSize.x, (uint32)viewportPanelSize.y);
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
			m_Viewport->m_Scene->OnViewportResize((uint32)m_ViewportSize.x, (uint32)m_ViewportSize.y);
		}

		uint32 textureID = m_Viewport->m_Framebuffer->GetColorAttachmentRendererID();

		ImGui::Image((void*)textureID, ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));


		ImGui::End();
		ImGui::PopStyleVar();
	}

	void ViewportPanel::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel = e.GetYOffset() * m_ZoomSpeed;
		m_CameraPosition.z += m_ZoomLevel;
		m_Viewport->m_Camera.GetComponent<TransformComponent>().m_Transform.SetPosition(m_CameraPosition);
	}

	void ViewportPanel::OnMouseMoved(MouseMovedEvent& e)
	{
		FVector2 MousePos = FVector2(e.GetX(), e.GetY());
		FVector2 DeltaMousePos = MousePos - m_OldMousePos;
		m_OldMousePos = MousePos;
		DeltaMousePos.Normalize();

		if (m_bMiddleMouseButtonPressed)
		{
			m_CameraPosition.x -= m_CameraSpeed * DeltaMousePos.x;
			m_CameraPosition.y += m_CameraSpeed * DeltaMousePos.y;
			m_Viewport->m_Camera.GetComponent<TransformComponent>().m_Transform.SetPosition(m_CameraPosition);
		}

		if (m_bLeftMouseButtonPressed)
		{
			//ADD ROTATION HERE
		}
	}

	void ViewportPanel::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == MouseButton::Middle)
		{
			m_bMiddleMouseButtonPressed = true;
		}
		else if (e.GetMouseButton() == MouseButton::Left)
		{
			m_bLeftMouseButtonPressed = true;
		}
	}

	void ViewportPanel::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		if (e.GetMouseButton() == MouseButton::Middle)
		{
			m_bMiddleMouseButtonPressed = false;
		}
		else if (e.GetMouseButton() == MouseButton::Last)
		{
			m_bLeftMouseButtonPressed = false;
		}
	}

}