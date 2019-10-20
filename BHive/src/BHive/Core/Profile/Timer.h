#pragma once


struct Timer
{	
	Timer()
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
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartPoint).time_since_epoch().count();
		auto duration = end - start;
		double ms = duration * 0.001;
		BH_CORE_TRACE("Timer clock: {0} milliseconds, {0} microseconds", ms, duration);
	}

private:
	std::chrono::time_point<std::chrono::steady_clock> m_StartPoint;
};