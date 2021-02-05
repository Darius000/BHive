#pragma once


#include "Camera.h"

namespace BHive
{
	class EditorCamera : public Camera
	{
		/*EditorCamera() = default;
		EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

		void OnUpdate(const Time& time);
		void OnEvent(Event& e);

		inline void SetViewportSize(float width, float height) {}

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjection() const { return m_Projection * m_ViewMatrix; }

	private:
		void UpdateProjection();
		void UpdateView();

		bool OnMouseScroll(MouseScrolledEvent& e);

		void MousePan(const FVector2& delta);
		void MouseRotate(const FVector2& delta);
		void MouseZoom(float delta);

	private:
		Transform transform;*/

	};
}