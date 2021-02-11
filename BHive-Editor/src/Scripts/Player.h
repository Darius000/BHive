#pragma once


namespace BHive
{
	class Player : public CPPScript
	{
	public:
		Player() = default;

		void OnCreate();

		void OnUpdate(const Time& time);
	};
}