#include "BHivePCH.h"
#include "APath.h"
#include <filesystem>

namespace BHive
{
	WinPath::WinPath()
		:m_Name(nullptr), m_Ext(nullptr)
	{
		m_Path = Make_Scope<ANSICHAR[]>(0);
		m_Length = 0;
	}

	WinPath::WinPath(const ANSICHAR* path)
	{
		m_Directory = std::filesystem::is_directory(path);

		index i = 0;
		while (path[i] != '\0') ++i;
		m_Length = i;

		m_Path = Make_Scope<ANSICHAR[]>(m_Length + (index)1);

		i = 0;
		while (i < m_Length)
		{
			m_Path[i] = path[i];
			++i;
		}

		m_Path[m_Length] = '\0';

		index dotPos = find_last_of({'.'});
		m_Ext = m_Directory ? Make_Scope<ANSICHAR[]>(0) : std::move(substring(dotPos + 1, m_Length));

		index lastslashPos = find_last_of({ '/', '\\' });

		m_Name = lastslashPos != -1 ? std::move(substring(lastslashPos + 1, m_Directory ? m_Length : dotPos - 1)) :
			std::move(substring(0, m_Directory ? m_Length : dotPos - 1));
	
	}

	WinPath::WinPath(const WinPath& other)
	{
		m_Length = other.m_Length;
		m_Path = Make_Scope<ANSICHAR[]>(m_Length + (index)1);
		copy(m_Path.get(), other.m_Path.get());
		
		index dotPos = find_last_of({ '.' });
		m_Ext = std::move(substring(dotPos + 1, m_Length));

		m_Directory = other.m_Directory;

		index lastslashPos = find_last_of({ '/', '\\' });
		m_Name = lastslashPos != -1 ? std::move(substring(lastslashPos + 1, dotPos - 1)) : 
			std::move(substring(0, dotPos - 1));
	}

	WinPath::~WinPath()
	{
		
	}

	void WinPath::copy(ANSICHAR* to, const ANSICHAR* from)
	{
		index i = 0;
		while (i < m_Length)
		{
			to[i] = from[i];
			++i;
		}
	}

	Scope<ANSICHAR[]> WinPath::substring(index start, index end)
	{
		index length = (end - start) + 1; //extra for null terminator
		auto str = std::make_unique<ANSICHAR[]>(length + (index)1);

		index i = 0;
		index j = start;
		while (j <= end)
		{
			str[i] = m_Path[j];
			++i;
			++j;
		}

		str[length] = '\0';

		return str;
	}

	index WinPath::find_first_of(std::vector<ANSICHAR> x)
	{
		index i = 0;
		index pos = 0;

		for (index i = 0; i < m_Length; i++)
		{
			auto& it = std::find(x.begin(), x.end(), m_Path[i]);
			if (it != x.end())
			{
				pos = i;

				return pos;
			}
		}

		return -1;
	}

	index WinPath::find_last_of(std::vector<ANSICHAR> x)
	{
		index i = 0;
		index pos = 0;
		bool found = false;

		while (i < m_Length)
		{
			auto& it = std::find(x.begin(), x.end(), m_Path[i]);
			if (it != x.end())
			{
				pos = i;
				found = true;
			}

			++i;
		}

		return found ? pos : -1;
	}

}