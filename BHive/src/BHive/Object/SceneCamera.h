#pragma once

#include "Camera.h"

namespace BHive
{
	enum class Projection : uint32
	{
		Perspective = 0,
		Orthographic = 1,
		
	};

	struct OrthographicSettings
	{
		float Size = 1.0f;
		float Near = -1.0f;
		float Far = 1.0f;
	};

	struct PerspectiveSettings
	{
		float FieldofView = 35.0f;
		float Near = .01f;
		float Far = 1000.0f;
	}; 

	class SceneCamera : public Camera 
	{
	public:
		SceneCamera();
		virtual ~SceneCamera();

		void SetOrthographic(OrthographicSettings settings);
		void SetPerspective(PerspectiveSettings settings);
		void RecalculateProjection();
		void OnViewportResize(uint32 width, uint32 height);

		OrthographicSettings m_OrthographicSettings;
		PerspectiveSettings m_PerspectiveSettings;
		Projection m_CurrentProjection = Projection::Orthographic;
		float m_AspectRatio = 0.0f;

		friend struct CameraComponent;
	};
}