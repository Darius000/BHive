#include "BHivePCH.h"
#include "FString.h"

namespace BHive
{
	FString::FString()
		:FString("")
	{

	}

	FString::FString(const ANSICHAR* c, EStringType::Type type)
		: charArray(nullptr), size(0), stringType(type), id(-1)
	{
		size = GetConstCharSize(c);
		charArray = new char[size + 1];
		CopyCharArray(charArray, c, size);

		if (type == EStringType::Name)
		{
			id = GenerateID();
		}
	}

	FString::FString(const FString& other)
		:FString("")
	{
		//cout << "Copying String" << "\n";

		//Copy the data from other object
		size = other.size;
		charArray = new char[size + 1];
		CopyCharArray(charArray, other.charArray, size);
		//strcpy_s(charArray, size + 1, other.charArray);	
	}

	FString::FString(FString&& other)
		:FString("")
	{
		//cout << "Moving String" << "\n";

		//Copy the data from other object
		size = other.size;
		charArray = new char[size + 1];
		//strcpy_s(charArray, size + 1, other.charArray);
		CopyCharArray(charArray, other.charArray, size);

		//Release the data from other object
		other.charArray = nullptr;
		other.size = 0;
	}

	FString::FString(uint32 length)
		:FString("")
	{
		size = length;
		charArray = new char[size + 1];
		CreateEmptyCharArray(charArray, size);
	}

	FString::~FString()
	{
		//free existing resource
		delete[] charArray;

		size = 0;

		if (stringType == EStringType::Name)
		{
			unusedIDs.push_back(id);
		}
	}

	const char FString::GetCharacter(uint32 index) const
	{
		//PROFILE(GetCharacter)

			return charArray[index];
	}

	const char* FString::GetCharArray() const
	{
		//PROFILE(GetCharArray)

		return charArray;
	}

	uint32 FString::Size() const
	{
		//PROFILE(Size)

		return size;
	}

	bool FString::IsEmpty() const
	{
		//PROFILE(IsEmpty)

		return size == 0;
	}

	bool FString::IsNumeric() const
	{
		//PROFILE(IsNumeric)

		for (uint32 i = 0; i < size; i++)
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
		//PROFILE(IsValidIndex)

		return index < size;
	}

	void FString::Insert(uint32 index, const FString& characters)
	{
		//PROFILE(InsertCharacters)

		for (uint32 i = 0; i < characters.size; i++)
		{
			Insert(index + i, characters[i]);
		}
	}

	void FString::Insert(uint32 index, const char& character)
	{
		//PROFILE(InsertCharacter)

		if (index > size)
			return;

		uint32 newSize = size + 1;
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
		size = newSize;

		delete[] charArray;
		charArray = new char[size + 1];
		CopyCharArray(charArray, temp, size);
		delete[] temp;
	}

	FString FString::Append(const FString& s)
	{
		//PROFILE(Append)

		return *this += s;
	}

	uint32 FString::Find(const FString& subString) const
	{
		//PROFILE(Find)

		char* substr = nullptr;
		substr = strstr(charArray, *subString);
		uint32 index = 0;

		if (!substr)
			return INDEX_NONE;

		for (uint32 i = 0; i < size; i++)
		{
			if (charArray[i] == substr[0])
			{
				index = i;
				break;
			}
		}

		return index;
	}

	FString FString::SubString(const uint32& start, const uint32& end) const
	{
		//PROFILE(Substring)

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
		//PROFILE(RemoveCharacter);

		char* temp = new char[size + 1];
		for (uint32 i = 0; i < size; i++)
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
		temp[size - 1] = 0;
		size -= 1;

		delete[] charArray;
		charArray = new char[size + 1];
		CopyCharArray(charArray, temp, size);
		delete[] temp;
	}

	void FString::RemoveCharacters(const uint32& start, const uint32& end)
	{
		//PROFILE(RemoveCharacters)

		uint32 diff = (end + 1) - start; //store the number of characters that will be removed
		uint32 newSize = size - diff;
		char* temp = new char[newSize + 1];
		for (uint32 i = 0; i < size; i++)
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
		size = newSize;

		delete[] charArray;
		charArray = new char[size + 1];
		CopyCharArray(charArray, temp, size);
		delete[] temp;
	}

	void FString::Split(const FString& substring, FString& first, FString& second) const
	{
		//PROFILE(Split)

		uint32 index = Find(substring);

		if (index != INDEX_NONE)
		{
			first = SubString(0, index - 1);
			second = SubString(index + 1, size);
		}
	}

	void FString::Clear()
	{
		//PROFILE(Clear)

		size = 0;
		delete[] charArray;
		charArray = new char[size + 1];
		charArray[size] = 0;
	}

	void FString::Swap(const uint32& a, const uint32& b)
	{
		//PROFILE(Swap)

		const char tmpA = charArray[a];
		const char tmpB = charArray[b];

		SetCharacter(a, tmpB);
		SetCharacter(b, tmpA);
	}

	FString& FString::ToUpperCase()
	{
		//PROFILE(ToUpperCase)

		for (uint32 i = 0; i < size; i++)
		{
			charArray[i] = toupper(charArray[i]);
		}

		return *this;
	}

