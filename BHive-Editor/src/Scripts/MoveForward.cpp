#include "BHivePCH.h"
#include "MoveForward.h"

namespace BHive
{
	void MoveForward::OnCreate()
	{
		GetComponent<TransformComponent>().m_Transform.SetRotation(0.0f, 0.0f, 0.0f);
	}

	void MoveForward::OnUpdate(const Time& time)
	{
		auto& transform = GetComponent<TransformComponent>().m_Transform;
		auto pos = transform.GetPosition();
		auto forw = transform.GetForward();
		pos += forw * 1.0f * time.GetDeltaTime();
		transform.SetPosition(pos);
	}

}