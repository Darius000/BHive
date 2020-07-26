#pragma once

#include "BHive/Components/CameraComponents.h"

namespace BHive
{
	
	class CameraController
	{
	public:
		CameraController();
		virtual ~CameraController() = default;

		void SetZoomLevel(float level);
		float GetZoomLevel() const { return m_ZoomLevel; }
	public:
		virtual void OnUpdate(const Time& time) = 0;
		void OnEvent(Event& e);

	protected:
		virtual bool OnMouseScrolled(MouseScrolledEvent& e) = 0;
		virtual bool OnMouseMoved(MouseMovedEvent& e) = 0;
		virtual bool OnMouseButtonPressed(MouseButtonPressedEvent& e) = 0;
		virtual bool OnMouseButtonReleased(MouseButtonReleasedEvent& e) = 0;

	protected:
		float m_ZoomLevel = 0.01f;
		float m_ZoomSpeed = 1.0f;

	};

	class OrthographicCameraController : public CameraController
	{
	public:
		OrthographicCameraController(Ref<OrthographicCameraComponent>& camera,  bool rotation = false);

		Ref<OrthographicCameraComponent>& GetCamera() { return m_Camera; }
		const Ref<OrthographicCameraComponent>& GetCamera() const;
	
	public:
		void OnUpdate(const Time & time) override;

	private:
		bool OnMouseScrolled(MouseScrolledEvent & e) override;
		bool OnMouseMoved(MouseMovedEvent& e) override;
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e) override;
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e) override;

	private:
		Ref<OrthographicCameraComponent> m_Camera;
		FVector3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_AspectRatio = 16.0f / 9.0f;
		float m_CameraRotation = 0.0f;
		float m_RotationSpeed = 1.0f;
		float m_CameraSpeed = 0.5f;
		bool m_Rotation;
		bool m_bLeftMouseButtonPressed = false;
		
	};

	class PerspectiveCameraController : public CameraController
	{
	public:
		PerspectiveCameraController(Ref<PerspectiveCameraComponent> camera);

		void OnUpdate(const Time& time) override;
		Ref<PerspectiveCameraComponent> GetCamera() { return m_Camera; }
		const Ref<PerspectiveCameraComponent> GetCamera() const { return m_Camera; }

	protected:
		bool OnMouseScrolled(MouseScrolledEvent& e) override;
		bool OnMouseMoved(MouseMovedEvent& e) override;
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e) override;
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e) override;

	private:
		Ref<PerspectiveCameraComponent> m_Camera;
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

