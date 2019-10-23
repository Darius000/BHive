#include "BHivePCH.h"
#include "String.h"

namespace BHive
{
	template<typename charType>
	String<charType>::String()
		:String(" ", STRING_SIZE)
	{

	}

	template<typename charType> 
	String<charType>::String(const charType* c)
		:String(c, STRING_SIZE)
	{
	
	}

	template<typename charType> 
	String<charType>::String(const charType* c, uint32 len)
		:m_Characters(nullptr), m_Capacity(len), m_Size(CharacterArrayHelper::GetCharArraySize(c)), m_IsNumeric(false)
	{
		Reset(len);
		CharacterArrayHelper::CopyCharacters(m_Characters, c, m_IsNumeric);
	}

	template<typename charType> 
	String<charType>::String(uint32 len)
		:String(" ", len)
	{
	
	}

	template<typename charType> 
	String<charType>::String(const String& other)
	{
		m_Capacity = other.m_Capacity;
		Reset(m_Capacity);
		
		m_Size = other.m_Size;
		m_IsNumeric = other.m_IsNumeric;
		CharacterArrayHelper::CopyCharacters(m_Characters, other.m_Characters);
	}

	template<typename charType>
	String<charType>::~String()
	{
		delete[] m_Characters;
	}

	template<typename charType> 
	void String<charType>::Resize(uint32 len)
	{
		
	}

	template<typename charType>
	void String<charType>::Shrink()
	{

	}

	template<typename charType>
	bool String<charType>::IsValidIndex(uint32 index) const
	{ 
		return index > -1 && index < m_Size; 
	}

	template<typename charType>
	bool String<charType>::Equals(const String& other, ESearchCase searchCase) const
	{
		if (m_Size != other.m_Size)
			return false;

		switch (searchCase)
		{
		case ESearchCase::CaseSensitive:

			for (uint32 i = 0; i < m_Size; i++)
			{
				if (m_Characters[i] != other[i])
				{
					return false;
				}
			}

			break;

		case ESearchCase::CaseInSensitive:

			for (uint32 i = 0; i < m_Size; i++)
			{
				if (tolower(m_Characters[i]) != tolower(other[i]))
				{
					return false;
				}
			}

			break;
		}

		return true;
	}

	template<typename charType>
	void String<charType>::SetCharacter(uint32 index, const char& character)
	{
		m_Characters[index] = character;
	}

	template<typename charType>
	void String<charType>::Reset(uint32 size)
	{
		if (m_Size > 0) delete[] m_Characters;
		m_Characters = new char[STRING_SIZE];
	}

	template<typename charType>
	String<charType> String<charType>::Append(const String& a, const String& b)
	{
		uint32 aSize = a.m_Size;
		uint32 newSize = aSize + b.m_Size;
		char* characters = new char[STRING_SIZE];

		uint32 i = 0;
		while (a[i] != String<charType>::null_terminator)
		{
			characters[i] = a[i];
			i++;
		}

		i = 0;
		while (b[i] != String<charType>::null_terminator)
		{
			characters[i + aSize] = b[i];
			i++;
		}

		characters[aSize] = String<charType>::null_terminator;

		return String(characters);
	}

	template<typename charType>
	uint32 String<charType>::Find(const ANSICHAR* subString, uint32 start) const
	{
		return -1;
	}

	template<typename charType>
	uint32 String<charType>::Find_First_Of(const ANSICHAR* subString) const
	{
		return -1;
	}

	template<typename charType>
	uint32 String<charType>::Find_Last_Of(const ANSICHAR* subString) const
	{
		return -1;
	}

	template<typename charType>
	std::vector<String<charType>> String<charType>::Tokenize(const ANSICHAR* delimiters)
	{

	}

	template<typename charType>
	void String<charType>::GetSubString(const uint32& start, const uint32& end, String& out) const
	{

	}

	template<typename charType>
	void String<charType>::Split(const ANSICHAR* substring, String& first, String& second, uint32 start) const
	{

	}

	template<typename charType>
	void String<charType>::Swap(const uint32& a, const uint32& b)
	{

	}

	template<typename charType>
	void String<charType>::ToUpper(String& s) const
	{
		uint32 i = 0;
		while (i < m_Size)
		{
			s[i] = toupper(m_Characters[i]);
		}
	}

	template<typename charType>
	void String<charType>::ToLower(String& s) const
	{
		uint32 i = 0;
		while (i < m_Size)
		{
			s[i] = tolower(m_Characters[i]);
		}
	}

	template<typename charType>
	int32 String<charType>::ToNumber() const
	{
		if (m_IsNumeric)
		{
			return atoi(m_Characters);
		}

		return INDEX_NONE;
	}

