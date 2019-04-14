#pragma once

#include "Camera.h"

namespace BHive
{
	enum ECameraMovement
	{
		FOWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	//default values
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 5.0f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM = 45.0f;

	class BHive_API FPSCamera : public Camera
	{
	public:
		FPSCamera();
		FPSCamera(float AspectRatio);
		FPSCamera(float AspectRatio, glm::vec3 position, float Zoom = ZOOM, float yaw = YAW, float pitch = PITCH);

		//Euler Angles
		float Yaw;
		float Pitch;

		//Camera options
		float MovementSpeed;
		float MouseSensitvity;
		float Zoom;

		void ProcessKeyboard(ECameraMovement Direction, float deltaTime);

		void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

		void ProcessMouseScroll(float yOffset);
	};
}
