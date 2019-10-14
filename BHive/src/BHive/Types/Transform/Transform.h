#pragma once

namespace BHive
{
	struct Transform;

	DECLARE_ONE_PARAMETER_EVENT(TransformUpdated, Transform&, newTransform);

	struct Transform
	{
	public:
		Transform();
		void SetPosition(const Vector3& InPos);
		void SetPosition(float x, float y, float z);
		void SetRotation(const Rotator& InRot);
		void SetRotation(float roll, float yaw, float pitch);
		void SetScale(const Vector3& InScale);
		void SetScale(float size);
		void SetScale(float x, float y, float z);

		Vector3 GetPosition() const;
		Rotator GetRotation() const;
		Vector3 GetScale() const;

		Vector3 GetForward() const;
		Vector3 GetRight() const;
		Vector3 GetUp() const;

		glm::mat4 GetMatrix() const;

		FString ToString() const;

		FTransformUpdatedEvent OnTransformUpdated;

	private:
		Vector3 Position;
		Rotator Rotation;
		Vector3 Scale;

		void UpdateMatrix();
		void UpdateTransform();

		glm::mat4 T, R, S, M;
	};

	inline std::ostream& operator<<(std::ostream& os, const Transform& transform)
	{
		return os << transform.ToString();
	}
}
