#pragma once

#ifdef BH_PLATFORM_WINDOWS
#if BH+DYNAMIC_DLL
	#ifdef BH_BUILD_DLL
		#define BHive_API _declspec(dllexport)
	#else
		#define BHive_API _declspec(dllimport)
	#endif
#else
	#define BHive_API
#endif
#else
	#error BHive only supports Windows!
#endif

#ifdef BH_DEBUG
	#define BH_ENABLE_ASSERTS
#endif

#ifdef BH_ENABLE_ASSERTS
	#define BH_ASSERT(x, ...) {if(!(x)){ BH_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define BH_CORE_ASSERT(x, ...) {if(!(x)){ BH_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define BH_ASSERT(x, ...)
	#define BH_CORE_ASSERT(x, ...)
#endif

#include "CoreLibrary.h"
#include "EventMacros.h"

