#ifndef FSTRING_H
#define FSTRING_H

namespace BHive
{
	class FString;
	class FStringHashFunction;

	#define DEFAULT_STRING_CAP 24
	#define INDEX_NONE -1
	#define MAX_FLOAT_DIGITS DBL_MAX_10_EXP + 2
	#define MAX_INT_DIGITS 11
	#define MAX_UINT_DIGITS 10

	namespace ESearchCase
	{
		enum Type
		{
			CaseSensitive,
			IgnoreCase
		};
	}

	namespace EStringType
	{
		enum Type
		{
			Default,
			Name
		};
	}

	class FString
	{
	public:
		FString();
		FString(const ANSICHAR* c, EStringType::Type type = EStringType::Default);
		explicit FString(uint32 length);
		FString(const FString& other);
		FString(FString&& other);
		~FString();

	private:
		char* charArray;
		uint32 size;
		EStringType::Type stringType;

	public:
		//Get a character from the string
		const char GetCharacter(uint32 index) const;

		//Get the string as a char array
		const char* GetCharArray() const;

		//Get the size of the string
		uint32 Size() const;

		//Is the string empty
		inline bool IsEmpty() const;

		//Is the string only numbers
		inline bool IsNumeric() const;

		//is the index within range
		bool IsValidIndex(const uint32& index) const;

		//insert a character at given position
		void Insert(uint32 index, const char& character);
		void Insert(uint32 index, const FString& characters);

		//concatenate a string to string
		FString Append(const FString& s);

		//Find a substring in the string
		uint32 Find(const FString& subString) const;

		//Get a substring at index
		FString SubString(const uint32& start, const uint32& end) const;

		//Remove character from string
		void RemoveCharacter(const uint32& index);

		//Remove Substring from string
		void RemoveCharacters(const uint32& start, const uint32& end);

		//Split string at string index
		void Split(const FString& substring, FString& first, FString& second) const;

		//Clear the string
		void Clear();

		//Swap string characters
		void Swap(const uint32& a, const uint32& b);

		//convert this to uppercase
		FString& ToUpperCase();

		//convert this to lowercase
		FString& ToLowerCase();

		//return a uppercase version of this
		FString ToUpper() const;

		//return a lowercase version of this
		FString ToLower() const;

		//Set a character to new character
		void SetCharacter(const uint32& index, const char& character);

		//return a boolean value if string equals true or false | 0
		bool ToBool() const;

		//return a number if numeric else return 0
		int32 ToNumber() const;

		//Check if two strings are equal
		static bool Compare(const FString& a, const FString& b, ESearchCase::Type searchCase = ESearchCase::IgnoreCase);
		bool Equals(const FString& other, ESearchCase::Type searchCase = ESearchCase::IgnoreCase) const;

		//Create from number
		static FString FromInt(const int32& number);
		static FString FromUInt(const uint32& number);
		static FString FromFloat(const float& number);
		static FString FromBool(const bool& boolean);
		//format the string from a number ex : 2220 = 2,220
		static FString AsFormatedNumber(const int32& number);

		//return index if a name
		uint64 GetIndex();

		const char* operator*() const;
		FString& operator+(const FString& other);
		FString& operator+(const int32& number);
		FString& operator+(const uint32& number);
		FString& operator+(const float& number);
		FString& operator+=(const FString& other);
		FString& operator=(const FString& other);
		FString& operator=(FString&& other);
		FString& operator=(const int32& number);
		bool operator==(const FString& other) const;
		char& operator[](const uint32& index);
		const char& operator[](const uint32& index) const;


	private:
		uint64 id;
		static std::vector<uint64> unusedIDs;

		inline void AppendStrings(FString& a, const FString& b);

		uint64 GenerateID();

		friend std::ostream& operator<<(std::ostream& os, const FString& s);
		friend FStringHashFunction;
	};

	inline std::ostream& operator<<(std::ostream& os, const FString& s)
	{
		return os << *s;
	}

	inline std::istream& operator>>(std::istream& is, const FString& s)
	{
		return is >> *s;
	}

	inline uint32 GetConstCharSize(const char* c)
	{
		//PROFILE(GetConstCharSize)

		uint32 i = 0;
		while (c[i] != 0)
		{
			i++;
		}

		return i;
	}

	//Copy a char pointer to another will automatically add a null terminator at end of array, size is number characters
	inline void CopyCharArray(char* to, const char* from, const uint32& size)
	{
		//PROFILE(CopyCharArray);

		uint32 i = 0;
		while (i < size)
		{
			to[i] = from[i];
			i++;
		}

		to[size] = 0;
	}

	//A char pointer with empty chars, will automatically add a null terminator at end of array, size is number characters
	inline void CreateEmptyCharArray(char* cArray, const uint32& size)
	{
		//PROFILE(CreateEmptyCharArray)

		uint32 i = 0;
		while (i < size)
		{
			cArray[i] = ' ';
			i++;
		}
		cArray[size] = 0;
	}

	class FStringHashFunction
	{
	public:
		inline uint64 operator()(const FString& s) const
		{
			return s.id;
		}
	};
}

#endif