#pragma once

#include "BHive.h"

namespace BHive
{ 
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(const Time& time) override;
		void OnImGuiRender() override;
		void OnEvent(Event& event) override;

	public:
	//events
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);

	private:
		//Editor Windows
		void DisplayMenuBar();
		void DisplayViewPort(bool* IsOpen);
		void DisplayContentBrowser(bool* IsOpen);
		void DisplayStyleEditor(bool* IsOpen);
		void DisplayDetailsPanel(bool* IsOpen);
		void DisplayEditorLayout();
		void DisplayNodeEditor(bool* IsOpen);
		void DisplayFileDialogBrowser(const char* label, bool* IsOpen, WinPath& startDir);

	private:
		Ref<Texture2D> m_Texture;
		Ref<Texture2D> m_Texture2;
		Ref<FrameBuffer> m_Framebuffer;
		Entity actor0;
		Entity Camera;
		Entity Camera2;
		Entity pl;
		Entity Light;
		Entity tri;
		FVector2 m_ViewportSize= {0, 0};
		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;

		//Mouse
		float m_ZoomLevel = 0.01f;
		float m_ZoomSpeed = 1.0f;
		FVector3 m_CameraPosition;
		Rotator m_CameraRotation = { 0.0f, 0.0f, 0.0f };
		float m_RotationSpeed = .01f;
		float m_CameraSpeed = 10.0f;
		bool m_bMiddleMouseButtonPressed = false;
		bool m_bLeftMouseButtonPressed = false;
		FVector2 m_OldMousePos;
		float m_DeltaTime = 0.0f;
		Vector2<float> m_Angles;

		//Window States
		bool showContentBrowser = true;
		bool showStyleEditor = false;
		bool showViewport = true;
		bool showDetailsPanel = true;
		bool showDemoWindow = false;
		bool showFileBrowser = false;
		bool showNodeEditor = true;
	};

	static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
	static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }

}