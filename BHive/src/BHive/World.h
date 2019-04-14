#pragma once

#include "GameObject.h"

namespace BHive
{
	class BHive_API World
	{

	public:
		World();
		virtual ~World();

		static std::vector<std::unique_ptr<GameObject>> children;

		template<class T>
		T* AddChild();

		void RemoveChild(const GameObject& object);

		//Override Create World in subclasses. Default includes preview
		virtual void CreateWorld();

		void RenderChildren(float deltaTime);

		void InitChildren();

		void SetActive();	
	};

	template<class T> 
	T* BHive::World::AddChild()
	{
		auto it = std::unique_ptr<T>(new T());
		T* itRef = it.get();
		children.push_back(std::move(it));
		return itRef;
	}
}


