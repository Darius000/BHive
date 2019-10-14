#include "BHivePCH.h"
#include "TransformComponent.h"
#include "BHive/Entities/Entity.h"

namespace BHive
{
	TransformComponent::TransformComponent()
		:m_Parent(nullptr)
	{
		m_Transform.OnTransformUpdated.AddBinding(BIND_EVENT_ONE_PARAM(&TransformComponent::OnTransformUpdated));
	}

	Vector3 TransformComponent::GetAbsoluteLocation()
	{
		Vector3 location = m_RelativeLocation;
		TransformComponent * parent = GetParent();

		//Loop through hierarchy to get locations to add to get absolute location
		while (parent != nullptr)
		{
			location += parent->GetTransform().GetPosition();
			parent = parent->GetParent(); //get the next parent
		}

		return location;
	}

	void TransformComponent::SetRelativeLocation(Vector3& location)
	{
		m_RelativeLocation = location;

		UpdateRelativeLocation();
	}

	Vector3 TransformComponent::GetRelativeLocation()
	{
		return m_RelativeLocation;
	}

	void TransformComponent::AddChild(TransformComponent& child)
	{
		//check to if child parent isn't this component
		if (child.m_Parent != this)
		{
			//if parent exists remove he child from it
			if(child.m_Parent != nullptr)
				child.m_Parent->RemoveChild(child);

			//set child parent to this
			child.m_Parent = this;
			children.push_back(&child);
		}

		return;
	}

	void TransformComponent::AttachToEntity(Entity& entity)
	{
		/*if (GetOwner() != &entity)
		{
			SetOwner(entity);
		}*/

		AttachToComponent(*entity.GetRootComponent());
	}

	void TransformComponent::AttachToComponent(TransformComponent& parent)
	{
		if (m_Parent != &parent)
		{
			if (m_Parent != nullptr)
				m_Parent->RemoveChild(*this);

			m_Parent = &parent;
			m_Parent->children.push_back(this);

			UpdateRelativeLocation();
		}

		return;
	}

	void TransformComponent::RemoveChild(TransformComponent& child)
	{
		ChildComponents::iterator it = std::find(children.begin(), children.end(), &child);

		if(it != children.end())
			children.erase(it);
	}

	void TransformComponent::UpdateRelativeLocation()
	{
		m_Transform.SetPosition(m_RelativeLocation + m_Parent->m_Transform.GetPosition());
	}

	void TransformComponent::OnTransformUpdated(const Transform& transform)
	{
		
	}
}