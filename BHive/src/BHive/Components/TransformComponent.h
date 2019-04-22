#pragma once

#include "ECS.h"

namespace BHive
{
	class BHive_API TransformComponent : public Component
	{
	public:
		void ComponentInit() override;
		void SetPosition(glm::vec3 InPos);
		void SetPosition(float x, float y, float z);
		void SetRotation(glm::vec3 InRot);
		void SetRotation(float x, float y, float z);
		void SetScale(glm::vec3 InScale);
		void SetScale(float size);
		void SetScale(float x, float y, float z);

		glm::vec3 GetPosition();
		glm::vec3 GetRotation();
		glm::vec3 GetScale();

		glm::vec3 GetForward();
		glm::vec3 GetRight();
		glm::vec3 GetUp();

		glm::mat4 GetMatrix();

	private:
		glm::vec3 Position;
		glm::vec3 Rotation;
		glm::vec3 Scale;

		void UpdateMatrix();

		glm::mat4 T, R, S, M;
	};
}
