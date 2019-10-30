#pragma once

namespace BHive
{
	typedef std::string BString;
	typedef BString Path;
	typedef BString BName;		
}

inline const BHive::ANSICHAR* Format(const BHive::ANSICHAR* format, ...)
{
	BHive::ANSICHAR* buffer = new BHive::ANSICHAR[256];
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, 255, format, args);
	va_end(args);

	return buffer;
}

inline const BHive::ANSICHAR* operator*(const BHive::BString& s)
{
	return s.c_str();
}

