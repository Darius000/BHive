#pragma once

#include "Core.h"

namespace BHive
{
	class BHive_API Time
	{
	public:

		Time();
		virtual ~Time();

		static float GetTime();
		static float GetDeltaTime();
		static void Update();

	private:
		static float m_Time;
		static float m_LastTime;
		static float m_DeltaTime;
	};
}