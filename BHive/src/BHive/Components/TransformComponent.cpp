#include "BHivePCH.h"
#include "TransformComponent.h"


namespace BHive
{
	void TransformComponent::ComponentInit()
	{
		SetPosition(0.0f, 0.0f, 0.0f);
		SetScale(1.0f);
		SetRotation(0.0f, 0.0f, 0.0f);
		UpdateMatrix();
	}

	void TransformComponent::SetPosition(glm::vec3 InPos)
	{
		Position = InPos;

		T = glm::translate(T, Position);

		UpdateMatrix();
	}

	void TransformComponent::SetPosition(float x, float y, float z)
	{
		SetPosition(glm::vec3(x, y, z));
	}

	void TransformComponent::SetRotation(glm::vec3 InRot)
	{
		Rotation = InRot;

		R = glm::rotate(R, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		R = glm::rotate(R, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		R = glm::rotate(R, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		UpdateMatrix();
	}

	void TransformComponent::SetRotation(float x, float y, float z)
	{
		SetRotation(glm::vec3(x, y, z));
	}

	void TransformComponent::SetScale(glm::vec3 InScale)
	{
		Scale = InScale;

		S = glm::scale(S, Scale);

		UpdateMatrix();
	}

	void TransformComponent::SetScale(float size)
	{
		SetScale(glm::vec3(size, size, size));
	}

	void TransformComponent::SetScale(float x, float y, float z)
	{
		SetScale(glm::vec3(x, y, z));
	}

	glm::vec3 TransformComponent::GetPosition()
	{
		return Position;
	}

	glm::vec3 TransformComponent::GetRotation()
	{
		return Rotation;
	}

	glm::vec3 TransformComponent::GetScale()
	{
		return Scale;
	}

	glm::vec3 TransformComponent::GetForward()
	{
		return glm::normalize(glm::vec3(-M[0][2], -M[1][2], -M[2][2]));
	}

	glm::vec3 TransformComponent::GetRight()
	{
		return glm::normalize(glm::vec3(M[0][0], M[1][0], M[2][0]));
	}

	glm::vec3 TransformComponent::GetUp()
	{
		return glm::normalize(glm::vec3(M[0][1], M[1][1], M[2][1]));
	}

	glm::mat4 TransformComponent::GetMatrix()
	{
		return M;
	}

	void TransformComponent::UpdateMatrix()
	{
		M = T * R * S;
	}
}