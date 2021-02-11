#pragma once

/* Macros to create enum class with strings and operators*/

namespace BHive
{
#define CREATE_ENUM(name) \
  name

#define CREATE_STRINGS(name) \
  #name

#define ENUM(name, types)\
	enum class name : int\
	{\
		types(CREATE_ENUM)\
	};

#define CREATE_ENUM_STRINGS(name, types) \
	static const char* name##Strings[] = { types(CREATE_STRINGS) };\
	//inline const char* name##ToString(name value) { return name##Strings[value]; }

#define ENUM_OPERATORS(EnumClass, T)\
	inline EnumClass operator |(EnumClass a, EnumClass b){return static_cast<EnumClass>(static_cast<T>(a) | static_cast<T>(b));};\
	inline EnumClass operator &(const EnumClass &a, const EnumClass &b){return static_cast<EnumClass>(static_cast<T>(a) & static_cast<T>(b));};\
	inline EnumClass& operator |=(EnumClass &a, EnumClass b){return a = a | b;};\
	inline bool HasFlag(const EnumClass& a, const EnumClass& b) { return (a & b) == b; }\
	inline bool operator && (const EnumClass& a, const EnumClass b) { return (a & b) == b; }; 

#define CREATE_ENUM_CLASS(name, types)\
	ENUM(name, types)\
	CREATE_ENUM_STRINGS(name, types)\
	ENUM_OPERATORS(name, int)
}