#pragma once

namespace BHive
{
	class ComponentSystem
	{
	public:
		ComponentSystem();
		virtual ~ComponentSystem() = default;

		virtual void OnInitialize() = 0;
		virtual void OnUpdate(const Time& time, entt::registry& componentRegistry) = 0;

	private:
		void RegisterComponentSystem(ComponentSystem* system);
	};

	class RegisteredSystems
	{
	public:

		static void RegisterSystem(ComponentSystem* system)
		{
			m_ComponentSystems.emplace_back(system);
		}

		static std::vector<ComponentSystem*> m_ComponentSystems;
	};
}