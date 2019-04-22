#include "BHivePCH.h"
#include "GameObject.h"

namespace BHive
{
	GameObject::GameObject()
		 :rootComponent(0)
	{
		if(!rootComponent)
			rootComponent = AddComponent<TransformComponent>();
		rootComponent->SetDisplayName("Transform");
	}

	GameObject::~GameObject()
	{
		
	}

	void GameObject::Start()
	{
		Entity::Start();
	}

	void GameObject::Update(float deltaTime)
	{
		Entity::Update(deltaTime);
	}

	void GameObject::SetRootComponent(TransformComponent* component)
	{
		rootComponent = component;
	}

	TransformComponent* GameObject::GetRootComponent()
	{
		return rootComponent;
	}
}