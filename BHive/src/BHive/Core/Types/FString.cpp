#include "BHivePCH.h"
#include "FString.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

namespace BHive
{
	FString::FString()
		:FString("")
	{

	}

	FString::FString(const ANSICHAR* c)
		: charArray(nullptr), m_Size(0)
	{
		m_Size = GetConstCharSize(c);
		charArray = new char[m_Size + 1];
		CopyCharArray(charArray, c, m_Size);
	}

	FString::FString(const FString& other)
		:FString("")
	{
		//cout << "Copying String" << "\n";

		//Copy the data from other object
		m_Size = other.m_Size;
		charArray = new char[m_Size + 1];
		CopyCharArray(charArray, other.charArray, m_Size);
		//strcpy_s(charArray, size + 1, other.charArray);	
	}

	FString::FString(FString&& other)
		:FString("")
	{
		//cout << "Moving String" << "\n";

		//Copy the data from other object
		m_Size = other.m_Size;
		charArray = new char[m_Size + 1];
		//strcpy_s(charArray, size + 1, other.charArray);
		CopyCharArray(charArray, other.charArray, m_Size);

		//Release the data from other object
		other.charArray = nullptr;
		other.m_Size = 0;
	}

	FString::FString(uint32 length)
		:FString("")
	{
		m_Size = length;
		charArray = new char[m_Size + 1];
		CreateEmptyCharArray(charArray, m_Size);
	}

	FString::~FString()
	{
		//free existing resource
		delete[] charArray;

		m_Size = 0;
	}

	void FString::Resize(uint32 size)
	{
		m_Size = size;
		charArray = new char[size + 1];
		CreateEmptyCharArray(charArray, m_Size);
	}

	bool FString::IsEmpty() const
	{
		return m_Size == 0;
	}

	bool FString::IsNumeric() const
	{
		for (uint32 i = 0; i < m_Size; i++)
		{
			if (!isdigit(charArray[i]))
			{
				return false;
			}
		}

		return true;
	}

	bool FString::IsValidIndex(const uint32& index) const
	{
		return index < m_Size;
	}

	void FString::Insert(uint32 index, const FString& characters)
	{
		for (uint32 i = 0; i < characters.m_Size; i++)
		{
			Insert(index + i, characters[i]);
		}
	}

	void FString::Insert(uint32 index, const char& character)
	{
		if (index > m_Size)
			return;

		uint32 newSize = m_Size + 1;
		char* temp = new char[newSize + 1];

		for (uint32 i = 0, j = 0; i < newSize; i++)
		{
			if (i < index)
			{
				temp[i] = charArray[i];
			}
			else if (i > index)
			{
				temp[i] = charArray[i - 1]; // - size since we skipped this step by 1
			}
			else
			{
				temp[i] = character;
				j++;
			}
		}

		temp[newSize] = 0;
		m_Size = newSize;

		delete[] charArray;
		charArray = new char[m_Size + 1];
		CopyCharArray(charArray, temp, m_Size);
		delete[] temp;
	}

	FString FString::Append(const FString& s)
	{
		return *this += s;
	}

	uint32 FString::Find(const FString& subString, uint32 start) const
	{
		char * substr = strstr(charArray, *subString);
		uint32 index = start;

		if (!substr)
			return INDEX_NONE;

		bool found = false;

		for (uint32 i = start; i < m_Size && !found; i++)
		{
			if (charArray[i] == substr[0])
			{
				for (uint32 s = 0, j = i; s < subString.Size(); s++)
				{
					if (charArray[j] != substr[s])
					{
						break;
					}
					else
					{
						j++;
						index = i;

						if (s == subString.Size() - 1)
						{
							found = true;
							break;
						}

					}
				}
			}
		}

		return index;
	}

	uint32 FString::Find_Last_Of(const FString& subString) const
	{
		char * substr = strstr(charArray, *subString);
		uint32 index = 0;

		if (!substr)
			return INDEX_NONE;

		for (uint32 i = 0; i < m_Size; i++)
		{
			if (charArray[i] == substr[0])
			{
				for (uint32 s = 0, j = i; s < subString.Size(); s++)
				{
					if (charArray[j] != substr[s])
					{
						break;
					}
					else
					{
						j++;
						index = i;

						if (s == subString.Size() - 1)
						{
							break;
						}

					}
				}
			}
		}

		return index;
	}

	FString FString::SubString(const uint32& start, const uint32& end) const
	{
		uint32 elements = (end + 1) - start; //add one to get last character
		char* c = new char[elements + 1]; // add one for null terminator

		uint32 j = 0;
		for (uint32 i = start; i <= end; i++)
		{
			c[j] = charArray[i];
			j++;
		}

		c[elements] = 0; //get last element to set to null terminator

		FString s = FString(c);
		delete[] c;
		return s;
	}

	void FString::RemoveCharacter(const uint32& index)
	{
		char* temp = new char[m_Size + 1];
		for (uint32 i = 0; i < m_Size; i++)
		{
			if (i < index)
			{
				temp[i] = charArray[i];
			}

			if (i > index)
			{
				temp[i - 1] = charArray[i];//Get the previous characters and move back 1
			}
		}
		temp[m_Size - 1] = 0;
		m_Size -= 1;

		delete[] charArray;
		charArray = new char[m_Size + 1];
		CopyCharArray(charArray, temp, m_Size);
		delete[] temp;
	}

