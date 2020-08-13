#include "BHivePCH.h"
#include "ComponentSystem.h"


namespace BHive
{
	ComponentSystem::ComponentSystem()
	{
		RegisterComponentSystem(this);
	}

	void ComponentSystem::RegisterComponentSystem(ComponentSystem* system)
	{
		RegisteredSystems::RegisterSystem(system);
	}

	std::vector<ComponentSystem*> RegisteredSystems::m_ComponentSystems;

}