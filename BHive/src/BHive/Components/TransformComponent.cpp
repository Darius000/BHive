#include "BHivePCH.h"
#include "TransformComponent.h"
#include "BHive/Entities/Entity.h"

namespace BHive
{

	TransformComponent::TransformComponent() :m_Parent(nullptr)
	{
		m_Transform.OnTransformUpdated.AddBinding(BIND_EVENT_ONE_PARAM(&TransformComponent::OnTransformUpdated));
	}

	Vector3 TransformComponent::GetRelativePosition() const
	{
		Vector3 pos = GetTransform().GetPosition();
		pos += GetParentComponent() ?  GetParentComponent()->GetTransform().GetPosition() : Vector3::Zero();
		pos += GetOwner() ? GetOwner()->GetTransform().GetPosition() : Vector3::Zero();
		return pos;
	}

	void TransformComponent::OnTransformUpdated(const Transform& newTranform)
	{
		//Update the children attached to this component
		BH_CORE_INFO("Updated Transform and Children");
	}
}