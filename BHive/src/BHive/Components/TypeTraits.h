#pragma once

namespace BHive
{
	namespace TypeTraits
	{

#define TypeHasFunction(FunctionName)\
		template<typename, typename T>\
		struct Has##FunctionName##Function {\
			static_assert(\
				std::integral_constant<T, false>::value,\
				"Second template parameter needs to be of function type.");\
		};\
\
		template<typename C, typename Ret, typename... Args>\
		struct  Has##FunctionName##Function<C, Ret(Args...)> {\
		private:\
			template<typename T>\
			static constexpr auto check(T*)\
				-> typename\
				std::is_same<\
				decltype(std::declval<T>().FunctionName(std::declval<Args>()...)),\
				Ret \
				>::type; \
\
			template<typename>\
			static constexpr std::false_type check(...);\
			typedef decltype(check<C>(0)) type;\
		public:\
			static constexpr bool value = type::value;\
		};\

		namespace detail
		{
			TypeHasFunction(OnCreate);
			TypeHasFunction(OnDestroy);
			TypeHasFunction(OnUpdate);
		}
		
		template<typename T>
		constexpr bool HasOnCreateFunction()
		{
			return detail::HasOnCreateFunction<T, void()>::value;
		}

		template<typename T>
		constexpr bool HasOnDestroyFunction()
		{
			return detail::HasOnDestroyFunction<T, void()>::value;
		}

		template<typename T>
		constexpr bool HasOnUpdateFunction()
		{
			return detail::HasOnUpdateFunction<T, void(const Time&)>::value;
		}
	}
}