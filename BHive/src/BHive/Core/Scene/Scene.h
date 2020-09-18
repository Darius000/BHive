#pragma once

#include "entt.hpp"
#include "BHive/Systems/RenderSystem.h"

namespace BHive
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		Scene(const std::string& name);
		~Scene();

		Entity CreateEntity(const std::string& name);

		virtual void OnBegin();
		virtual void OnUpdate(const Time& time);
		virtual void OnEnd();

		void OnViewportResize(uint32 width, uint32 height);

	public:
		const std::string& GetName() const { return m_Name; }

		entt::registry& GetRegistry() { return m_Registry; }

	private:
		entt::registry m_Registry;

		std::string m_Name;

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