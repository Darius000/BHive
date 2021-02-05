#pragma once

#include <string>

namespace BHive
{
	class FileDialog
	{
	public:
		//if canceled return empty strings
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};
}