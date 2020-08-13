#include "BHivePCH.h"
#include "SceneCamera.h"

namespace BHive
{

	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	SceneCamera::~SceneCamera()
	{

	}

	void SceneCamera::SetOrthographic(OrthographicSettings settings)
	{
		m_CurrentProjection = Projection::Orthographic;

		m_OrthographicSettings = settings;

		RecalculateProjection();
	}

	void SceneCamera::SetPerspective(PerspectiveSettings settings)
	{
		m_CurrentProjection = Projection::Perspective;
		m_PerspectiveSettings = settings;

		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		if(m_CurrentProjection == Projection::Orthographic)
		{
			float orthoRight = m_OrthographicSettings.Size * m_AspectRatio * 0.5f;
			float orthoLeft = -m_OrthographicSettings.Size * m_AspectRatio * 0.5f;
			float orthoBottom = -m_OrthographicSettings.Size * 0.5f;
			float orthoTop = m_OrthographicSettings.Size * 0.5f;
			m_Projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop,
				m_OrthographicSettings.Near, m_OrthographicSettings.Far);
			return;
		}
		else 
		{
			m_Projection = glm::perspective(glm::radians(m_PerspectiveSettings.FieldofView), m_AspectRatio,
				m_PerspectiveSettings.Near, m_PerspectiveSettings.Far);
			return;
		}
	}

	void SceneCamera::OnViewportResize(uint32 width, uint32 height)
	{
		m_AspectRatio = float(width)/(float)height;
		RecalculateProjection();
	}
}