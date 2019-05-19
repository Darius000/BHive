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
		Component() :m_Entity(nullptr) {};
		virtual ~Component() {};

		virtual void ComponentInit() {};
		virtual void ComponentStart() {};
		virtual void ComponentUpdate(float DeltaTime) {};
		void SetOwner(Entity& entity);
		Entity* GetOwner() const { return m_Entity; };
	
	private:
		Entity* m_Entity;
		
	};
}

