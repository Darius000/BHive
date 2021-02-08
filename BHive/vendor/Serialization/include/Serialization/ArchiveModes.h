#pragma once

#include <fstream>
#include "EnumOperators.h"

namespace Serialization
{
	enum class EArchiveModes : int
	{
		None = 0,
		In = std::fstream::in,
		Out = std::fstream::out,
		Binary = std::fstream::binary,
		Ate = std::fstream::ate,
		App = std::fstream::app,
		Trunc = std::fstream::trunc
	};

	DEFENUMOPERATORS(EArchiveModes, int)

	/*template<typename T, typename U>
	class IEnumerable
	{
	public:
		template<typename EnumClass, typename T>
		friend EnumClass operator |(EnumClass a, EnumClass b);

		template<typename EnumClass, typename T>
		friend EnumClass operator &(const EnumClass& a, const EnumClass& b);

		template<typename EnumClass, typename T>
		friend EnumClass& operator |=(EnumClass& a, EnumClass b);
	};

	template<typename EnumClass, typename T>
	inline EnumClass operator |(EnumClass a, EnumClass b) { return static_cast<EnumClass>(static_cast<T>(a) | static_cast<T>(b)); }

	template<typename EnumClass, typename T>
	inline EnumClass operator &(const EnumClass& a, const EnumClass& b) { return static_cast<EnumClass>(static_cast<T>(a) & static_cast<T>(b)); }

	template<typename EnumClass, typename T>
	inline EnumClass& operator |=(EnumClass& a, EnumClass b) { return a = a | b; }*/

	

	//IEnumerable<EArchiveModes, int>;	
}