#include "BHivePCH.h"
#include "Camera.h"
#include "GameStatics.h"


namespace BHive
{
	Camera::Camera()
		:Entity(), Fov(45.0f), Near(.1f), Far(100.0f)
	{
		if (!GameStatics::GetActiveCamera())
		{
			GameStatics::SetActiveCamera(this);
		}
	}

	Camera::Camera(float AspectRatio)
		:Camera()
	{
		aspectRatio = AspectRatio;
	}

	Camera::Camera(float AspectRatio, const Vector3& position)
		: Camera(AspectRatio)
	{
		GetTransform().SetPosition(position);
	}

	Camera::~Camera()
	{

	}

	void Camera::SetActive()
	{
		GameStatics::SetActiveCamera(this);
	}

	glm::mat4 Camera::GetViewMatrix()
	{
		return LookAt(GetTransform().GetPosition() + GetTransform().GetForward());
	}

	glm::mat4 Camera::GetProjectionMatrix()
	{
		return glm::perspective(glm::radians(Fov), aspectRatio, Near, Far);
	}

	glm::mat4 Camera::LookAt(const Vector3& target)
	{
		Vector3 ZAxis = (GetTransform().GetPosition() - target).Normalize(); //forward
		Vector3 XAxis = GetTransform().GetRight(); //right
		Vector3 YAxis = GetTransform().GetUp();//up

		glm::mat4 translation;
		translation[3][0] = -GetTransform().GetPosition().x;
		translation[3][1] = -GetTransform().GetPosition().y;
		translation[3][2] = -GetTransform().GetPosition().z;

		glm::mat4 rotation;
		rotation[0][0] = XAxis.x;
		rotation[1][0] = XAxis.y;
		rotation[2][0] = XAxis.z;
		rotation[0][1] = YAxis.x;
		rotation[1][1] = YAxis.y;
		rotation[2][1] = YAxis.z;
		rotation[0][2] = ZAxis.x;
		rotation[1][2] = ZAxis.y;
		rotation[2][2] = ZAxis.z;

		return rotation * translation;
	}
}