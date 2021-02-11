#include "BHivePCH.h"
#include "LookAt.h"

namespace BHive
{

	void LookAt::OnCreate()
	{
	
	}

	void LookAt::OnUpdate(const Time& time)
	{
		auto& transform = GetComponent<TransformComponent>();

		transform.m_Transform.LookAt({0.0f});
	}
}