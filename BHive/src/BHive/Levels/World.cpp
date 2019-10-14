#include "BHivePCH.h"
#include "World.h"
#include "BHive/Statics/GameStatics.h"

namespace BHive
{
	World::World()
	{
		if (!GameStatics::GetWorld())
		{
			SetActive();
		}
	}

	void World::SetActive()
	{
		GameStatics::SetWorld(this);

		CreateWorld();

		Start();
	}
}
