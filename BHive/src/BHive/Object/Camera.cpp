#include "BHivePCH.h"
#include "Camera.h"

namespace BHive
{
	Camera::Camera()
	{

	}

	Camera::Camera(glm::mat4 projection)
		:m_Projection(projection)
	{

	}
}