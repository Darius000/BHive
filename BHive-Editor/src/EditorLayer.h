#pragma once

#include "BHive.h"

namespace BHive
{ 
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(const Time& time) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;

	public:
	//events
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);

	private:
		//Ref<PerspectiveCameraController> m_OrthoCameraController;
		//Plane* m_Plane;
		Ref<Texture2D> m_Texture;
		Ref<Texture2D> m_Texture2;
		Ref<FrameBuffer> m_Framebuffer;
		Entity actor0;
		Entity Camera;
		FVector2 m_ViewportSize= {0, 0};
		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;

		//Mouse
		float m_ZoomLevel = 0.01f;
		float m_ZoomSpeed = 1.0f;
		FVector3 m_CameraPosition;
		Rotator m_CameraRotation = { 0.0f, 0.0f, 0.0f };
		float m_RotationSpeed = .01f;
		float m_CameraSpeed = 100.0f;
		bool m_bMiddleMouseButtonPressed = false;
		bool m_bLeftMouseButtonPressed = false;
		FVector2 m_OldMousePos;
		float m_DeltaTime = 0.0f;
		Vector2<float> m_Angles;
	};
}