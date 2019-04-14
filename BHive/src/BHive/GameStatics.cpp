#include "BHivePCH.h"
#include "GameStatics.h"

namespace BHive
{

	GameStatics::GameStatics()
	{
		if (!s_Instance)
		{
			s_Instance = this;
		}
	}

	GameStatics::~GameStatics()
	{

	}

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

	Camera* GameStatics::currentCamera;

	World* GameStatics::currentWorld;

	GameStatics* GameStatics::s_Instance;
}
