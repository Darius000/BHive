#pragma once

#include "entt.hpp"
#include "BHive/Core/Scene/Scene.h"
#include "Components/Component.h"

namespace BHive
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity entityhandle, Scene* scene);
		Entity(const Entity& other) = default;
		~Entity() = default;

	public:
		void Destroy();
		bool IsBeingDestroyed() const { return m_BeingDestroyed; }
		
		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			BH_CORE_ASSERT(!HasComponent<T>(), "Component Already Exists!");

			auto& component = m_Scene->GetRegistry().emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			return component;
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

		int32 GetID() { return (int32)m_EntityHandle; }

		operator bool() const { return m_EntityHandle != entt::null; }

		operator uint32() const { return (uint32)m_EntityHandle; }

		bool operator==(const Entity& other) const 
		{ 
			return m_EntityHandle == other.m_EntityHandle && 
			m_Scene == other.m_Scene; 
		}

		bool operator!=(const Entity& other) const {
			return !(*this == other);
		}

		operator entt::entity() const { return m_EntityHandle; }

	private:
		entt::entity m_EntityHandle {entt::null};
		Scene* m_Scene = nullptr;
		bool m_BeingDestroyed = false;
	};

	class ScriptEntity
	{
	public:
		ScriptEntity() = default;	

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return m_Entity.AddComponent<T>(std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Entity.HasComponent<T>();
		}

		template<typename T>
		void RemoveComponent()
		{
			m_Entity.RemoveComponent<T>();
		}

	private:
		Entity m_Entity;
		friend class Scene;
	};

	class Player : public ScriptEntity
	{
	public:
		Player() = default;

		void OnCreate()
		{
			GetComponent<DirectionalLightComponent>().m_LightBrightness = 0.0f;
		}

		void OnUpdate(const Time& time)
		{
			GetComponent<DirectionalLightComponent>().m_LightBrightness += .001f;
		}
	};
}