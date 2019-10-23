#pragma once

namespace BHive
{
	#define DEFAULT_STRING_CAP 24
	#define MAX_FLOAT_DIGITS DBL_MAX_10_EXP + 2
	#define MAX_INT_DIGITS 11
	#define MAX_UINT_DIGITS 10

	enum { STRING_SIZE = 1024 };

	enum class ESearchCase : uint8
	{
		CaseSensitive,
		CaseInSensitive
	};

	template<typename charType>
	class String 
	{
	public:
		String();

		String(const charType* c);

		String(const charType* c, uint32 len);

		explicit String(uint32 len);

		String(const String& other);

		~String();
		
	public:
		void Resize(uint32 len);

		//shrinks the char array capacity to size
		void Shrink();

		uint32 Size() const { return m_Size; }

		uint32 Capacity() const { return m_Capacity; }

		bool IsEmpty() const { return m_Size == 0; }

		bool IsNumeric() const { return m_IsNumeric; }

		bool IsValidIndex(uint32 index) const;

		bool Equals(const String& other, ESearchCase searchCase) const;

		void Reset(uint32 size);

		void SetCharacter(uint32 index,const char& character);

		String Append(const String& a, const String& b);

		uint32 Find(const ANSICHAR* subString, uint32 start) const;	

		uint32 Find_First_Of(const ANSICHAR* subString) const;

		uint32 Find_Last_Of(const ANSICHAR* subString) const;

		std::vector<String> Tokenize(const ANSICHAR* delimiters);	

		void GetSubString(const uint32& start, const uint32& end, String& out) const;	

		void Split(const ANSICHAR* substring, String& first, String& second, uint32 start) const;

		void Swap(const uint32& a, const uint32& b);

		void ToUpper(String& s) const;

		void ToLower(String& s) const;

		int32 ToNumber() const;
		
		template<typename T>
		String FromNumber(const T n);

		String AsFormatedNumber(const int32 number);

		String operator+(const charType* other);

		String operator+(const String& other);

		template<typename T>
		String operator+(T n);

		String operator+=(const String& other);

		String& operator=(const String& other);

		template<typename T>
		String& operator=(const T& n);

		bool operator==(const String& other) const;

		charType& operator[](uint32 index) const;

		const charType* operator*() const;

		static const char null_terminator;

	private:
		charType* m_Characters;
		uint32 m_Size = 0;
		uint32 m_Capacity = STRING_SIZE;
		bool m_IsNumeric;

		friend class CharacterArrayHelper;

		template<typename>
		friend class Name;

		friend std::ostream& operator<<(std::ostream& os, const String& s);
	};

	template<typename charType>
	std::ostream& operator<<(std::ostream& os, const String<charType>& s)
	{
		return os << *s;
	}
	
	template<> template<>
	inline String<ANSICHAR> String<ANSICHAR>::FromNumber(const int32 n)
	{
		ANSICHAR c[MAX_INT_DIGITS];
		sprintf_s(c, "%d", n);
		return String(c);
	}

	template<> template<>
	inline String<ANSICHAR> String<ANSICHAR>::FromNumber(const uint32 n)
	{
		ANSICHAR c[MAX_UINT_DIGITS];
		sprintf_s(c, "%u", n);
		return String(c);
	}

	template<> template<>
	inline String<ANSICHAR> String<ANSICHAR>::FromNumber(const float n)
	{
		ANSICHAR c[MAX_FLOAT_DIGITS];
		sprintf_s(c, "%f", n);
		return String(c);
	}

	template<> template<>
	inline String<ANSICHAR> String<ANSICHAR>::FromNumber(const bool n)
	{
		String s;
		return  s = n ? "true" : "false";
	}

	class CharacterArrayHelper
	{
	public:
		template<typename charType>
		static void InitializeString(const String<charType>& string, uint32 size, uint32 len);

		template<typename charType>
		static void CopyString(String<charType>& toString, const String<charType>& fromString, bool& numeric);

		template<typename charType>
		static void CopyCharactersToString(String<charType>& toString, const charType* characters);

		template<typename charType>
		static void CopyCharacters(charType* to, const charType* from);

		template<typename charType>
		static void CopyCharacters(charType* to, const charType* from, bool& numeric);

		template<typename charType>
		static uint32 GetCharArraySize(const charType* characters);

		template<typename charType>
		static bool NeedToResizeString(const String<charType>& string, uint32 newLen);
	};

	typedef String<ANSICHAR> FString;
	typedef String<WIDECHAR> WString;
	typedef FString Path;
}

#include "String.inl"

