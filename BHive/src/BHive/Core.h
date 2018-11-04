#pragma once

#ifdef BH_PLATFORM_WINDOWS
	#ifdef BH_BUILD_DLL
		#define BHive_API _declspec(dllexport)
	#else
		#define BHive_API _declspec(dllimport)
	#endif
#else
	#error BHive only supports Windows!
#endif