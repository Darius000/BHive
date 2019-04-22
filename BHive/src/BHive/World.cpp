#include "BHivePCH.h"
#include "World.h"
#include "Application.h"
#include "GameStatics.h"

namespace BHive
{
	World::World()
	{
		if (!GameStatics::GetWorld())
		{
			SetActive();
		}
	}

	void World::CreateWorld()
	{
		BH_INFO("Created Default World");
	}

	void World::SetActive()
	{
		GameStatics::SetWorld(this);

		CreateWorld();

		Start();
	}
}
