#pragma once

#define BIND_EVENT_ONE_PARAM(x) std::bind(x, this, std::placeholders::_1)
#define BIND_EVENT_TWO_PARAMS(x) std::bind(x, this, std::placeholders::_1, std::placeholders::_2)
#define BIND_EVENT_THREE_PARAMS(x) std::bind(x, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
#define BIND_EVENT_FOUR_PARAMS(x) std::bind(x, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)
#define BIND_EVENT_FIVE_PARAMS(x) std::bind(x, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5)
#define CLASSNAME(x) x

#define DECLARE_ONE_PARAMETER_EVENT(EventName, type1, parameter1)\
	class BHive_API F##EventName##Event\
	{\
		public:\
			F##EventName##Event(){}\
		public:\
			std::vector< std::function<void(type1)>> bindedFunctions;\
			void AddBinding(const std::function<void(type1)>& func)\
			{\
				bindedFunctions.emplace_back(func);\
			}\
			void Broadcast(type1 parameter1)\
			{\
				for(auto f : bindedFunctions)\
				{\
					f(parameter1);\
				}\
			}\
	};

#define DECLARE_TWO_PARAMETER_EVENT(EventName, type1, parameter1, type2, parameter2)\
	class BHive_API F##EventName##Event\
	{\
		public:\
			F##EventName##Event(){}\
			std::vector< std::function<void(type1, type2)>> bindedFunctions;\
			void AddBinding(const std::function<void(type1, type2)>& func)\
			{\
				bindedFunctions.emplace_back(func);\
			}\
			void Broadcast(type1 parameter1, type2 parameter2)\
			{\
				for(auto f : bindedFunctions)\
				{\
					f(parameter1, parameter2);\
				}\
			}\
	};

#define DECLARE_THREE_PARAMETER_EVENT(EventName, type1, parameter1, type2, parameter2, type3, parameter3)\
	class BHive_API F##EventName##Event\
	{\
		public:\
			F##EventName##Event(){}\
			std::vector< std::function<void(type1, type2, type3)>> bindedFunctions;\
			void AddBinding(const std::function<void(type1, type2, type3)>& func)\
			{\
				bindedFunctions.emplace_back(func);\
			}\
			void Broadcast(type1 parameter1, type2 parameter2, type3 parameter3)\
			{\
				for(auto f : bindedFunctions)\
				{\
					f(parameter1, parameter2, parameter3);\
				}\
			}\
	};

#define DECLARE_FOUR_PARAMETER_EVENT(EventName, type1, parameter1, type2, parameter2, type3, parameter3, type4, paramater4)\
	class BHive_API F##EventName##Event\
	{\
		public:\
			F##EventName##Event(){}\
			std::vector< std::function<void(type1, type2, type3, type4)>> bindedFunctions;\
			void AddBinding(const std::function<void(type1, type2, type3, type4)>& func)\
			{\
				bindedFunctions.emplace_back(func);\
			}\
			void Broadcast(type1 parameter1, type2 parameter2, type3 parameter3, type4 parameter4)\
			{\
				for(auto f : bindedFunctions)\
				{\
					f(parameter1, parameter2, parameter3, parameter4);\
				}\
			}\
	};


#define DECLARE_FIVE_PARAMETER_EVENT(EventName, type1, parameter1, type2, parameter2, type3, parameter3, type4, paramater4, type5, parameter5)\
	class BHive_API F##EventName##Event\
	{\
		public:\
			F##EventName##Event(){}\
			std::vector< std::function<void(type1, type2, type3, type4, type5)>> bindedFunctions;\
			void AddBinding(const std::function<void(type1, type2, type3, type4, type5)>& func)\
			{\
				bindedFunctions.emplace_back(func);\
			}\
			void Broadcast(type1 parameter1, type2 parameter2, type3 parameter3, type4 parameter4, type5 parameter5)\
			{\
				for(auto f : bindedFunctions)\
				{\
					f(parameter1, parameter2, parameter3, parameter4, parameter5);\
				}\
			}\
	};