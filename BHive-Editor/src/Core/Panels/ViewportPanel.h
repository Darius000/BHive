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

		void OnUnFocused() override;

		Ref<Viewport> m_Viewport;

		void FocusOnEntity();
		void Zoom(float offset);
		void Pan(float xOffset, float yOffset);
		void Orbit(float yaw, float pitch);

	private:
		FVector2 m_ViewportSize = { 0, 0 };
		FVector3 m_FocusedPosition = {};

		//Mouse
		float m_ZoomSpeed = 1.0f;
		float m_PanSpeed = 15.0f;
		float m_CameraDistance = 0.0f;

		float m_OrbitalSpeed = 100.0f;

		/*x = yaw, y = pitch in radians*/
		float Yaw = 0.0f;
		float Pitch = 0.0f;

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

