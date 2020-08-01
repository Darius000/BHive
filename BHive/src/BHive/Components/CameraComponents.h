#pragma once

#include "Object/Camera.h"

namespace BHive
{
	class CameraComponent;

	class CameraSystem
	{
	public:
		CameraSystem() = default;
		static CameraComponent* m_ActiveCamera;
	};

	class CameraComponent
	{
	public:
		CameraComponent()
		{
			if (CameraSystem::m_ActiveCamera == nullptr)
			{
				SetPrimaryCamera(true);
			}
		}
		CameraComponent(Projection projection);
		CameraComponent(const CameraComponent&) = default;

		void OnImGuiRender();

		void SetPrimaryCamera(bool active)
		{
			if(active) CameraSystem::m_ActiveCamera = this;
		}

		Camera m_Camera;
	};

	
}