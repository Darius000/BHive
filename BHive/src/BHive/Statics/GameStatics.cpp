#include "BHivePCH.h"
#include "GameStatics.h"

namespace BHive
{
	Camera* GameStatics::GetActiveCamera()
	{
		return currentCamera;
	}

	World* GameStatics::GetWorld()
	{
		return currentWorld;
	}

	void GameStatics::SetActiveCamera(Camera* camera)
	{
		currentCamera = camera;
	}

	void GameStatics::SetWorld(World* world)
	{
		currentWorld = world;
	}

	Camera* GameStatics::currentCamera = nullptr;

	World* GameStatics::currentWorld = nullptr;
}
