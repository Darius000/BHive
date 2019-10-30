#include "BHivePCH.h"
#include "CameraComponents.h"
#include "BHive/Renderer/Shader.h"

namespace BHive
{
	OrthographicCameraComponent::OrthographicCameraComponent()
		:m_ProjectionMatrix(1.0f), m_ViewMatrix(1.0f), m_ViewProjectionMatrix(1.0f)
	{

	}

	OrthographicCameraComponent::OrthographicCameraComponent(float left, float right, float bottom, float top)
		:m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f), m_ViewProjectionMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

		GetTransform().OnTransformUpdated.AddBinding(BIND_EVENT_ONE_PARAM(&OrthographicCameraComponent::RecalulateViewMatrix));
	}

	void OrthographicCameraComponent::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCameraComponent::OnTransformUpdated(const Transform& transform)
	{
		glm::mat4 VP = GetViewProjectionMatrix();
		ShaderLibrary::UpdateShaderViewProjectionMatrices(VP); //TODO : change this
	}

	void OrthographicCameraComponent::RecalulateViewMatrix(const Transform& transform)
	{
		glm::mat4 matrix = transform.GetMatrix();
		m_ViewMatrix = glm::inverse(matrix);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; //need to be this order
	}
}