#include "BHivePCH.h"
#include "FName.h"

namespace BHive
{
	FName::FName(uint32 len, const ANSICHAR* c)
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

	FName::FName(uint32 len, const WIDECHAR* wc)
	{
		uint32 i = 0;
		while (i != len)
		{
			m_WChars[i] = wc[i];
			i++;
		}
	}

	FName::FName(const ANSICHAR* c)
	{
		uint32 i = 0;
		while (c[i] != NULL_TERMINATOR)
		{
			m_Chars[i] = c[i];
			i++;
		}
	}

	FName::FName(const WIDECHAR* wc)
	{
		uint32 i = 0;
		while (wc[i] != NULL_TERMINATOR)
		{
			m_WChars[i] = wc[i];
			i++;
		}
	}

	FName::FName()
	{
		m_Chars[0] = 'N';
		m_Chars[1] = 'O';
		m_Chars[2] = 'N';
		m_Chars[3] = 'E';
		m_Chars[4] = '\0';
	}

	int32 FName::Compare(const FName& other) const
	{
		return INDEX_NONE;
	}

	bool FName::IsEqual(const FName& other, ENameCase nameCase)
	{
		return false;
	}

	bool FName::IsNone()
	{
		return false;
	}

	void FName::SetNumber(int32 newNumber)
	{

	}

	FString FName::ToString() const
	{
		return FString(m_Chars);
	}

	void FName::ToString(const FString& out)
	{

	}

	bool FName::operator!=(const FName& name) const
	{
		return false;
	}

	bool FName::operator==(const WIDECHAR* name)
	{
		return false;
	}

	bool FName::operator==(const ANSICHAR* name)
	{
		return false;
	}

	bool FName::operator==(const FName& name)
	{
		return false;
	}

	uint64 FName::operator()(const FName& n) const
	{
		return 0;
	}
}

