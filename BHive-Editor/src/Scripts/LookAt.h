#pragma once

namespace BHive
{
	class LookAt : public CPPScript
	{
	public:
		void OnCreate();
		void OnUpdate(const Time& time);
	};
}