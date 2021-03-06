#pragma once

#define DEFINE_ENUM_OPERATORS(EnumClass, T)\
	inline EnumClass operator |(EnumClass a, EnumClass b){return static_cast<EnumClass>(static_cast<T>(a) | static_cast<T>(b));};\
	inline EnumClass operator &(const EnumClass &a, const EnumClass &b){return static_cast<EnumClass>(static_cast<T>(a) & static_cast<T>(b));};\
	inline EnumClass& operator |=(EnumClass &a, EnumClass b){return a = a | b;};\
	inline bool HasFlag(const EnumClass& a, const EnumClass& b) { return (a & b) == b; }\
	inline bool operator && (const EnumClass& a, const EnumClass b) { return (a & b) == b; }; 