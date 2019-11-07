#pragma once

#include "BHive/Components/CameraComponents.h"

namespace BHive
{
	
	class CameraController
	{
	public:
		CameraController(float aspectRatio);
		virtual ~CameraController() = default;

		void SetZoomLevel(float level);
		float GetZoomLevel() const { return m_ZoomLevel; }
	public:
		virtual void OnUpdate(const Time& time) = 0;
		void OnEvent(Event& e);

	protected:
		virtual bool OnMouseScrolled(MouseScrolledEvent& e) = 0;
		virtual bool OnWindowResized(WindowResizeEvent& e) = 0;

	protected:
		float m_AspectRatio = 16.0f / 9.0f;
		float m_ZoomLevel = 0.01f;
		float m_ZoomSpeed = 1.0f;
	};

	class OrthographicCameraController : public CameraController
	{
	public:
		OrthographicCameraController(Ref<OrthographicCameraComponent>& camera, float aspectRatio, bool rotation = false);

		Ref<OrthographicCameraComponent>& GetCamera() { return m_Camera; }
		const Ref<OrthographicCameraComponent>& GetCamera() const { return m_Camera; }
	
	public:
		virtual void OnUpdate(const Time & time) override;

	private:
		virtual bool OnMouseScrolled(MouseScrolledEvent & e) override;
		virtual bool OnWindowResized(WindowResizeEvent & e) override;

	private:
		Ref<OrthographicCameraComponent> m_Camera;
		FVector3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_AspectRatio = 16.0f / 9.0f;
		float m_ZoomLevel = 1.0f;
		float m_CameraRotation = 0.0f;
		float m_RotationSpeed = 1.0f;
		float m_CameraSpeed = 0.1f;
		float m_ZoomSpeed = 1.0f;
		bool m_Rotation;
	};

	class PerspectiveCameraController : public CameraController
	{
	public:
		PerspectiveCameraController(Ref<PerspectiveCameraComponent>& camera, float aspect);

		virtual void OnUpdate(const Time& time) override;
		Ref<PerspectiveCameraComponent>& GetCamera() { return m_Camera; }
		const Ref<PerspectiveCameraComponent>& GetCamera() const { return m_Camera; }

	protected:
		virtual bool OnMouseScrolled(MouseScrolledEvent& e) override;
		virtual bool OnWindowResized(WindowResizeEvent& e) override;

	private:
		Ref<PerspectiveCameraComponent> m_Camera;
		FVector3 m_CameraPosition = { 0.0f, 0.0f, 10.0f };
		Rotator m_CameraRotation = { 0.0f, 0.0f, 0.0f };
		float m_AspectRatio = 16.0f / 9.0f;
		float m_ZoomLevel = 1.0f;
		float m_RotationSpeed = 1.0f;
		float m_CameraSpeed = 0.001f;
		float m_ZoomSpeed = 0.1f;
	};
}

