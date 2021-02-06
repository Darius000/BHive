#pragma once

#include <string>
#include "IRegisterable.h"

namespace Reflection
{ 
	template<typename T>
	class Type 
	{
	public:
		Type() = default;
		virtual ~Type() = default;
		virtual std::string GetName() = 0;
		virtual size_t GetSize() = 0;
	};

	#define DEFINE_TYPE(type)\
		class type##Type : public Type<type>\
		{\
		public:\
			std::string GetName() override { return #type; }\
			size_t GetSize() override { return sizeof(type); }\
		};\

	DEFINE_TYPE(char)
	DEFINE_TYPE(int)
	DEFINE_TYPE(float)
	using namespace std;
	DEFINE_TYPE(string)
}