#include "BHivePCH.h"
#include "FPSCamera.h"


namespace BHive
{
	FPSCamera::FPSCamera()
	{

	}

	FPSCamera::FPSCamera(float AspectRatio)
		:Camera(AspectRatio), MovementSpeed(SPEED), MouseSensitvity(SENSITIVITY), Yaw(YAW), Pitch(PITCH), Zoom(Fov)
	{
		
	}


	FPSCamera::FPSCamera(float AspectRatio, const Vector3& position, float Zoom /*= ZOOM*/, float yaw /*= YAW*/, float pitch /*= PITCH*/)
		:Camera(AspectRatio, position), MovementSpeed(SPEED), MouseSensitvity(SENSITIVITY)
	{

	}

	void FPSCamera::ProcessKeyboard(ECameraMovement Direction, float deltaTime)
	{
		Transform transform = GetRootComponent()->GetTransform();

		Vector3 pos = transform.GetPosition();

		float velocity = MovementSpeed * deltaTime;
		if (Direction == FOWARD)
		{
			pos += transform.GetForward() * velocity;
		}
		if (Direction == BACKWARD)
		{
			pos -= transform.GetForward() * velocity;
		}
		if (Direction == LEFT)
		{
			pos -= transform.GetRight() * velocity;
		}
		if (Direction == RIGHT)
		{
			pos += transform.GetRight() * velocity;
		}

		pos.y = 0.0f;

		transform.SetPosition(pos);
	}

	void FPSCamera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch /*= true*/)
	{
		float X = xOffset * MouseSensitvity;
		float Y = yOffset * MouseSensitvity;

		Yaw = X;
		Pitch = Y;

		if (constrainPitch)
		{
			if (Pitch > 89.0f)
			{
				Pitch = 89.0f;
			}

			if (Pitch < -89.0f)
			{
				Pitch = -89.0f;
			}
		}

		GetRootComponent()->GetTransform().SetRotation(Rotator(-Pitch, Yaw, 0.0f));
	}

	void FPSCamera::ProcessMouseScroll(float yOffset)
	{
		if (Zoom >= 1.0f && Zoom <= 45.0f)
		{
			Zoom -= (float)yOffset;
		}

		if (Zoom <= 1.0f)
		{
			Zoom = 1.0f;
		}

		if (Zoom >= 45.0f)
		{
			Zoom = 45.0f;
		}

		Fov = Zoom;
	}
}