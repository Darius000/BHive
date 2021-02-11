#pragma once

namespace BHive
{
	#define YAW 1
	#define PITCH 0

	class OrbitScript : public CPPScript
	{
	public:
		void OnCreate();
		void OnUpdate(const Time& time);

		float Yaw = 0.0f;
		float Pitch = 0.0f;
		float Speed = 20.0f;
		float Distance = 0.0f;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	};
}