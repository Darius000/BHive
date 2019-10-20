#include "BHivePCH.h"
#include "Name.h"

namespace BHive
{
	Name::Name(uint32 len, const ANSICHAR* c)
		:Name()
	{
		uint32 i = 0;
		while (i < len)
		{
			m_Chars[i] = c[i];
			i++;
		} 

		m_Chars[i + 1] = NULL_TERMINATOR;
		m_Size = i;
	}

	Name::Name(uint32 len, const WIDECHAR* wc)
		:Name()
	{
		uint32 i = 0;
		while (i != len)
		{
			m_WChars[i] = wc[i];
			i++;
		}
	}

	Name::Name(const ANSICHAR* c)
		:Name()
	{
		uint32 i = 0;
		while (c[i] != NULL_TERMINATOR)
		{
			m_Chars[i] = c[i];
			i++;
		}
	}

	Name::Name(const WIDECHAR* wc)
		:Name()
	{
		uint32 i = 0;
		while (wc[i] != NULL_TERMINATOR)
		{
			m_WChars[i] = wc[i];
			i++;
		}
	}

	Name::Name()
		:m_Size(0)
	{
		m_Chars[0] = 'N';
		m_Chars[1] = 'O';
		m_Chars[2] = 'N';
		m_Chars[3] = 'E';
		m_Chars[4] = '\0';
	}

	int32 Name::Compare(const Name& other) const
	{
		return INDEX_NONE;
	}

	bool Name::IsEqual(const Name& other, ENameCase nameCase)
	{
		return false;
	}

	bool Name::IsNone()
	{
		return false;
	}

	void Name::SetNumber(const int32 newNumber)
	{
		m_Number = newNumber;
	}

	FString Name::ToString() const
	{
		return FString(m_Chars, m_Size);
	}

	void Name::ToString(FString& out)
	{
		out.Reset(m_Chars, m_Size);
	}

	bool Name::operator==(const Name& name)
	{
		return (m_ComparsionID == m_ComparsionID) & (GetNumber() == name.GetNumber());
	}

	using FName = Name;
	//using WName = Name<WIDECHAR>;
}

