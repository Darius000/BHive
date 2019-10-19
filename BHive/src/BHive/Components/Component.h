#pragma once

#include "BHive/Object/Object.h"

namespace BHive
{
	class Entity;

	//add get relative

	class BHive_API Component : public Object
	{
		BCLASS(Component, ComponentCategory, Object)

	public:
		Component() :m_Owner(nullptr) {};
		virtual ~Component() {};

		virtual void ComponentInit() {};
		virtual void ComponentStart() {};
		virtual void ComponentUpdate(const Time& time) {};
		//void SetOwner(Entity& entity); remove component from eniy and add to new one
		Entity* GetOwner() const { return m_Owner; };
	
	private:
		Entity* m_Owner;
		
	};
}

