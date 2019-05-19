#pragma once

namespace BHive
{
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

	template <typename T> bool Entity::HasComponent() const {
		return componentBitSet[GetComponentID<T>()];
	}

	template <typename T, typename... TArgs>
	T* Entity::AddComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->SetOwner(*this);
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[GetComponentTypeID<T>()] = c;
		componentBitSet[GetComponentTypeID<T>()] = true;

		c->ComponentInit();
		return c;
	}

	template <typename T> T* Entity::GetComponent() const {
		auto ptr(componentArray[GetComponentTypeID<T>()]);
		return static_cast<T*>(ptr);
	}
}