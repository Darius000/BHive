#include "BHivePCH.h"
#include "Transform.h"


namespace BHive
{
	Transform::Transform()
		:Transform(FVector3(0.0f), Rotator(0.0f), FVector3(1.0f))
	{
		
	};

	Transform::Transform(const FVector3& position, const Rotator& rotation, const FVector3& scale)
		:m_Position(position), m_Rotation(rotation), m_Scale(scale), 
		m_ModelMatrix(1.0f)
	{
		RecalulateModelMatrix();
	}

	void Transform::SetPosition(const FVector3& position)
	{
		m_Position = position;

		RecalulateModelMatrix();
	}

	void Transform::SetPosition(float x, float y, float z)
	{
		m_Position = FVector3(x, y, z);

		RecalulateModelMatrix();
	}

	void Transform::SetRotation(const Rotator& rotation)
	{
		m_Rotation = rotation;

		RecalulateModelMatrix();
	}

	void Transform::SetRotation(float roll, float yaw, float pitch)
	{
		SetRotation(Rotator(roll, yaw, pitch ));
	}

	void Transform::SetScale(const FVector3& scale)
	{
		m_Scale = scale;

		RecalulateModelMatrix();
	}

	void Transform::SetScale(float size)
	{
		m_Scale = FVector3(size);

		RecalulateModelMatrix();
	}

	void Transform::SetScale(float x, float y, float z)
	{
		m_Scale = FVector3(x, y ,z);

		RecalulateModelMatrix();
	}

	void Transform::LookAt(const FVector3& target)
	{
		auto upVector = glm::vec3(0, 1, 0);
		auto lookAtMatrix = glm::lookAt((glm::vec3)m_Position, (glm::vec3)target, upVector);
		auto viewMatrix = glm::inverse(lookAtMatrix);
		m_Rotation = Quaternion::ToRotator(Quaternion(viewMatrix));

		RecalulateModelMatrix();
	}


	FVector3 Transform::GetForward() const
	{
		return FVector3(m_ModelMatrix[0][2], m_ModelMatrix[1][2], m_ModelMatrix[2][2]).Normalize();
	}


	FVector3 Transform::GetRight() const
	{
		return FVector3(m_ModelMatrix[0][0], m_ModelMatrix[1][0], m_ModelMatrix[2][0]).Normalize();
	}


	FVector3 Transform::GetUp() const
	{
		return FVector3(m_ModelMatrix[0][1], m_ModelMatrix[1][1], m_ModelMatrix[2][1]).Normalize();
	}


	const BString Transform::ToString() const
	{
		return	Format("Position: {%f, %f, %f}, Rotation: {%f, %f, %f} , Scale: {%f, %f, %f} ", m_Position.x, m_Position.y, m_Position.z, m_Rotation.roll, m_Rotation.yaw, m_Rotation.pitch, m_Scale.x, m_Scale.y, m_Scale.z );
	}

	void Transform::RecalulateModelMatrix()
	{
		//Position
		glm::mat4 m_TranslationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position.x, m_Position.y, m_Position.z));
		glm::mat4 m_ScaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(m_Scale.x, m_Scale.y, m_Scale.z));
		Quaternion rotationQ = Quaternion::FromEuler(m_Rotation);
		glm::mat4 m_RotationMatrix = Quaternion::ToMatrix(rotationQ);

		m_ModelMatrix = m_TranslationMatrix * m_RotationMatrix * m_ScaleMatrix;

		OnTransformUpdated.Broadcast(*this);
	}

}