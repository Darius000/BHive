#include "BHivePCH.h"
#include "Profiler.h"

namespace BHive
{
	void FProfiler::ShowStats()
	{
		LARGE_INTEGER f;
		QueryPerformanceFrequency(&f);

		printf("%20s Calls \tTime(secs)\n", "Scope");

		for (ProfileManager::iterator it = profileManager.begin();
			it != profileManager.end(); it++)
		{
			double freq = double(f.QuadPart) / 1000.0;
			double eTime = (double)it->second.ElapsedTime / freq;
			printf("%20s %5d  \t%5f \n", it->first, (int32)it->second.Calls, eTime);
		}
	}

	ProfileManager FProfiler::profileManager;
}