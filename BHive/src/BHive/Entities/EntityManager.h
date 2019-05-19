#pragma once

#include "Core.h"
#include "Entity.h"

namespace BHive
{
	class BHive_API EntityManager
	{
	private:
		std::vector<std::unique_ptr<Entity>> entities;

	public:
		void Start();

		void Update(float deltaTime);

		void Refresh();

		template<typename T>
		T* AddEntity();
	};
}

#include "EntityManager.inl"