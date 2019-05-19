#pragma once

#include "BHive/Entities/Entity.h"

namespace BHive
{
	//Make Component
	class BHive_API Camera : public Entity
	{
	public:
		Camera();
		Camera(float AspectRatio);
		Camera(float AspectRatio, const Vector3& position);
		virtual ~Camera();

		float Fov;
		float Near;
		float Far;
		float aspectRatio;

		void SetActive();
		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();
		glm::mat4 LookAt(const Vector3& target);
	};
}
