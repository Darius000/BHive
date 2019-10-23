#pragma once

#include "BHive/Components/TransformComponent.h"

namespace BHive
{
	class CameraComponent : public TransformComponent
	{
		
	public:
		CameraComponent() {}
		virtual ~CameraComponent() {}

	public:
		virtual const glm::mat4& GetProjectionMatrix() const = 0;
		virtual const glm::mat4& GetViewMatrix() const = 0;
		virtual const glm::mat4& GetViewProjectionMatrix() const = 0;

	private:
		virtual void RecalulateViewMatrix(const Transform& transform) = 0;
	
	};

	class OrthographicCameraComponent : public CameraComponent
	{
		BCLASS(OrthographicCameraComponent, ComponentCategory, CameraComponent)

	public:
		OrthographicCameraComponent();
		OrthographicCameraComponent(float left, float right, float bottom, float top) ;

		void SetProjection(float left, float right, float bottom, float top);
		virtual const glm::mat4& GetProjectionMatrix() const override { return m_ProjectionMatrix; }
		virtual const glm::mat4& GetViewMatrix() const override { return m_ViewMatrix; }
		virtual const glm::mat4& GetViewProjectionMatrix() const override { return m_ViewProjectionMatrix; }

	protected:
		virtual void OnTransformUpdated(const Transform& transform) override;

	private:
		virtual void RecalulateViewMatrix(const Transform& transform) override;

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
	};
}