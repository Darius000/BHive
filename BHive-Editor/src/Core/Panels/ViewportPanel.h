#pragma once

#include "BHive.h"
#include "Editors/ImGuiPanel.h"
#include "BHive/Core/Viewport/Viewport.h"


namespace BHive
{

	class ViewportPanel : public ImGuiPanel
	{
	public:
		ViewportPanel(const std::string& label, Ref<Viewport> viewport, uint64 id = 0);

		void OnRenderMenuBar() override;
		void OnRenderWindow() override;
		void RenderGizmo(const FVector2& windowPos, const FVector2& windowSize);

		bool OnMouseScrolled(MouseScrolledEvent& e) override;
		bool OnMouseMoved(MouseMovedEvent& e) override;
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e) override;
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e) override;
		bool OnKeyPressed(KeyPressedEvent& e) override;
		bool OnKeyReleased(KeyReleasedEvent& e) override;

		Ref<Viewport> m_Viewport;

		void Zoom(float offset);
		void Pan(float xOffset, float yOffset);

	private:
		FVector2 m_ViewportSize = { 0, 0 };

		//Mouse
		float m_ZoomSpeed = .5f;
		FVector3 m_CameraPosition;
		float m_CameraSpeed = 1.0f;
		Rotator m_CameraRotation;
		float m_ZoomLevel;
		bool m_AltPressed = false;
		bool m_bMiddleMouseButtonPressed = false;
		bool m_bLeftMouseButtonPressed = false;
		FVector2 m_OldMousePos;

		//gizmo
		int32 m_GizmoType = -1;
		int32 m_GizmoMode = 0;
		bool m_IsUsingGizmo = false;
	};
}

