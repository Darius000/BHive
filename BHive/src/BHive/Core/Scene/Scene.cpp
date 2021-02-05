#include "BHivePCH.h"
#include "Scene.h"
#include "Components/Component.h"


namespace BHive
{
	Scene::Scene()
		:Scene("New Scene")
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
		Entity entity = {m_Registry.create(), this};
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::DeleteEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::OnBegin()
	{
		InitializeCamera({0.0f, 20.0f, 20.0f});
		InitializeUniformBlocks();

		//Update Scripts----------------------------------------------------
		{
			auto view = m_Registry.view<NativeScriptComponent>();
			for (auto entity : view)
			{
				auto nsc = view.get<NativeScriptComponent>(entity);
				if (nsc.OnCreateFunc)
				{
					if (!nsc.Instance)
					{
						nsc.InstantiateFunc();
					}

					nsc.Instance->m_Entity = Entity{ entity , this };

					nsc.OnCreateFunc(nsc.Instance.get());
				}

			}
		}

		for (auto& system : RegisteredSystems::m_ComponentSystems)
		{
			system->OnInitialize();
		}
	}

	/*void Scene::OnUpdateEditor(const Time& time, EditorCamera& Camera)
	{

	}*/

	void Scene::OnUpdateRuntime(const Time& time)
	{
		SendDefaultCameraParametersToShaders();

		for (auto& system : RegisteredSystems::m_ComponentSystems)
		{
			system->OnUpdate(time, m_Registry);
		}	

		//Update Scripts----------------------------------------------------
		{
			auto view = m_Registry.view<NativeScriptComponent>();
			for(auto entity : view)
			{
				auto nsc = view.get<NativeScriptComponent>(entity);
				if (nsc.OnUpdateFunc)
				{
					if (!nsc.Instance)
					{
						nsc.InstantiateFunc();
					}

					nsc.Instance->m_Entity = Entity{ entity , this };

					nsc.OnUpdateFunc(nsc.Instance.get(), time);
				}

			}
		}
	}

	void Scene::OnEnd()
	{
		//Update Scripts----------------------------------------------------
		{
			auto view = m_Registry.view<NativeScriptComponent>();
			for (auto entity : view)
			{
				auto nsc = view.get<NativeScriptComponent>(entity);
				if (nsc.OnDestroyFunc)
				{
					if (!nsc.Instance)
					{
						nsc.InstantiateFunc();
					}

					nsc.Instance->m_Entity = Entity{ entity , this };

					nsc.OnDestroyFunc(nsc.Instance.get());
				}

			}
		}
	}

	void Scene::OnViewportResize(uint32 width, uint32 height)
	{
		m_RenderSystem.OnViewportResize(width, height, m_Registry);
		m_DefaultSceneView.m_Camera.OnViewportResize(width, height);
	}

	void Scene::InitializeCamera(const FVector3& position)
	{
		m_DefaultSceneView.m_Transform.SetPosition(position);
		m_DefaultSceneView.m_Transform.LookAt({0.0f, 0.0f, 0.0f});
		m_DefaultSceneView.m_Camera.SetPerspective({ 35.0f, .01f, 1000.0f });
	}

	void Scene::SendDefaultCameraParametersToShaders()
	{
		auto& camera = m_DefaultSceneView.m_Camera;
		auto& transform = m_DefaultSceneView.m_Transform;

		glm::mat4 m_ProjectionMatrix = camera.GetProjection();

		glm::mat4 matrix = transform.GetMatrix();
		glm::mat4 m_ViewMatrix = glm::inverse(matrix);
		glm::mat4 m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

		UniformBlock* matrices = m_MatrixBlocks["Matrices"];
		matrices->SendData(0, &m_ViewProjectionMatrix);
		matrices->SendData(sizeof(glm::mat4), &m_ViewMatrix);
		matrices->SendData(sizeof(glm::mat4) + sizeof(Vector3<float>), &transform.GetPosition());
	}

	void Scene::InitializeUniformBlocks()
	{
		UniformBlock* matricesBlock = new UniformBlock("Matrices", 2 * sizeof(glm::mat4) + sizeof(Vector3<float>));

		m_MatrixBlocks.insert({ matricesBlock->m_Name, matricesBlock });

		for (auto& a : AssetManager::GetAssets<Shader>())
		{
			matricesBlock->Bind(a.second, 0);
		}
	}

	Scene* SceneManager::CreateScene(const std::string& name)
	{
		Scope<Scene> scene = Make_Scope<Scene>(name);
		AddScene(scene);
		return m_Scenes[name].get();
	}

	void SceneManager::SetActiveScene(const std::string& name)
	{
		BH_CORE_ASSERT(HasScene(name), "Scene doesn't existed!");
		if (m_ActiveScene)
		{
			m_ActiveScene->OnEnd();
		}

		m_ActiveScene = m_Scenes[name].get();
		m_ActiveScene->OnBegin();
	}

	void SceneManager::DestroyScene(const std::string& name)
	{
		BH_CORE_ASSERT(!HasScene(name), "Scene doesn't existed!");
		BH_CORE_ASSERT(m_ActiveScene != m_Scenes[name].get(), "Scene currently Active! Cannot Destroy!");

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

	Scene* SceneManager::m_ActiveScene = nullptr;
}