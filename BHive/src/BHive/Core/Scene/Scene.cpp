#include "BHivePCH.h"
#include "Scene.h"

namespace BHive
{
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	Entity* Scene::CreateEntity()
	{
		Entity* entity = new Entity(m_Registry.create(), this);
		return entity;
	}

	void Scene::OnUpdate()
	{

	}

}