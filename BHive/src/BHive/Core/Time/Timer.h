#pragma once

namespace BHive
{
	struct Timer
	{
		Timer(const ANSICHAR* name)
			:m_Name(name)
		{
			m_StartPoint = std::chrono::high_resolution_clock::now();
		}

		~Timer()
		{
			Stop();
		}

		void Stop()
		{
			auto endTimePoint = std::chrono::high_resolution_clock::now();

			auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartPoint).time_since_epoch().count();
			auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
			auto duration = end - start;
			double ms = duration * 0.001;
			BH_CORE_WARN("Timer: {0} took {1} milliseconds, {2} microseconds to complete!", m_Name, ms, duration);
		}

	private:
		std::chrono::time_point<std::chrono::steady_clock> m_StartPoint;
		const ANSICHAR* m_Name;
	};
}