	FString& FString::ToLowerCase()
	{
		//PROFILE(ToLowerCase)

		for (uint32 i = 0; i < size; i++)
		{
			charArray[i] = tolower(charArray[i]);
		}

		return *this;
	}

	FString FString::ToUpper() const
	{
		//PROFILE(ToUpper)

		char* c = new char[size + 1];
		CopyCharArray(c, charArray, size);
		//strcpy_s(c, size + 1, this->charArray);
		FString s(c);
		delete[] c;
		return s.ToUpperCase();
	}

	FString FString::ToLower() const
	{
		//PROFILE(ToLower)

		char* c = new char[size + 1];
		CopyCharArray(c, charArray, size);
		//strcpy_s(c, size + 1, this->charArray);
		FString s(c);
		delete[] c;
		return s.ToLowerCase();
	}

	void FString::SetCharacter(const uint32& index, const char& character)
	{
		//PROFILE(SetCharacter)

		if (index >= 0 && index < size)
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
		//PROFILE(ToBool)

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
		//PROFILE(ToNumber)

		if (IsNumeric())
		{
			return atoi(charArray);
		}

		return  0;
	}

	bool FString::Compare(const FString& a, const FString& b, ESearchCase::Type searchCase)
	{
		//PROFILE(Compare)

		return a.Equals(b);
	}

	bool FString::Equals(const FString& other, ESearchCase::Type searchCase /*= ESearchCase::IgnoreCase*/) const
	{
		//PROFILE(Equals)

		//Check size first
		if (size != other.size)
				return false;

		if (searchCase == ESearchCase::CaseSensitive)
		{
			//Check characters for case as well
			for (uint32 i = 0; i < size; i++)
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
			for (uint32 i = 0; i < size; i++)
			{
				if (tolower(charArray[i]) != tolower(other[i]))
				{
					return false;
				}
			}
		}

		return true;
	}

	FString FString::FromInt(const int32& number)
	{
		//PROFILE(FromInt)

		char c[MAX_INT_DIGITS];
		sprintf_s(c, "%d", number);
		return FString(c);
	}

	FString FString::FromUInt(const uint32& number)
	{
		char c[MAX_UINT_DIGITS];
		sprintf_s(c, "%u", number);
		return FString(c);
	}

	FString FString::FromFloat(const float& number)
	{
		char c[MAX_FLOAT_DIGITS];
		sprintf_s(c, "%f", number);
		return FString(c);
	}

	FString FString::FromBool(const bool& boolean)
	{
		//PROFILE(FromBool)

		FString s;
		return  s = boolean ? "true" : "false";
	}

	FString FString::AsFormatedNumber(const int32& number)
	{
		//PROFILE(AsFormatedNumber)

		FString s = FString::FromInt(number);

		if (s.size > 3)
		{
			s.Insert(s.size - 3, ",");
		}

		if (s.size > 7)
		{
			s.Insert(s.size - 7, ",");
		}

		return s;
	}

	uint64 FString::GetIndex()
	{
		if (stringType != EStringType::Name)
		{
			return -1;
		}

		return id;
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

	FString& FString::operator+(const int32& number)
	{
		AppendStrings(*this, FromInt(number));
		return *this;
	}

	FString& FString::operator+(const float& number)
	{
		AppendStrings(*this, FromFloat(number));
		return *this;
	}

	FString& FString::operator+(const uint32& number)
	{
		AppendStrings(*this, FromUInt(number));
		return *this;
	}

	FString& FString::operator=(const int32& number)
	{
		return *this = FromInt(number);
	}

	bool FString::operator==(const FString& other) const
	{
		return this->Equals(other, ESearchCase::CaseSensitive);
	}

	char& FString::operator[](const uint32& index)
	{
		return charArray[index];
	}

	const char& FString::operator[](const uint32& index) const
	{
		return charArray[index];
	}

	std::vector<uint64> FString::unusedIDs;

	void FString::AppendStrings(FString& a, const FString& b)
	{
		uint32 appendSize = a.Size() + b.size;

		char* temp = new char[appendSize + 1];
		uint32 i = 0;
		while (i < a.size)
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
		a.size = appendSize;

		delete[] temp;
	}

	uint64 FString::GenerateID()
	{
		if (unusedIDs.size() == 0)
		{
			return id++;
		}

		uint64 existingID = unusedIDs[0];
		unusedIDs.erase(unusedIDs.begin());
		return existingID;
	}

	FString& FString::operator=(FString&& other)
	{
		//cout << "Moving String" << "\n";

		if (this != &other)
		{
			//free existing resource
			delete[] charArray;

			//Copy the data from other object
			size = other.size;
			charArray = new char[size + 1];
			//strcpy_s(charArray, size + 1, other.charArray);
			CopyCharArray(charArray, other.charArray, size);

			//Release the data from other object
			other.charArray = nullptr;
			other.size = 0;
		}

		return *this;
	}

	FString& FString::operator=(const FString& other)
	{
		//cout << "Copying String" << "\n";

		//Copy data from other object
		size = other.size;
		charArray = new char[size + 1];
		//strcpy_s(charArray, size + 1, other.charArray);
		CopyCharArray(charArray, other.charArray, size);

		return *this;
	}
}