#include "BHivePCH.h"
#include "Scene.h"

namespace BHive
{
	Scene::Scene(CameraComponent& camera)
		:m_Camera(&camera)
	{
		
	}

	void Scene::Start()
	{
		for (auto& e : m_Entities) e->Start();
	}

	void Scene::Update(const Time& time)
	{
		for (auto& e : m_Entities) e->Update(time);
		Refresh();
	}

	void Scene::Refresh()
	{
		m_Entities.erase(std::remove_if(std::begin(m_Entities), std::end(m_Entities),
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return mEntity->IsDestroyed();
		}), std::end(m_Entities));
	}
}