	template<typename charType>  template<typename T>
	String<charType> String<charType>::FromNumber(const T n)
	{
		BH_CORE_ASSERT(false, "Type not supported!");
		return String();
	}


	template<typename charType>
	String<charType> String<charType>::AsFormatedNumber(const int32 number)
	{
		String s = String::FromNumber(number);

		if (s.m_Size > 3)
		{
			//s.Insert(s.m_Size - 3, ",");
		}

		if (s.m_Size > 7)
		{
			//s.Insert(s.m_Size - 7, ",");
		}

		return s;
	}

	template<typename charType>
	String<charType> String<charType>::operator+(const charType* other)
	{
		return Append(*this, other);
	}

	template<typename charType>
	String<charType> String<charType>::operator+(const String& other)
	{
		return Append(*this, other);
	}

	template<typename charType> template<typename T>
	String<charType> String<charType>::operator+(T n)
	{
		return Append(*this, FromNumber(n));
	}

	template<typename charType>
	String<charType> String<charType>::operator+=(const String& other)
	{
		return *this = Append(*this, other);
	}

	template<typename charType> template<typename T>
	String<charType>& String<charType>::operator=(const T& n)
	{
		return *this = FromNumber(n);
	}

	template<typename charType>
	String<charType>& String<charType>::operator=(const String& other)
	{
		m_Size = other.m_Size;
		m_Capacity = other.m_Capacity;
		CharacterArrayHelper::CopyCharacters(m_Characters, other.m_Characters, m_IsNumeric);
		return *this;
	}

	template<typename charType>
	bool String<charType>::operator==(const String& other) const
	{ 
		return Equals(other, ESearchCase::CaseSensitive); 
	}

	template<typename charType>
	charType& String<charType>::operator[](uint32 index) const
	{ 
		BH_CORE_ASSERT(!IsValidIndex(index), "Invalid index"); return m_Characters[index]; 
	}

	template<typename charType>
	const charType* String<charType>::operator*() const
	{ 
		return m_Characters; 
	}

	template<typename charType>
	const char String<charType>::null_terminator = '\0';

	template<typename charType>
	void CharacterArrayHelper::InitializeString(const String<charType>& string, uint32 size, uint32 len)
	{
		string.Resize(len);

		uint32 i = 0;
		while (i < size)
		{
			string.m_Characters[i] = ' ';
			i++;
		}

		string.m_Characters[size] = String<charType>::null_terminator;

		return;
	}

	template<typename charType>
	void CharacterArrayHelper::CopyString(String<charType>& toString, const String<charType>& fromString, bool& numeric)
	{
		uint32 len = fromString.m_Size;

		if (NeedToResizeString(toString, len))
		{
			toString.Resize(len);
		}

		bool num = true;

		uint32 i = 0;
		while (fromString[i] != String<charType>::null_terminator)
		{
			toString[i] = fromString[i];

			if (!isdigit(toString[i]) && num == true)
			{
				num = false;
				numeric = num;
			}

			i++;
		}

		toString[len] = String<charType>::null_terminator;

		return;
	}

	template<typename charType>
	void CharacterArrayHelper::CopyCharactersToString(String<charType>& toString, const charType* characters)
	{
		uint32 i = 0;
		while (characters[i] != String<charType>::null_terminator)
		{
			toString[i] = characters[i];
			i++;
		}

		toString[i] = String<charType>::null_terminator;
	}

	template<typename charType>
	void CharacterArrayHelper::CopyCharacters(charType* to, const charType* from)
	{
		uint32 i = 0;
		while (from[i] != String<charType>::null_terminator)
		{
			to[i] = from[i];
			i++;
		}

		to[i] = String<charType>::null_terminator;
	}

	template<typename charType>
	void CharacterArrayHelper::CopyCharacters(charType* to, const charType* from, bool& numeric)
	{
		bool num = true;
		uint32 i = 0;
		while (from[i] != String<charType>::null_terminator)
		{
			to[i] = from[i];

			if (!isdigit(to[i]) && num == true)
			{
				num = false;
				numeric = num;
			}

			i++;
		}

		to[i] = String<charType>::null_terminator;
	}

	template<typename charType>
	uint32 CharacterArrayHelper::GetCharArraySize(const charType* characters)
	{
		uint32 i = 0;
		while (characters[i] != String<charType>::null_terminator) { i++; }
		return i;
	}

	template<typename charType>
	bool CharacterArrayHelper::NeedToResizeString(const String<charType>& string, uint32 newLen)
	{
		return string.m_Capacity < newLen;
	}
}