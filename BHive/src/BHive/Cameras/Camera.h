#pragma once

#include "GameObject.h"

namespace BHive
{
	class BHive_API Camera : public GameObject
	{
	public:
		Camera();
		Camera(float AspectRatio);
		Camera(float AspectRatio, glm::vec3 position);
		virtual ~Camera();

		float Fov;
		float Near;
		float Far;
		float aspectRatio;

		void SetActive();
		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();
		glm::mat4 LookAt(glm::vec3 target);
	};
}
