#pragma once

#include "entt.hpp"
#include "BHive/Core/Scene/Scene.h"

namespace BHive
{
	class Entity
	{
	public:
		Entity();
		Entity(const std::string& name, entt::entity entityhandle, Scene* scene);
		Entity(const Entity& other) = default;
		
		void OnImGuiRender();

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			BH_CORE_ASSERT(!HasComponent<T>(), "Component Already Exists!");

			return m_Scene->GetRegistry().emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			BH_CORE_ASSERT(HasComponent<T>(), "Component Doesn't Exists!");

			return m_Scene->GetRegistry().get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->GetRegistry().has<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			BH_CORE_ASSERT(HasComponent<T>(), "Component Doesn't Exists!");

			m_Scene->GetRegistry().remove<T>(m_EntityHandle);
		}

		std::string& GetName() {return m_Name; }

	private:
		std::string m_Name;
		entt::entity m_EntityHandle {entt::null};
		Scene* m_Scene = nullptr;
	};
}