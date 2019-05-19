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
		void SetRotation(const Vector3& InRot);
		void SetRotation(float x, float y, float z);
		void SetScale(const Vector3& InScale);
		void SetScale(float size);
		void SetScale(float x, float y, float z);

		Vector3 GetPosition();
		Vector3 GetRotation();
		Vector3 GetScale();

		Vector3 GetForward();
		Vector3 GetRight();
		Vector3 GetUp();

		glm::mat4 GetMatrix();

		FTransformUpdatedEvent OnTransformUpdated;

	private:
		Vector3 Position;
		Vector3 Rotation;
		Vector3 Scale;

		void UpdateMatrix();
		void UpdateTransform();

		glm::mat4 T, R, S, M;
	};
}
