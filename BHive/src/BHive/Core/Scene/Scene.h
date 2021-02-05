#pragma once

#include "entt.hpp"
#include "BHive/Systems/RenderSystem.h"
#include "Renderer/UniformBlock.h"
#include "Object/SceneCamera.h"

namespace BHive
{
	class Entity;

	struct DefaultSceneView
	{
		class SceneCamera m_Camera;
		Transform m_Transform;
	};

	class Scene
	{
	public:
		Scene();
		Scene(const std::string& name);
		~Scene();

		Entity CreateEntity(const std::string& name);
		void DeleteEntity(Entity entity);

		void OnBegin();
		//void OnUpdateEditor(const Time& time, EditorCamera& Camera);
		void OnUpdateRuntime(const Time& time);
		void OnEnd();

		void OnViewportResize(uint32 width, uint32 height);

	private:
		void InitializeCamera(const FVector3& position);
		void SendDefaultCameraParametersToShaders();
		void InitializeUniformBlocks();

	public:
		const std::string& GetName() const { return m_Name; }

		entt::registry& GetRegistry() { return m_Registry; }

		DefaultSceneView m_DefaultSceneView;

	private:
		entt::registry m_Registry;

		std::string m_Name;

		std::unordered_map<const char*, UniformBlock*> m_MatrixBlocks;

	private:
	//Systems
		RenderSystem m_RenderSystem;

		friend class SceneHierarchyPanel;
	};

	class SceneManager
	{
	public:
		static Scene* CreateScene(const std::string& name);

	public:
		static Scene* GetActiveScene() { return m_ActiveScene; }
		static void SetActiveScene(const std::string& name);
	protected:
		static void DestroyScene(const std::string& name);
		static void AddScene(Scope<Scene>& scene);		
		static const bool HasScene(const std::string& name);

	private:
		static std::unordered_map<std::string, Scope<Scene>> m_Scenes;
		static Scene* m_ActiveScene;
	};
}