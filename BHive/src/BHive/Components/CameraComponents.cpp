#include "BHivePCH.h"
#include "CameraComponents.h"
#include "BHive/Renderer/Shader.h"

namespace BHive
{
	CameraComponent::CameraComponent()
		:m_ProjectionMatrix(1.0f), m_ViewMatrix(1.0f), m_ViewProjectionMatrix(1.0f)
	{
		GetTransform().OnTransformUpdated.AddBinding(BIND_EVENT_ONE_PARAM(CameraComponent::RecalulateViewMatrix));
	}

	void CameraComponent::OnTransformUpdated(const Transform& transform)
	{
		glm::mat4 VP = GetViewProjectionMatrix();
		ShaderLibrary::UpdateShaderViewProjectionMatrices(VP); //TODO : change this
	}

	OrthographicCameraComponent::OrthographicCameraComponent()
		:CameraComponent()
	{

	}

	OrthographicCameraComponent::OrthographicCameraComponent(float left, float right, float bottom, float top)
		:OrthographicCameraComponent()
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCameraComponent::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCameraComponent::RecalulateViewMatrix(const Transform& transform)
	{
		glm::mat4 matrix = transform.GetMatrix();
		m_ViewMatrix = glm::inverse(matrix);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; //need to be this order
	}

	PerspectiveCameraComponent::PerspectiveCameraComponent()
		:CameraComponent()
	{

	}

	PerspectiveCameraComponent::PerspectiveCameraComponent(float fov, float aspect, float zNear, float zFar)
		:PerspectiveCameraComponent()
	{
		m_ProjectionMatrix = glm::perspective(fov, aspect, zNear, zFar);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	

	void PerspectiveCameraComponent::SetProjection(float fov, float aspect, float zNear, float zFar)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspect, zNear, zFar);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCameraComponent::LookAt(FVector3 location)
	{
		FVector3 loc = GetTransform().GetPosition();
		m_ViewMatrix = glm::lookAt(glm::vec3(loc.x, loc.y, loc.z), glm::vec3(location.x, location.y, location.z), glm::vec3(0.0f, 1.0f, 0.0f));
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCameraComponent::RecalulateViewMatrix(const Transform& transform)
	{
		glm::mat4 matrix = transform.GetMatrix();
		m_ViewMatrix = glm::inverse(matrix);
		/*FVector3 loc = GetTransform().GetPosition();
		m_ViewMatrix = glm::lookAt(glm::vec3(loc.x, loc.y, loc.z), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));*/
		m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, .1f, 1000.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}