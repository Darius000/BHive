#pragma once

#include "../Editors/Editor.h"
#include "Core/Viewport/Viewport.h"
#include "Object/Entity.h"

namespace BHive
{

	class ViewportPanel : public ImGuiPanel
	{
	public:
		ViewportPanel(const char* label, Viewport* viewport);

		void OnImGuiRender() override;
		

		void OnMouseScrolled(MouseScrolledEvent& e);
		void OnMouseMoved(MouseMovedEvent& e);
		void OnMouseButtonPressed(MouseButtonPressedEvent& e);
		void OnMouseButtonReleased(MouseButtonReleasedEvent& e);

		Viewport* m_Viewport;

	private:
		FVector2 m_ViewportSize = { 0, 0 };
		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;

		//Mouse
		float m_ZoomLevel = 0.01f;
		float m_ZoomSpeed = 1.0f;
		FVector3 m_CameraPosition;
		float m_CameraSpeed = 10.0f;
		bool m_bMiddleMouseButtonPressed = false;
		bool m_bLeftMouseButtonPressed = false;
		FVector2 m_OldMousePos;
	};
}

