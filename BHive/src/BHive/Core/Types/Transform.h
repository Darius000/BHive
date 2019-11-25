#pragma once

namespace BHive
{
	struct Transform;

	DECLARE_ONE_PARAMETER_EVENT(TransformUpdated, Transform&, newTransform)

	enum class ERotationOrder
	{
		XYZ, XZY, YXZ, YZX, ZXY, ZYX
	};

	struct Transform
	{
	public:
		Transform();
		Transform(const FVector3& location, 
			const Rotator& rotation = Rotator(0.0f), 
			const FVector3& scale = FVector3(1.0f));
	public:
		void SetPosition(const FVector3& position);
		void SetPosition(float x, float y, float z);
		void SetRotation(const Rotator& rotation);
		void SetRotation(float roll, float yaw, float pitch);
		void SetScale(const FVector3& scale);
		void SetScale(float size);
		void SetScale(float x, float y, float z);
		void SetRotationOrder(const ERotationOrder& rotationOrder);

		const FVector3& GetPosition() { return m_Position; }
		const Rotator& GetRotation() { return m_Rotation; }
		const FVector3& GetScale()  { return m_Scale; }
		const FVector3& GetForward() { return FVector3(-m_ModelMatrix[0][2], -m_ModelMatrix[1][2], -m_ModelMatrix[2][2]).Normalize(); }
		const FVector3& GetRight() { return FVector3(m_ModelMatrix[0][0], m_ModelMatrix[1][0], m_ModelMatrix[2][0]).Normalize(); }
		const FVector3& GetUp() { return FVector3(m_ModelMatrix[0][1], m_ModelMatrix[1][1], m_ModelMatrix[2][1]).Normalize(); }
		const glm::mat4& GetMatrix() const { return m_ModelMatrix;}

		const BString ToString() const;

		FTransformUpdatedEvent OnTransformUpdated;

	private:
		void RecalulateModelMatrix();

	private:
		FVector3 m_Position;
		Rotator m_Rotation;
		FVector3 m_Scale;
		glm::mat4 m_TranslationMatrix;
		glm::mat4 m_RotationMatrix;
		glm::mat4 m_ScaleMatrix;
		glm::mat4  m_ModelMatrix;
		ERotationOrder m_RotationOrder;
	};

	inline std::ostream& operator<<(std::ostream& os, const Transform& transform)
	{
		return os << transform.ToString();
	}
}
