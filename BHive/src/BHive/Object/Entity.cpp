#include "BHivePCH.h"
#include "Entity.h"

namespace BHive
{
	Entity::Entity() {};
	Entity::Entity(const std::string& name, entt::entity entityhandle, Scene* scene)
		:m_Name(name), m_EntityHandle(entityhandle),m_Scene(scene)
	{

	}

	void Entity::OnImGuiRender()
	{
		ImGui::Separator();
		ImGui::Text(*m_Name);
	}

}