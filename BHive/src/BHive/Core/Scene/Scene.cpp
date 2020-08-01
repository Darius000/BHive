#include "BHivePCH.h"
#include "Scene.h"
#include "Components/RenderComponent.h"
#include "Components/TransformComponent.h"
#include "Components/CameraComponents.h"

namespace BHive
{
	Scene::Scene()
	{

	}

	Scene::Scene(const std::string& name)
		:m_Name(name)
	{

	}

	Scene::~Scene()
	{

	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = {name, m_Registry.create(), this};
		entity.AddComponent<TransformComponent>();
		return entity;
	}

	void Scene::OnBegin()
	{
		
	}

	void Scene::OnUpdate(const Time& time)
	{
		{
			auto group = m_Registry.view<RenderComponent, TransformComponent>();
			for (auto entity : group)
			{
				auto& render = group.get<RenderComponent>(entity);
				auto& transform = group.get<TransformComponent>(entity);
				render.m_Model->SetTransform(transform.m_Transform);
				render.Draw();
			}
		}
		{
			auto group = m_Registry.view<CameraComponent, TransformComponent>();
			for (auto entity : group)
			{
				auto& camera = group.get<CameraComponent>(entity);
				auto& transform = group.get<TransformComponent>(entity);

				CameraComponent* ActiveCamera = CameraSystem::m_ActiveCamera;
				if(ActiveCamera == &camera)
				{ 
					glm::mat4 m_ProjectionMatrix = camera.m_Camera.GetProjection();

					glm::mat4 matrix = transform.m_Transform.GetMatrix();
					glm::mat4 m_ViewMatrix = glm::inverse(matrix);
					glm::mat4 m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
					ShaderLibrary::UpdateShaderViewProjectionMatrices(m_ViewProjectionMatrix);
				}
			}
		}
	}

	void Scene::OnEnd()
	{
		
	}

	Scene* SceneManager::CreateScene(const std::string& name)
	{
		Scope<Scene> scene(new Scene(name));
		AddScene(scene);
		return m_Scenes.find(name)->second.get();
	}

	void SceneManager::SetActiveScene(const std::string& name)
	{
		BH_CORE_ASSERT(HasScene(name), "Scene doesn't existed!");
		m_ActiveScene = m_Scenes[name].get();
	}

	void SceneManager::DestroyScene(const std::string& name)
	{
		BH_CORE_ASSERT(!HasScene(name), "Scene doesn't existed!");
		m_Scenes.erase(name);
	}

	void SceneManager::AddScene(Scope<Scene>& scene)
	{
		BH_CORE_ASSERT(!HasScene(scene->GetName()), "Scene already exists!");
		m_Scenes.emplace(scene->GetName(), std::move(scene));
	}

	const bool SceneManager::HasScene(const std::string& name)
	{
		return m_Scenes.find(name) != m_Scenes.end();
	}

	std::unordered_map<std::string, Scope<Scene>> SceneManager::m_Scenes;

	Scene* SceneManager::m_ActiveScene;
}