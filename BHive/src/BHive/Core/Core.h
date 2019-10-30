#pragma once

#include <memory>

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

#define  BIT(x) (1 << x)
#define INDEX_NONE -1

#define BH_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace BHive
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref= std::shared_ptr<T>;	

	template<typename T>
	using WRef = std::weak_ptr<T>;

}