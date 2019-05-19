#include "BHivePCH.h"
#include "Entity.h"

namespace BHive
{
	Entity::Entity()
		:m_RootComponent(nullptr)
	{
		TransformComponent* root = AddComponent<TransformComponent>();
		SetRootComponent(*root);
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

	TransformComponent* Entity::GetRootComponent()
	{
		return m_RootComponent;
	}
}