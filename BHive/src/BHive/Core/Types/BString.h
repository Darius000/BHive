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

	inline const char* operator+(const std::string& String, const uint32& Integer)
	{
		return *(String + std::to_string(Integer));
	}

	inline BString operator+(const BString& a, const ANSICHAR* b) 
	{
		return (a + BString(b));
	}

	inline const char* operator+(const uint32& Integer, const std::string& String)
	{
		return *(std::to_string(Integer) + String);
	}

	inline uint64 find_last_of(const BString& str, std::vector<ANSICHAR> x)
	{
		uint64 i = 0;
		uint64 pos = 0;
		bool found = false;

		while (str[i] != '\0')
		{
			auto& it = std::find(x.begin(), x.end(), str[i]);
			if (it != x.end())
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

	inline std::istream& GetLine(std::istream& is, std::string& result, char delim = '\n')
	{
		char ch;
		result.clear();
		while (is.get(ch))
		{
			if (ch == delim)
			{
				break;
			}
			else
			{
				result += ch;
			}
		}

		return is;
	}

	inline std::string CheckNextLine(std::istream& is, char delim = '\n')
	{
		char ch;
		std::string result;

		//Get current position
		std::streampos len = is.tellg();

		while (is.get(ch))
		{
			if (ch == delim)
			{
				break;
			}
			else
			{
				result += ch;
			}
		}

		//return to position
		is.seekg(len, std::ios_base::beg);

		return result;
	}
}