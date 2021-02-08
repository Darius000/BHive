#pragma once


#define DEFENUMOPERATORS(EnumClass, T)\
	inline EnumClass operator |(EnumClass a, EnumClass b){return static_cast<EnumClass>(static_cast<T>(a) | static_cast<T>(b));};\
	inline EnumClass operator &(const EnumClass &a, const EnumClass &b){return static_cast<EnumClass>(static_cast<T>(a) & static_cast<T>(b));};\
	inline EnumClass& operator |=(EnumClass &a, EnumClass b){return a = a | b;};\
	inline bool HasFlag(const EnumClass& a, const EnumClass& b) { return (a & b) == b; }

