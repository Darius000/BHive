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
		m_ModelMatrix(1.0f), m_RotationOrder(ERotationOrder::XYZ)
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

	void Transform::SetRotationOrder(const ERotationOrder& rotationOrder)
	{
		m_RotationOrder = rotationOrder;
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
		glm::mat4 m_RotationMatrix = glm::mat4(1.0);

		switch (m_RotationOrder)
		{
		case ERotationOrder::XYZ:
			m_RotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.roll), glm::vec3(1.0f, 0.0f, 0.0f));
			m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(m_Rotation.yaw), glm::vec3(0.0f, 1.0f, 0.0f));
			m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(m_Rotation.pitch), glm::vec3(0.0f, 0.0f, 1.0f));
			break;
		case ERotationOrder::XZY:
			m_RotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.roll), glm::vec3(1.0f, 0.0f, 0.0f));
			m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(m_Rotation.pitch), glm::vec3(0.0f, 0.0f, 1.0f));
			m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(m_Rotation.yaw), glm::vec3(0.0f, 1.0f, 0.0f));
			break;
		case ERotationOrder::YXZ:
			m_RotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.yaw), glm::vec3(0.0f, 1.0f, 0.0f));
			m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(m_Rotation.roll), glm::vec3(1.0f, 0.0f, 0.0f));
			m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(m_Rotation.pitch), glm::vec3(0.0f, 0.0f, 1.0f));
			break;
		case ERotationOrder::YZX:
			m_RotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.yaw), glm::vec3(0.0f, 1.0f, 0.0f));
			m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(m_Rotation.pitch), glm::vec3(0.0f, 0.0f, 1.0f));
			m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(m_Rotation.roll), glm::vec3(1.0f, 0.0f, 0.0f));
			break;
		case ERotationOrder::ZXY:
			m_RotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.pitch), glm::vec3(0.0f, 0.0f, 1.0f));
			m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(m_Rotation.roll), glm::vec3(1.0f, 0.0f, 0.0f));
			m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(m_Rotation.yaw), glm::vec3(0.0f, 1.0f, 0.0f));
			break;
		case ERotationOrder::ZYX:
			m_RotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.pitch), glm::vec3(0.0f, 0.0f, 1.0f));
			m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(m_Rotation.yaw), glm::vec3(0.0f, 1.0f, 0.0f));
			m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(m_Rotation.roll), glm::vec3(1.0f, 0.0f, 0.0f));
			break;
		}

		m_ModelMatrix = m_TranslationMatrix * m_RotationMatrix * m_ScaleMatrix;

		OnTransformUpdated.Broadcast(*this);
	}

}