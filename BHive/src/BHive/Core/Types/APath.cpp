#include "BHivePCH.h"
#include "APath.h"

namespace BHive
{
	WinPath::WinPath()
		:m_Name(nullptr), m_Ext(nullptr)
	{
		m_Path = std::make_unique<ANSICHAR[]>(0);
		m_Length = 0;
	}

	WinPath::WinPath(const ANSICHAR* path)
	{
		index i = 0;
		while (path[i] != '\0') ++i;
		m_Length = i;

		m_Path = std::make_unique<ANSICHAR[]>(m_Length + (index)1);

		i = 0;
		while (i < m_Length)
		{
			m_Path[i] = path[i];
			++i;
		}

		m_Path[m_Length] = '\0';

		index dotPos = find_last_of('.');
		m_Ext = std::move(substring(dotPos + 1, m_Length));

		m_Directory = dotPos == -1 ? true : false;

		index lastslashPos = find_last_of('/');

		if (!m_Directory)
		{
			m_Name = lastslashPos != -1 ? std::move(substring(lastslashPos + 1, dotPos - 1)) :
				std::move(substring(0, dotPos - 1));
		}
		else
		{
			m_Name = lastslashPos != -1 ? std::move(substring(lastslashPos + 1, m_Length)) :
				std::move(substring(0, m_Length));
		}
	}

	WinPath::WinPath(const WinPath& other)
	{
		m_Path = std::make_unique<ANSICHAR[]>(other.m_Length);
		copy(m_Path.get(), other.m_Path.get());
		
		index dotPos = find_last_of('.');
		m_Ext = std::move(substring(dotPos + 1, m_Length));

		m_Directory = other.m_Directory;

		index lastslashPos = find_last_of('/');
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

	index WinPath::find_first_of(ANSICHAR x)
	{
		index i = 0;
		index pos = 0;

		for (index i = 0; i < m_Length; i++)
		{
			if (m_Path[i] == x)
			{
				pos = i;

				return pos;
			}
		}

		return -1;
	}

	index WinPath::find_last_of(ANSICHAR x)
	{
		BHive::index i = 0;
		BHive::index pos = 0;
		bool found = false;

		while (i < m_Length)
		{
			if (m_Path[i] == x)
			{
				pos = i;
				found = true;
			}

			++i;
		}

		return found ? pos : -1;
	}

}