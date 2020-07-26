#pragma once

#include "entt.hpp"

namespace BHive
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity* CreateEntity();

		void OnUpdate();

	private:
		entt::registry m_Registry;
	};
}