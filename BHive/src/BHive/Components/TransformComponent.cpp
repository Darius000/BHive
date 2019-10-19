#include "BHivePCH.h"
#include "TransformComponent.h"
#include "BHive/Object/Entity.h"

namespace BHive
{
	TransformComponent::TransformComponent()
		:m_Parent(nullptr)
	{
		m_Transform.OnTransformUpdated.AddBinding(BIND_EVENT_ONE_PARAM(&TransformComponent::UpdateTransformation));
	}

	Transform TransformComponent::GetAbsoluteTransform()
	{
		TransformComponent * parent = GetParent();

		FVector3 location = m_RelativeTransform.GetPosition();
		Rotator rotation = m_RelativeTransform.GetRotation();
		FVector3 scale = m_RelativeTransform.GetScale();
		FVector3 pScale = parent->GetTransform().GetScale();

		//Loop through hierarchy to get locations to add to get absolute location
		while (parent != nullptr)
		{
			location += parent->GetTransform().GetPosition();
			rotation += parent->GetTransform().GetRotation();
			scale.x *= pScale.x;
			scale.y *= pScale.y;
			scale.z *= pScale.z;

			parent = parent->GetParent(); //get the next parent
		}

		return Transform(location, rotation, scale);
	}

	void TransformComponent::SetRelativeTransform(const Transform& transform)
	{
		m_RelativeTransform = transform;

		UpdateRelativeTransform();
	}

	Transform TransformComponent::GetRelativeTransform()
	{
		return m_RelativeTransform;
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

			UpdateRelativeTransform();
		}

		return;
	}

	void TransformComponent::RemoveChild(TransformComponent& child)
	{
		ChildComponents::iterator it = std::find(children.begin(), children.end(), &child);

		if(it != children.end())
			children.erase(it);
	}

	void TransformComponent::OnTransformUpdated(const Transform& transform)
	{
		//BH_CORE_TRACE("TransformComponent OnTransformUpdate!");

		for (auto& c : children)
		{
			c->UpdateRelativeTransform();
		}
	}

	void TransformComponent::UpdateTransformation(const Transform& transform)
	{
		OnTransformUpdated(transform);
	}

	void TransformComponent::UpdateRelativeTransform()
	{
		FVector3 relLocation = m_RelativeTransform.GetPosition();
		Rotator relRotation = m_RelativeTransform.GetRotation();
		FVector3 relScale	= m_RelativeTransform.GetScale();
		FVector3 pScale		= m_Parent->m_Transform.GetScale();

 		m_Transform.SetPosition(relLocation + m_Parent->m_Transform.GetPosition());
		m_Transform.SetRotation(relRotation + m_Parent->m_Transform.GetRotation());
		m_Transform.SetScale(relScale.x * pScale.x, relScale.y * pScale.y, relScale.z * pScale.z);
	}
}