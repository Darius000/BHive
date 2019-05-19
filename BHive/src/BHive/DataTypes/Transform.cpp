#include "BHivePCH.h"
#include "Transform.h"


namespace BHive
{
	Transform::Transform()
	{
		SetPosition(0.0f, 0.0f, 0.0f);
		SetScale(1.0f);
		SetRotation(0.0f, 0.0f, 0.0f);
		//UpdateMatrix();
	};

	void Transform::SetPosition(const Vector3& InPos)
	{
		Position = InPos;

		T = glm::translate(T, glm::vec3(Position.x, Position.y, Position.z));

		UpdateTransform();

		UpdateMatrix();
	}

	void Transform::SetPosition(float x, float y, float z)
	{
		SetPosition(Vector3(x, y, z));
	}

	void Transform::SetRotation(const Vector3& InRot)
	{
		Rotation = InRot;

		R = glm::rotate(R, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		R = glm::rotate(R, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		R = glm::rotate(R, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		UpdateTransform();

		UpdateMatrix();
	}

	void Transform::SetRotation(float x, float y, float z)
	{
		SetRotation(Vector3(x, y, z));
	}

	void Transform::SetScale(const Vector3& InScale)
	{
		Scale = InScale;

		S = glm::scale(S, glm::vec3(Scale.x, Scale.y, Scale.z));

		UpdateTransform();

		UpdateMatrix();
	}

	void Transform::SetScale(float size)
	{
		SetScale(Vector3(size, size, size));
	}

	void Transform::SetScale(float x, float y, float z)
	{
		SetScale(Vector3(x, y, z));
	}

	Vector3 Transform::GetPosition()
	{
		return Position;
	}

	Vector3 Transform::GetRotation()
	{
		return Rotation;
	}

	Vector3 Transform::GetScale()
	{
		return Scale;
	}

	Vector3 Transform::GetForward()
	{
		return Vector3(-M[0][2], -M[1][2], -M[2][2]).Normalize();
	}

	Vector3 Transform::GetRight()
	{
		return Vector3(M[0][0], M[1][0], M[2][0]).Normalize();
	}

	Vector3 Transform::GetUp()
	{
		return Vector3(M[0][1], M[1][1], M[2][1]).Normalize();
	}

	glm::mat4 Transform::GetMatrix()
	{
		return M;
	}

	void Transform::UpdateMatrix()
	{
		M = T * R * S;
	}

	void Transform::UpdateTransform()
	{
		OnTransformUpdated.Broadcast(*this);
	}
}