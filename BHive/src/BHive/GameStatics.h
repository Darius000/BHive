#pragma once

#include "Core.h"
#include "World.h"
#include "Cameras/Camera.h"

namespace BHive
{
	class BHive_API GameStatics 
	{
	public:
		static Camera* GetActiveCamera();
		static World* GetWorld();

		static void SetActiveCamera(Camera* camera);
		static void SetWorld(World* world);

	private:
		static Camera* currentCamera;
		static World* currentWorld;
	};
}

