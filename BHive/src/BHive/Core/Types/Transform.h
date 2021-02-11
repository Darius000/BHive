#pragma once

namespace BHive
{
	struct Transform
	{
	public:
		Transform();
		Transform(const FVector3& position, 
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
		void LookAt(const FVector3& target);

		FVector3& GetPosition() { return m_Position; }
		Rotator& GetRotation() { return m_Rotation; }
		FVector3& GetScale() { return m_Scale; }
		FVector3 GetForward() const;
		FVector3 GetRight() const;
		FVector3 GetUp()  const;
		glm::mat4& GetMatrix() { return m_ModelMatrix;}

		const BString ToString() const;

		void RecalulateModelMatrix();

	private:
		void RecalulateModelMatrixInternal(Transform& transform);

		FVector3 m_Position;
		Rotator m_Rotation;
		FVector3 m_Scale;
		glm::mat4  m_ModelMatrix;
		glm::mat4 m_TranslationMatrix;
		glm::mat4 m_RotationMatrix;
		glm::mat4 m_ScaleMatrix;	
		glm::quat quat;
	};

	inline std::ostream& operator<<(std::ostream& os, const Transform& transform)
	{
		return os << transform.ToString();
	}
}
