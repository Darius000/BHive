#pragma once
#include <memory>

namespace BHive
{
	struct CoreLibrary
	{
		template<typename T>
		static const char* GetVariableType(T t)
		{
			return typeid(t).name();
		}
	};

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using Weak = std::weak_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> Make_Scope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename ... Args>
	constexpr Ref<T> Make_Ref(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