	void FString::RemoveCharacters(const uint32& start, const uint32& end)
	{
		uint32 diff = (end + 1) - start; //store the number of characters that will be removed
		uint32 newSize = m_Size - diff;
		char* temp = new char[newSize + 1];
		for (uint32 i = 0; i < m_Size; i++)
		{
			if (i < start)
			{
				temp[i] = charArray[i];
			}

			if (i > end)
			{
				temp[i - diff] = charArray[i]; //get the last characters and set it to new location by index - characters removed
			}
		}

		temp[newSize] = 0;
		m_Size = newSize;

		delete[] charArray;
		charArray = new char[m_Size + 1];
		CopyCharArray(charArray, temp, m_Size);
		delete[] temp;
	}

	void FString::Split(const FString& substring, FString& first, FString& second, uint32 start) const
	{
		uint32 index = Find(substring, start);

		if (index != INDEX_NONE)
		{
			first = SubString(0, index - 1);
			second = SubString(index + 1, m_Size);
		}
	}

	void FString::Clear()
	{
		m_Size = 0;
		delete[] charArray;
		charArray = new char[m_Size + 1];
		charArray[m_Size] = 0;
	}

	void FString::Swap(const uint32& a, const uint32& b)
	{
		const char tmpA = charArray[a];
		const char tmpB = charArray[b];

		SetCharacter(a, tmpB);
		SetCharacter(b, tmpA);
	}

	FString& FString::ToUpperCase()
	{
		for (uint32 i = 0; i < m_Size; i++)
		{
			charArray[i] = toupper(charArray[i]);
		}

		return *this;
	}

	FString& FString::ToLowerCase()
	{
		for (uint32 i = 0; i < m_Size; i++)
		{
			charArray[i] = tolower(charArray[i]);
		}

		return *this;
	}

	FString FString::ToUpper() const
	{
		char* c = new char[m_Size + 1];
		CopyCharArray(c, charArray, m_Size);
		//strcpy_s(c, size + 1, this->charArray);
		FString s(c);
		delete[] c;
		return s.ToUpperCase();
	}

	FString FString::ToLower() const
	{
		char* c = new char[m_Size + 1];
		CopyCharArray(c, charArray, m_Size);
		//strcpy_s(c, size + 1, this->charArray);
		FString s(c);
		delete[] c;
		return s.ToLowerCase();
	}

	void FString::SetCharacter(const uint32& index, const char& character)
	{
		if (index >= 0 && index < m_Size)
		{
			charArray[index] = character;
		}
		else
		{
			std::cout << "Invalid Index" << "\n";
		}
	}

	bool FString::ToBool() const
	{
		if (Equals("true") || Equals("1") || Equals("yes"))
		{
			return true;
		}

		if (Equals("false") || Equals("0") || Equals("no"))
		{
			return false;
		}

		return false;
	}

	int32 FString::ToNumber() const
	{
		if (IsNumeric())
		{
			return atoi(charArray);
		}

		return  0;
	}

	bool FString::Compare(const FString& a, const FString& b, ESearchCase::Type searchCase)
	{
		return a.Equals(b);
	}

	bool FString::Equals(const FString& other, ESearchCase::Type searchCase /*= ESearchCase::IgnoreCase*/) const
	{
		//Check size first
		if (m_Size != other.m_Size)
				return false;

		if (searchCase == ESearchCase::CaseSensitive)
		{
			//Check characters for case as well
			for (uint32 i = 0; i < m_Size; i++)
			{
				if (charArray[i] != other[i])
				{
					return false;
				}
			}
		}
		else
		{
			//only check if value is same
			for (uint32 i = 0; i < m_Size; i++)
			{
				if (tolower(charArray[i]) != tolower(other[i]))
				{
					return false;
				}
			}
		}

		return true;
	}

	FString FString::AsFormatedNumber(const int32& number)
	{
		FString s = FString::FromNumber(number);

		if (s.m_Size > 3)
		{
			s.Insert(s.m_Size - 3, ",");
		}

		if (s.m_Size > 7)
		{
			s.Insert(s.m_Size - 7, ",");
		}

		return s;
	}

	const char* FString::operator*() const
	{
		return charArray;
	}

	FString& FString::operator+(const FString& other)
	{
		AppendStrings(*this, other);
		return *this;
	}

	FString& FString::operator+=(const FString& other)
	{
		AppendStrings(*this, other);
		return *this;
	}

	bool FString::operator==(const FString& other) const
	{
		return this->Equals(other, ESearchCase::CaseSensitive);
	}

	char& FString::operator[](uint32 index)
	{
		return charArray[index];
	}

	const char& FString::operator[](uint32 index) const
	{
		return charArray[index];
	}

	const uint32 FString::npos = -1;

	void FString::AppendStrings(FString& a, const FString& b)
	{
		uint32 appendSize = a.Size() + b.Size();

		char* temp = new char[appendSize + 1];

		uint32 i = 0;
		while (i < a.m_Size)
		{
			temp[i] = a.GetCharacter(i);
			i++;
		}

		uint32 j = 0;
		while (j < b.Size())
		{
			temp[i + j] = b.GetCharacter(j);
			j++;
		}

		temp[appendSize] = 0;

		a.charArray = new char[appendSize + 1];
		//strcpy_s(a.charArray, appendSize + 1, temp);
		CopyCharArray(charArray, temp, appendSize);
		a.m_Size = appendSize;

		delete[] temp;
	}

	FString& FString::operator=(const FString& other)
	{
		//cout << "Copying String" << "\n";

		//Copy data from other object
		m_Size = other.m_Size;
		charArray = new char[m_Size + 1];
		//strcpy_s(charArray, size + 1, other.charArray);
		CopyCharArray(charArray, other.charArray, m_Size);

		return *this;
	}
}