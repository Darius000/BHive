#include "BHivePCH.h"
#include "Transform.h"


namespace BHive
{
	Transform::Transform()
		:Transform(FVector3(0.0f), Rotator(0.0f), FVector3(1.0f))
	{
		RecalulateModelMatrix();
	};

	Transform::Transform(const FVector3& position, const Rotator& rotation, const FVector3& scale)
		:m_Position(position), m_Rotation(rotation), m_Scale(scale), 
		m_ModelMatrix(1.0f), m_TranslationMatrix(1.0), m_RotationMatrix(1.0f), m_ScaleMatrix(1.0f), quat()
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
		auto upVector = FVector3(0, 1, 0);
		auto lookAtMatrix = glm::lookAt((glm::vec3)m_Position, (glm::vec3)target, (glm::vec3)upVector);
		auto viewMatrix = glm::inverse(lookAtMatrix);
		glm::vec3 translation, scale, skew;
		glm::vec4 perspective;
		glm::quat orientation;
		glm::decompose(viewMatrix, scale, orientation, translation, skew, perspective);
		auto angles = glm::eulerAngles(orientation);

		m_Rotation.roll = MathLibrary::ToDegrees(angles.x);
		m_Rotation.yaw = MathLibrary::ToDegrees(angles.y);
		m_Rotation.pitch = MathLibrary::ToDegrees(angles.z);
		//m_ModelMatrix = m_TranslationMatrix * viewMatrix * m_ScaleMatrix;
		//quat = glm::quat({ m_Rotation.roll, m_Rotation.yaw, m_Rotation.pitch });

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
		RecalulateModelMatrixInternal(*this);
	}

	void Transform::RecalulateModelMatrixInternal(Transform& transform)
	{
		m_TranslationMatrix = glm::translate(glm::mat4(1.0f), (glm::vec3)transform.m_Position);
		m_ScaleMatrix = glm::scale(glm::mat4(1.0f), (glm::vec3)m_Scale);
		//Quaternion rotationQ = Quaternion::FromEuler(transform.m_Rotation);

		float x = MathLibrary::ToRadians(transform.m_Rotation.roll);
		float y = MathLibrary::ToRadians(transform.m_Rotation.yaw);
		float z = MathLibrary::ToRadians(transform.m_Rotation.pitch);

		quat = glm::quat({x, y, z});
		m_RotationMatrix = glm::toMat4(quat);

		m_ModelMatrix = m_TranslationMatrix * m_RotationMatrix * m_ScaleMatrix;
	}

}