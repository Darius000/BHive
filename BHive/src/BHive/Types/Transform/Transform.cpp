#include "BHivePCH.h"
#include "Transform.h"


namespace BHive
{
	Transform::Transform()
		:Position(0.0f), Scale(1.0f), Rotation(0.0f)
	{
	
	};

	void Transform::SetPosition(const Vector3& InPos)
	{
		SetPosition(InPos.x, InPos.y, InPos.z);
	}

	void Transform::SetPosition(float x, float y, float z)
	{
		Position.x = x;
		Position.y = y;
		Position.z = z;

		T = glm::translate(T, glm::vec3(x, y, z));

		UpdateTransform();

		UpdateMatrix();

		//BH_TRACE("{0}", Position.ToString());
	}

	void Transform::SetRotation(const Rotator& InRot)
	{
		Rotation = InRot;

		R = glm::rotate(R, glm::radians(Rotation.roll), glm::vec3(1.0f, 0.0f, 0.0f));
		R = glm::rotate(R, glm::radians(Rotation.yaw), glm::vec3(0.0f, 1.0f, 0.0f));
		R = glm::rotate(R, glm::radians(Rotation.pitch), glm::vec3(0.0f, 0.0f, 1.0f));

		UpdateTransform();

		UpdateMatrix();
	}

	void Transform::SetRotation(float roll, float yaw, float pitch)
	{
		SetRotation(Rotator(roll, yaw, pitch));
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

	Vector3 Transform::GetPosition() const
	{
		return Position;
	}

	Rotator Transform::GetRotation() const
	{
		return Rotation;
	}

	Vector3 Transform::GetScale() const
	{
		return Scale;
	}

	Vector3 Transform::GetForward() const
	{
		return Vector3(-M[0][2], -M[1][2], -M[2][2]).Normalize();
	}

	Vector3 Transform::GetRight() const
	{
		return Vector3(M[0][0], M[1][0], M[2][0]).Normalize();
	}

	Vector3 Transform::GetUp() const
	{
		return Vector3(M[0][1], M[1][1], M[2][1]).Normalize();
	}

	glm::mat4 Transform::GetMatrix() const
	{
		return M;
	}

	FString Transform::ToString() const
	{
		return	FString("{") + Position.x + "," + Position.y + "," + Position.z + "} ,"
				"{" + Scale.x + "," + Scale.y + "," + Scale.z + "} ,"
				"{" + Rotation.roll + "," + Rotation.yaw + "," +Rotation.pitch + "}";
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