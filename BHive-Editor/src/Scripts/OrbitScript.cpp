#include "BHivePCH.h"
#include "OrbitScript.h"

namespace BHive
{

	void OrbitScript::OnCreate()
	{
		auto& transform = GetComponent<TransformComponent>().m_Transform;
		Distance = transform.GetPosition().GetMagnitude();
	}

	void OrbitScript::OnUpdate(const Time& time)
	{
		auto& transform = GetComponent<TransformComponent>().m_Transform;
		
#if YAW
		Yaw += time.GetDeltaTime() * Speed;
#endif
#if PITCH

		Pitch += time.GetDeltaTime();
#endif

#if DEGREE_ANGLES
		x = MathLibrary::CosD(Yaw) * MathLibrary::CosD(Pitch) * Distance;
		y = MathLibrary::SinD(Pitch) * Distance;
		z = (MathLibrary::SinD(Yaw) * MathLibrary::CosD(Pitch)) * Distance;
#else
		x = MathLibrary::Cos(Yaw) * MathLibrary::Cos(Pitch) * Distance;
		y = MathLibrary::Sin(Pitch) * Distance;
		z = (MathLibrary::Sin(Yaw) * MathLibrary::Cos(Pitch)) * Distance;
#endif

		auto newPos = FVector3(x, y, z);

		transform.SetPosition(newPos);
		
		transform.LookAt({ 0,0,0 });
	}
}