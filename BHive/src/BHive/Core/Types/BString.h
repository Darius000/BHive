#pragma once

namespace BHive
{
	using BString = std::string;
	using BName = BString;

	inline const ANSICHAR* Format(const ANSICHAR* format, ...)
	{
		auto* buffer = new ANSICHAR[256];
		va_list args;
		va_start(args, format);
		vsnprintf(buffer, 255, format, args);
		va_end(args);

		return buffer;
	}

	inline const ANSICHAR* operator*(const BString& s)
	{
		return s.c_str();
	}

	inline uint64 find_last_of(const BString& str, ANSICHAR x)
	{
		uint64 i = 0;
		uint64 pos = 0;
		bool found = false;

		while (str[i] != '\0')
		{
			if (str[i] == x)
			{
				pos = i;
				found = true;
			}

			++i;
		}

		return found ? pos : -1;
	}

	template<class ForwardIterator, typename T>
	inline void Replace(ForwardIterator start, ForwardIterator end, const T& oldVal, const T& newVal)
	{
		ForwardIterator i = start;

		BString::iterator j;

		while (i < end)
		{
			if (*i == oldVal)
				*i = newVal;

			i++;
		}

		return;
	}
}