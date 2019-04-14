#pragma once

#include "Object.h"

namespace BHive
{
	class GameObject;

	class BHive_API ObjectComponent : public Object
	{
	public:
		ObjectComponent();
		virtual ~ObjectComponent();

		virtual void ComponentStart();
		virtual void ComponentUpdate(float DeltaTime);
		void SetParent(GameObject* gameObject);
		GameObject* GetParent();

	private:
		GameObject* parent;
	};
}

