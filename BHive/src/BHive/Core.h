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

#ifdef BH_ENABLE_ASSERTS
	#define BH_ASSERT(x, ...) {if(!(x)){ BH_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); _debugbreak(); }}
	#define BH_ASSERT(x, ...) {if(!(x)){ BH_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); _debugbreak(); }}
#else
	#define BH_ASSERT(x, ...)
	#define BH_CORE_ASSERT(x, ...)
#endif

#define  BIT(x) (1 << x)