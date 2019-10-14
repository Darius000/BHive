#ifndef PROFILER_H
#define PROFILER_H

#include "Core.h"

namespace BHive
{
	struct FPRofilerStats;
	struct FProfiler;

	typedef std::unordered_map<const char*, FPRofilerStats> ProfileManager;
	typedef std::vector<FProfiler*> ProfileChildren;

	struct FPRofilerStats
	{
		FPRofilerStats()
			:Calls(0), ElapsedTime(0)
		{

		}

		int64 Calls;
		int64 ElapsedTime;
	};

	typedef uint32 numCalls;

	struct FProfiler
	{
		FProfiler(const char* name, numCalls calls)
		{
			m_name = name;
			QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);
			stats.Calls = calls;
		}

		~FProfiler()
		{
			int64 endtime = 0;
			QueryPerformanceCounter((LARGE_INTEGER*)&endtime);
			int64 elapsedTime = endtime - m_startTime;

			ProfileManager::iterator it = profileManager.find(m_name);

			if (it == profileManager.end())
			{
				it = profileManager.insert(std::make_pair(m_name, stats)).first;
			}

			it->second.ElapsedTime = elapsedTime;
			it->second.Calls = stats.Calls;
		}

		FPRofilerStats GetStats()
		{
			return stats;
		}


		static void ShowStats();

		static  ProfileManager profileManager;
		static FProfiler* currentProfiler;

	private:
		const char* m_name = "";
		int64 m_startTime;
		FPRofilerStats stats;
	};


#define PROFILE(FUNCTION) static numCalls nC = 0;\
	nC ++;\
	FProfiler p(#FUNCTION, nC);
}

#endif