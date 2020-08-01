#include "BHivePCH.h"
#include "Camera.h"

namespace BHive
{
	Camera::Camera()
		:Camera(Projection::Perspective)
	{

	}

	Camera::Camera(Projection projection)
		: m_ProjectionType(Projection::Perspective), m_Projection(1.0f), m_PerspSettings(), m_OrthoSettings()
	{
		if (projection == Projection::Perspective)
		{
			SetPerspective(m_PerspSettings);
		}
		else
		{
			SetOthographic(m_OrthoSettings);
		}
	}

	void Camera::SetPerspective(PerspectiveSettings perspective)
	{
		m_ProjectionType = Projection::Perspective;
		m_PerspSettings = perspective;
		float aspectRatio = perspective.AspectRatio.x / perspective.AspectRatio.y;
		m_Projection = glm::perspective(glm::radians(perspective.FieldofView), aspectRatio,
			perspective.Near, perspective.Far);
	}

	void Camera::SetOthographic(OrthographicSettings orthographic)
	{
		m_ProjectionType = Projection::Orthographic;
		m_OrthoSettings = orthographic;
		m_Projection = glm::ortho(orthographic.Left, orthographic.Right, orthographic.Bottom, orthographic.Top,
			orthographic.Near, orthographic.Far);
	}
}