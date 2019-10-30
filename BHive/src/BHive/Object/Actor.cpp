#include "BHivePCH.h"
#include "Actor.h"

namespace BHive
{
	Actor::Actor()
		:m_RootComponent(nullptr)
	{
		AddComponent<TransformComponent>();
	}

	Actor::~Actor()
	{
		
	}

	void Actor::Start()
	{
		for (auto& c : components) c->ComponentStart();
	}

	void Actor::Update(const Time& time)
	{
		for (auto& c : components) c->ComponentUpdate(time);
	}

	void Actor::OnDestroyed()
	{
		for (auto& c : components) c->Destroy();
	}

	void Actor::SetRootComponent(TransformComponent& component)
	{
		m_RootComponent = &component;
	}

	/*void Entity::AttachComponentToRoot(TransformComponent& component)
	{
		//m_RootComponent->AddChild(component);
		component.AttachToComponent(*m_RootComponent);
	}*/

	void Actor::AttachToEntity(Actor& entity)
	{
		GetRootComponent()->AttachToEntity(entity);
	}

	void Actor::AttachToComponent(TransformComponent& component)
	{
		GetRootComponent()->AttachToComponent(component);
	}

	TransformComponent* Actor::GetRootComponent()
	{
		return m_RootComponent;
	}

	bool Actor::RemoveComponent(Component& component)
	{
		return false;
	}

	void Actor::AddComponent(Component& component)
	{

	}

}