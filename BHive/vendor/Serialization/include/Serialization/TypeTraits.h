#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <array>
#include <type_traits>

namespace Serialization
{
	template<typename ...Ts>
	struct voider
	{
		using type = void;
	};

	template<typename T, typename = void>
	struct  Does_Container_Have_Size
	{
		static constexpr bool value = false;
	};

	template<typename T>
	struct  Does_Container_Have_Size<T, 
	typename voider<decltype(std::declval<T>().size())>::type>
	{
		static constexpr bool value = true;
	};

	template<typename T, bool = Does_Container_Have_Size<T>::value>
	struct TypeSize;

	template<typename T>
	struct TypeSize<T, false>
	{
		static size_t Value(const T& t)
		{
			return sizeof(t);
		};
	};

	template<typename T>
	struct TypeSize<T, true>
	{
		static size_t Value(const T& t)
		{
			return t.size();
		};
	};

	template<typename T>
	inline size_t GetSize(const T& t)
	{
		return TypeSize<T>::Value(t);
	};
}