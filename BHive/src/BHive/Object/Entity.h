#pragma once

#include "entt.hpp"
#include "BHive/Core/Scene/Scene.h"

namespace BHive
{
	class Entity
	{
	public:
		Entity();
		Entity(entt::entity entityhandle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			BH_CORE_ASSERT(HasComponent<T>(), "Component Already Exists!");

			m_Scene.m_Registry.emplace(m_EntityHandle, std::forward<Args>(args));
		}

		template<typename T>
		T* GetComponent()
		{
			BH_CORE_ASSERT(!HasComponent<T>(), "Component Doesn't Exists!");

			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			BH_CORE_ASSERT(!HasComponent<T>(), "Component Doesn't Exists!");

			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

	private:
		entt::entity m_EntityHandle = {entt::null};
		Scene* m_Scene = nullptr;
	};
}