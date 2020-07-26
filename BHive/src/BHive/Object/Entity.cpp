#include "BHivePCH.h"
#include "Entity.h"

namespace BHive
{
	Entity::Entity() {};
	Entity::Entity(entt::entity entityhandle, Scene* scene)
		:m_EntityHandle(entityhandle),m_Scene(scene)
	{

	}
}