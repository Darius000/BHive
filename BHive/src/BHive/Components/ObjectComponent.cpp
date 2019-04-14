#include "BHivePCH.h"
#include "ObjectComponent.h"


namespace BHive
{
	ObjectComponent::ObjectComponent()
		:parent(0)
	{

	}

	ObjectComponent::~ObjectComponent()
	{

	}

	void ObjectComponent::ComponentStart()
	{

	}

	void ObjectComponent::ComponentUpdate(float DeltaTime)
	{
	}

	void ObjectComponent::SetParent(GameObject* gameObject)
	{
		parent = gameObject;
	}

	GameObject* ObjectComponent::GetParent()
	{
		return parent;
	}
}

