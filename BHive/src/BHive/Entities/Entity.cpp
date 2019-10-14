#include "BHivePCH.h"
#include "Entity.h"

namespace BHive
{
	Entity::Entity()
		:m_RootComponent(nullptr)
	{
		AddComponent<TransformComponent>();
	}

	Entity::~Entity()
	{
		
	}

	void Entity::Start()
	{
		for (auto& c : components) c->ComponentStart();
	}

	void Entity::Update(float deltaTime)
	{
		for (auto& c : components) c->ComponentUpdate(deltaTime);
	}

	void Entity::OnDestroyed()
	{
		for (auto& c : components) c->Destroy();
	}

	void Entity::SetRootComponent(TransformComponent& component)
	{
		m_RootComponent = &component;
	}

	/*void Entity::AttachComponentToRoot(TransformComponent& component)
	{
		//m_RootComponent->AddChild(component);
		component.AttachToComponent(*m_RootComponent);
	}*/

	void Entity::AttachToEntity(Entity& entity)
	{
		GetRootComponent()->AttachToEntity(entity);
	}

	void Entity::AttachToComponent(TransformComponent& component)
	{
		GetRootComponent()->AttachToComponent(component);
	}

	TransformComponent* Entity::GetRootComponent()
	{
		return m_RootComponent;
	}

	bool Entity::RemoveComponent(Component& component)
	{
		return false;
	}

	void Entity::AddComponent(Component& component)
	{

	}

}