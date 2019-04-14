#include "BHivePCH.h"
#include "GameObject.h"

namespace BHive
{
	GameObject::GameObject()
		:destroyed(false), rootComponent(0)
	{
		if(!rootComponent)
			rootComponent = AddComponent<TransformComponent>("Transform");
	}

	GameObject::~GameObject()
	{
		for (auto i = components.begin(); i != components.end();)
		{
			if ((*i)->IsDestroyed())
			{
				i = components.erase(i);
			}
			else
			{
				++i;
			}
		}
	}

	void GameObject::Start()
	{
		for (auto it = components.begin(); it != components.end(); ++it)
		{
			(*it)->ComponentStart();
		}
	}

	void GameObject::Update(float deltaTime)
	{
		for (auto it = components.begin(); it != components.end();)
		{
			if (!(*it)->IsDestroyed())
			{
				(*it)->ComponentUpdate(deltaTime);
				++it;
			}
		}
	}

	void GameObject::SetRootComponent(TransformComponent* component)
	{
		rootComponent = component;
	}

	TransformComponent* GameObject::GetRootComponent()
	{
		return rootComponent;
	}

	bool GameObject::IsDestroyed()
	{
		return destroyed;
	}

	void GameObject::OnDestroyed()
	{
		Object::OnDestroyed();

		for (auto i = components.begin(); i != components.end(); ++i)
		{
			(*i)->Destroy();
		}
	}
}