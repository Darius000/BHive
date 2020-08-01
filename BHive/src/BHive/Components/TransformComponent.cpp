#include "BHivePCH.h"
#include "TransformComponent.h"

namespace BHive
{


	//Transform TransformComponent::GetAbsoluteTransform()
	//{
	//	TransformComponent * parent = GetParent();

	//	FVector3 location = m_RelativeTransform.GetPosition();
	//	Rotator rotation = m_RelativeTransform.GetRotation();
	//	FVector3 scale = m_RelativeTransform.GetScale();
	//	FVector3 pScale = parent->GetTransform().GetScale();

	//	//Loop through hierarchy to get locations to add to get absolute location
	//	while (parent != nullptr)
	//	{
	//		location += parent->GetTransform().GetPosition();
	//		rotation += parent->GetTransform().GetRotation();
	//		scale.x *= pScale.x;
	//		scale.y *= pScale.y;
	//		scale.z *= pScale.z;

	//		parent = parent->GetParent(); //get the next parent
	//	}

	//	return Transform(location, rotation, scale);
	//}

	//void TransformComponent::SetRelativeTransform(const Transform& transform)
	//{
	//	m_RelativeTransform = transform;

	//	UpdateRelativeTransform();
	//}

	//Transform TransformComponent::GetRelativeTransform()
	//{
	//	return m_RelativeTransform;
	//}


	//void TransformComponent::UpdateRelativeTransform()
	//{
	//	FVector3 relLocation = m_RelativeTransform.GetPosition();
	//	Rotator relRotation = m_RelativeTransform.GetRotation();
	//	FVector3 relScale	= m_RelativeTransform.GetScale();
	//	FVector3 pScale		= m_Parent->m_Transform.GetScale();

 //		m_Transform.SetPosition(relLocation + m_Parent->m_Transform.GetPosition());
	//	m_Transform.SetRotation(relRotation + m_Parent->m_Transform.GetRotation());
	//	m_Transform.SetScale(relScale.x * pScale.x, relScale.y * pScale.y, relScale.z * pScale.z);
	//}

	void TransformComponent::OnImGuiRender(const std::string& ID)
	{
		ImGui::Separator();
		ImGui::Text("Transform");
		FVector3 Position = m_Transform.GetPosition();
		if (ImGui::InputFloat3(*("Position##" + ID), *Position))
		{
			m_Transform.SetPosition(Position);
		}

		Rotator Rotation = m_Transform.GetRotation();
		if (ImGui::InputFloat3(*("Rotation##" + ID), *Rotation))
		{
			m_Transform.SetRotation(Rotation);
		}

		FVector3 Scale = m_Transform.GetScale();
		if (ImGui::InputFloat3(*("Scale##" + ID), *Scale))
		{
			m_Transform.SetScale(Scale);
		}
	}

}