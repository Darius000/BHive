#pragma once

namespace BHive
{
	class MoveForward : public CPPScript
	{
	public:
		MoveForward() = default;

		void OnCreate();

		void OnUpdate(const Time& time);
	};
}