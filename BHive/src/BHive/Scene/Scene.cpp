#include "BHivePCH.h"
#include "Scene.h"

namespace BHive
{
	Scene::Scene(CameraComponent& camera)
		:m_SceneData(nullptr)
	{
		m_SceneData = new SceneData(camera);
	}

	void Scene::Begin()
	{
		for (auto& e : m_SceneData->m_Entities) e->Start();
	}

	void Scene::Update(const Time& time)
	{
		for (auto& e : m_SceneData->m_Entities) e->Update(time);
		Refresh();
	}

	void Scene::End()
	{
		delete m_SceneData;
	}

	void Scene::Refresh()
	{
		m_SceneData->m_Entities.erase(std::remove_if(std::begin(m_SceneData->m_Entities), std::end(m_SceneData->m_Entities),
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return mEntity->IsDestroyed();
		}), std::end(m_SceneData->m_Entities));
	}

	Scene::SceneData::SceneData(CameraComponent& camera) :m_Camera(&camera), m_VPM(glm::mat4(1.0f))
	{

	}

}