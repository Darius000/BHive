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

#ifdef BH_ENABLE_ASSERTS
	#define BH_ASSERT(x, ...) {if(!(x)){ BH_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); _debugbreak(); }}
	#define BH_ASSERT(x, ...) {if(!(x)){ BH_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); _debugbreak(); }}
#else
	#define BH_ASSERT(x, ...)
	#define BH_CORE_ASSERT(x, ...)
#endif

#define  BIT(x) (1 << x)

#define BH_BIND_EVENT_FN(x) std::bind(x, this, std::placeholders::_1)

#define BIND_EVENT_TWO_PARAM(x) std::bind(x, this, std::placeholders::_1, std::placeholders::_2)
#define BIND_EVENT_THREE_PARAM(x) std::bind(x, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)

#define DECLARE_TWO_PARAMETER_EVENT(EventName, type1, parameter1, type2, parameter2)\
	class BHive_API F##EventName##Event\
	{\
		public:\
			F##EventName##Event(){}\
			F##EventName##Event(type1 a, type2 b):m##parameter1(a), m##parameter2(b) {}\
			type1 Get##parameter1() const {return m##parameter1;}\
			type2 Get##parameter2() const {return m##parameter2;}\
		private:\
			type1 m##parameter1;\
			type2 m##parameter2;\
		public:\
			std::vector< std::function<void(type1, type2)>> bindedFunctions;\
			void AddBinding(const std::function<void(type1, type2)>& func)\
			{\
				bindedFunctions.emplace_back(func);\
			}\
			void Broadcast(type1 a, type2 b)\
			{\
				m##parameter1 = a;\
				m##parameter2 = b;\
				for(auto f : bindedFunctions)\
				{\
					f(a, b);\
				}\
			}\
			std::string ToString() const\
			{\
				std::stringstream ss;\
				ss << "F" << #EventName << "Event" << ": param1: " << m##parameter1 << "param2: " <<  m##parameter2;\
				return ss.str();\
			}\
	};

#define DECLARE_THREE_PARAMETER_EVENT(EventName, type1, parameter1, type2, parameter2, type3, parameter3)\
	class BHive_API F##EventName##Event\
	{\
		public:\
			F##EventName##Event(){}\
			type1 Get##parameter1() const {return m##parameter1;}\
			type2 Get##parameter2() const {return m##parameter2;}\
			type2 Get##parameter3() const {return m##parameter3;}\
		private:\
			type1 m##parameter1;\
			type2 m##parameter2;\
			type3 m##parameter3;\
		public:\
			std::vector< std::function<void(type1, type2, type3)>> bindedFunctions;\
			void AddBinding(const std::function<void(type1, type2, type3)>& func)\
			{\
				bindedFunctions.emplace_back(func);\
			}\
			void Broadcast(type1 a, type2 b, type3 c)\
			{\
				m##parameter1 = a;\
				m##parameter2 = b;\
				m##parameter3 = c;\
				for(auto f : bindedFunctions)\
				{\
					f(a, b, c);\
				}\
			}\
	};