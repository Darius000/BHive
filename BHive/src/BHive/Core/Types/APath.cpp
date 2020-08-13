#include "BHivePCH.h"
#include "APath.h"
#include <filesystem>

namespace BHive
{
	WinPath::WinPath()
	{

	}

	WinPath::WinPath(const ANSICHAR* path)
	{
		m_Length = StringLibrary::GetLength(path);

		if (m_Length == 0) return;

		m_Directory = std::filesystem::is_directory(path);

		StringLibrary::copy(m_FullPath, path);

		ConstructPath();
	}

	WinPath::WinPath(const WinPath& other)
	{
		m_Length = other.m_Length;

		if (m_Length == 0) return;

		m_Directory = other.m_Directory;

		StringLibrary::copy(m_FullPath, other.m_FullPath);

		ConstructPath();
	}


	WinPath::WinPath(WinPath&& other) noexcept
	{
		//BH_CORE_INFO("Moved!");
		m_Name = std::move(other.m_Name); 
		m_Ext = std::move(other.m_Ext);
		m_Directory = other.m_Directory;
		m_Path = std::move(other.m_Path);
		m_FullPath = std::move(other.m_FullPath);
		m_Length = other.m_Length;
		
		other.m_Length = 0;
		other.m_Directory = false;
	}

	WinPath::~WinPath()
	{
		::operator delete(m_Path, (StringLibrary::GetLength(m_Path) + 1) * sizeof(ANSICHAR));
		::operator delete(m_FullPath, (m_Length + 1) * sizeof(ANSICHAR));
		::operator delete(m_Name, (StringLibrary::GetLength(m_Name) + 1) * sizeof(ANSICHAR));
		::operator delete(m_Ext, (StringLibrary::GetLength(m_Ext)  + 1) * sizeof(ANSICHAR));
	}


	void WinPath::ConstructPath()
	{
		uint64 dotPos = StringLibrary::find_last_of(m_FullPath, { '.' });
		uint64 lastslashPos = StringLibrary::find_last_of(m_FullPath, { '/', '\\' });

		bool HasDot = dotPos != -1;
		bool HasSlash = lastslashPos != -1;

		uint64 start = 0; uint64 end = 0;

		start = HasDot ? dotPos + 1 : m_Length;
		end = m_Length;
		m_Ext = std::move(StringLibrary::substring(m_FullPath, start, end));

		start = HasSlash ? lastslashPos + 1 : 0;
		end = HasDot && !m_Directory ? dotPos - 1 : m_Length;
		m_Name = std::move(StringLibrary::substring(m_FullPath, start, end));

		start = 0;
		end = HasSlash ? lastslashPos : m_Length;
		m_Path = std::move(StringLibrary::substring(m_FullPath, start, end ));
	}

	WinPath& WinPath::operator=(const WinPath& Other)
	{
		//BH_CORE_INFO("Copied!");

		StringLibrary::copy(m_Name, Other.m_Name);
		StringLibrary::copy(m_Ext, Other.m_Ext);
		StringLibrary::copy(m_Path, Other.m_Path);
		StringLibrary::copy(m_FullPath, Other.m_FullPath);

		m_Directory = Other.m_Directory;
		m_Length = Other.m_Length;
		return *this;
	}

	namespace StringLibrary
	{
		void copy(ANSICHAR*& to, const ANSICHAR* from)
		{
			
			if (from == nullptr)
			{
				return;
			}

			uint64 length = GetLength(from);
			to = (ANSICHAR*)::operator new (length + 1);

			uint64 i = 0;
			while (i < length)
			{
				to[i] = from[i];
				++i;
			}

			to[length] = '\0';
		}

		ANSICHAR* substring(ANSICHAR* from, uint64 start, uint64 end)
		{
			if(end < start) return nullptr;

			const uint64 length = (end - start) + 1; //extra for null terminator
			auto str = (ANSICHAR*)::operator new (length + 1);

			uint64 i = 0;
			uint64 j = start;
			while (j <= end)
			{
				str[i] = from[j];
				++i;
				++j;
			}

			str[length] = '\0';

			return str;
		}

		int64 find_first_of(ANSICHAR* from, std::vector<ANSICHAR> x)
		{
			uint64 i = 0;
			uint64 pos = 0;
			uint64 length = GetLength(from);

			for (uint64 i = 0; i < length; i++)
			{
				auto& it = std::find(x.begin(), x.end(), from[i]);
				if (it != x.end())
				{
					pos = i;

					return (int64)pos;
				}
			}

			return -1;
		}

		int64 find_last_of(ANSICHAR* from, std::vector<ANSICHAR> x)
		{
			uint64 i = 0;
			uint64 pos = 0;
			bool found = false;
			uint64 length = GetLength(from);

			while (i < length)
			{
				auto& it = std::find(x.begin(), x.end(), from[i]);
				if (it != x.end())
				{
					pos = i;
					found = true;
				}

				++i;
			}

			return found ? (int64)pos : -1;
		}

		int64 GetLength(const ANSICHAR* from)
		{
			if (from == nullptr)
			{
				return 0;
			}

			uint64 i = 0;
			while (from[i] != '\0') ++i;
			return i;
		}
	}
}