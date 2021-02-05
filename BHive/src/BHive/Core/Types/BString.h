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

	template<typename T>
	inline std::string ToString(T num)
	{
		return std::to_string(num);
	}

	inline const ANSICHAR* operator*(const BString& s)
	{
		return s.c_str();
	}

	inline const char* operator+(const std::string& String, const uint32& Integer)
	{
		return *(String + std::to_string(Integer));
	}

	inline const char* operator+(const std::string& String, const uint64& Integer)
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

	inline std::string GetLineFromString(const std::string& source, size_t pos, size_t& eol, const std::string& delim = "\n")
	{
		std::string result;
		eol = source.find_first_of(delim.c_str(), pos);
		result = source.substr(pos, eol - pos);

		return result;
	}

	inline std::vector<std::string> GetLinesFromString(const std::string& source, const std::string& delim = "\n")
	{
		std::vector<std::string> str;
		size_t pos = 0;
		size_t eol = 0;
		size_t size = source.size();
		//npos = 18446744073709551615
		while (eol != std::string::npos)
		{
			std::string line = GetLineFromString(source, pos, eol, delim);
			str.push_back(line);
			pos = eol + delim.size();
		}
		return str;
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

	template<typename T>
	inline void RemoveFromVector(const T& val, std::vector<T>& v)
	{
		if(FindInVector(val, v) != -1)
			v.erase(std::find(v.begin(), v.end(), val));
	}

	template<typename T>
	inline int64 FindInVector(const T& val, std::vector<T>& v)
	{
		auto it = std::find(v.begin(), v.end(), val);
		if (it != v.end()) return it - v.begin();
		return -1;
	}
}