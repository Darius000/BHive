#pragma once

#include "BHivePCH.h"
#include "Object.h"

using ComponentID = std::size_t;

namespace BHive 
{

class Entity;
class Component;

//Generate a new ID and return last ID += 1
inline ComponentID GetComponentID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetComponentID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;


	class BHive_API Component : public Object
	{
	public:
		Entity* entity; //parent entity

		virtual void ComponentInit() {}; // Called when added to Entity
		virtual void ComponentStart() {};
		virtual void ComponentUpdate(float DeltaTime) {};
		Entity* GetParent() { return entity; }

		virtual ~Component() {};
	};

	class BHive_API Entity : public Object
	{
	private:
		std::vector<std::unique_ptr<Component>> components;

		ComponentArray componentArray;
		ComponentBitSet componentBitSet;

	public:
		virtual void Start() 
		{
			for (auto& c : components) c->ComponentStart();
		}

		virtual void Update(float deltaTime) 
		{
			for (auto& c : components) c->ComponentUpdate(deltaTime);
		}

		virtual void OnDestroyed() override 
		{
			for (auto& c : components) c->Destroy();
		}

		template <typename T> bool HasComponent() const {
			return componentBitSet[GetComponentID<T>()];
		}

		template <typename T, typename... TArgs>
		T* AddComponent(TArgs&&... mArgs)
		{
			T* c(new T(std::forward<TArgs>(mArgs)...));
			c->entity = this;
			std::unique_ptr<Component> uPtr{ c };
			components.emplace_back(std::move(uPtr));

			componentArray[GetComponentTypeID<T>()] = c;
			componentBitSet[GetComponentTypeID<T>()] = true;

			c->ComponentInit();
			return c;
		}

		template <typename T> T* GetComponent() const {
			auto ptr(componentArray[GetComponentTypeID<T>()]);
			return static_cast<T*>(ptr);
		}
	};

	class BHive_API EntityManager
	{
	private:
		std::vector<std::unique_ptr<Entity>> entities;

	public:
		void Start()
		{
			for (auto& e : entities) e->Start();
		}

		void Update(float deltaTime)
		{
			for (auto& e : entities) e->Update(deltaTime);
		}

		void Refresh()
		{
			entities.erase(std::remove_if(std::begin(entities), std::end(entities),
				[](const std::unique_ptr<Entity> &mEntity)
			{
				return !mEntity->IsDestroyed();
			}), std::end(entities));
		}

		template<typename T>
		T* AddEntity()
		{
			T* e = new T();
			std::unique_ptr<T> uPtr{ e };
			entities.emplace_back(std::move(uPtr));
			return e;
		}
	};
}
