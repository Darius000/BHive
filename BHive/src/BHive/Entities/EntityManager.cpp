#include "BHivePCH.h"
#include "EntityManager.h"

namespace BHive
{
	void EntityManager::Start()
	{
		for (auto& e : entities) e->Start();
	}

	void EntityManager::Update(float deltaTime)
	{
		for (auto& e : entities) e->Update(deltaTime);
	}

	void EntityManager::Refresh()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->IsDestroyed();
		}), std::end(entities));
	}
}