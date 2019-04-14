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


	World::~World()
	{
	}

	std::vector<std::unique_ptr<GameObject>> World::children;

	void World::RemoveChild(const GameObject& object)
	{
		auto it = std::find_if(children.begin(), children.end(), ErasePredicateUnique<GameObject>(object));

		children.erase(it);
	}

	void World::CreateWorld()
	{
		BH_INFO("Created World");
	}

	void World::RenderChildren(float deltaTime)
	{
		for (auto it = children.begin(); it != children.end();)
		{
			if (!(*it)->IsDestroyed())
			{
				(*it)->Update(deltaTime);
				++it;
			}
			else
			{
				it = children.erase(it);
			}

		}
	}

	void World::InitChildren()
	{
		CreateWorld();

		for (auto it = children.begin(); it != children.end(); ++it)
		{
			(*it)->Start();
		}
	}

	void World::SetActive()
	{
		GameStatics::SetWorld(this);

		InitChildren();		
	}
}
