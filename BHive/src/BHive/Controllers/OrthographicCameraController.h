#pragma once

#include "BHive/Components/CameraComponents.h"

namespace BHive
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);
		virtual ~OrthographicCameraController() = default;

		OrthographicCameraComponent& GetCamera() { return m_Camera; }
		const OrthographicCameraComponent& GetCamera() const { return m_Camera; }
		void SetZoomLevel(float level);
		float GetZoomLevel() const { return m_ZoomLevel; }
	public:
		void OnUpdate(const Time& time);
		void OnEvent(Event& e);

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		OrthographicCameraComponent m_Camera;
		FVector3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_AspectRatio = 16.0f / 9.0f;
		float m_ZoomLevel = 0.01f;
		float m_CameraRotation = 0.0f;
		float m_RotationSpeed = 1.0f;
		float m_CameraSpeed = 0.1f;
		float m_ZoomSpeed = 1.0f;
		bool m_Rotation;
	};
}

