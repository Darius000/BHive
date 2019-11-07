#pragma once

#include "BHive/Components/TransformComponent.h"

namespace BHive
{
	class CameraComponent : public TransformComponent
	{
		
	public:
		CameraComponent();
		virtual ~CameraComponent() {}

	public:
		const glm::mat4& GetProjectionMatrix() const  { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const  { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	protected:
		virtual void OnTransformUpdated(const Transform& transform) override;

	private:
		virtual void RecalulateViewMatrix(const Transform& transform) = 0;

	protected:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		friend class CameraController;
	
	};

	class OrthographicCameraComponent : public CameraComponent
	{
		BCLASS(OrthographicCameraComponent, ComponentCategory, CameraComponent)

	public:
		OrthographicCameraComponent();
		OrthographicCameraComponent(float left, float right, float bottom, float top) ;

		void SetProjection(float left, float right, float bottom, float top);

	private:
		virtual void RecalulateViewMatrix(const Transform& transform) override;
	
	};

	class PerspectiveCameraComponent : public CameraComponent
	{
		BCLASS(PerspectiveCameraComponent, ComponentCategory, CameraComponent)

	public:
		PerspectiveCameraComponent();
		PerspectiveCameraComponent(float fov, float aspect, float zNear, float zFar);

		void SetProjection(float fov, float aspect, float zNear, float zFar);
		void LookAt(FVector3 location);

	private:
		virtual void RecalulateViewMatrix(const Transform& transform) override;

	};
}