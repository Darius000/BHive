#pragma once

namespace BHive
{
	class FString;

	#define DEFAULT_STRING_CAP 24
	#define MAX_FLOAT_DIGITS DBL_MAX_10_EXP + 2
	#define MAX_INT_DIGITS 11
	#define MAX_UINT_DIGITS 10
	#define NULL_TERMINATOR '\0'
	#define NEWLINE '\n'
	#define NEWLINERETURN '\r\n'

	namespace ESearchCase
	{
		enum Type
		{
			CaseSensitive,
			IgnoreCase
		};
	}

	class FString
	{
	public:
		FString();
		FString(const ANSICHAR* c);
		explicit FString(uint32 length);
		FString(const FString& other);
		FString(FString&& other);
		~FString();	
	private:
		char* charArray;
		uint32 m_Size;
	public:
		const char GetCharacter(uint32 index) const { return charArray[index]; }
		uint32 Size() const { return m_Size; }
		void Resize(uint32 size);
		inline bool IsEmpty() const;
		inline bool IsNumeric() const;
		bool IsValidIndex(const uint32& index) const;
		void Insert(uint32 index, const char& character);
		void Insert(uint32 index, const FString& characters);
		FString Append(const FString& s);
		uint32 Find(const FString& subString, uint32 start) const;
		uint32 Find_Last_Of(const FString& subString) const;
		FString SubString(const uint32& start, const uint32& end) const;
		void RemoveCharacter(const uint32& index);
		void RemoveCharacters(const uint32& start, const uint32& end);
		void Split(const FString& substring, FString& first, FString& second, uint32 start) const;
		void Clear();
		void Swap(const uint32& a, const uint32& b);
		FString& ToUpperCase();
		FString& ToLowerCase();
		FString ToUpper() const;
		FString ToLower() const;
		void SetCharacter(const uint32& index, const char& character);
		bool ToBool() const;
		int32 ToNumber() const;
		static bool Compare(const FString& a, const FString& b, ESearchCase::Type searchCase = ESearchCase::IgnoreCase);
		bool Equals(const FString& other, ESearchCase::Type searchCase = ESearchCase::IgnoreCase) const;

		template<typename T>
		static FString FromNumber(const T& n);
		static FString AsFormatedNumber(const int32& number);

		const char* operator*() const;
		FString& operator+(const FString& other);
		template<typename T>
		FString& operator+(T n);
		FString& operator+=(const FString& other);
		FString& operator=(const FString& other);
		template<typename T>
		FString& operator=(const T& n);
		bool operator==(const FString& other) const;
		char& operator[](uint32 index);
		const char& operator[](uint32 index) const;
		static const uint32 npos;

	private:

		inline void AppendStrings(FString& a, const FString& b);

		friend std::ostream& operator<<(std::ostream& os, const FString& s);
public:
	
	};

	template<typename T>
	FString FString::FromNumber(const T& n)
	{
		BH_CORE_ASSERT(false, "Type not supported!");
		return FString();
	}

	template<>
	inline FString FString::FromNumber(const int32& n)
	{
		char c[MAX_INT_DIGITS];
		sprintf_s(c, "%d", n);
		return FString(c);
	}

	template<>
	inline FString FString::FromNumber(const uint32& n)
	{
		char c[MAX_UINT_DIGITS];
		sprintf_s(c, "%u", n);
		return FString(c);
	}

	template<>
	inline FString FString::FromNumber(const float& n)
	{
		char c[MAX_FLOAT_DIGITS];
		sprintf_s(c, "%f", n);
		return FString(c);
	}

	template<>
	inline FString FString::FromNumber(const bool& n)
	{
		FString s;
		return  s = n ? "true" : "false";
	}

	template<typename T>
	FString& FString::operator+(T n)
	{
		AppendStrings(*this, FromNumber(n));
		return *this;
	}

	template<typename T>
	FString& FString::operator=(const T& n)
	{
		return *this = FromNumber(n);
	}

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
		uint32 i = 0;
		while (c[i] != 0)
		{
			i++;
		}

		return i;
	}

	inline void CopyCharArray(char* to, const char* from, const uint32& size)
	{
		uint32 i = 0;
		while (i < size)
		{
			to[i] = from[i];
			i++;
		}

		to[size] = 0;
	}

	inline void CreateEmptyCharArray(char* cArray, const uint32& size)
	{
		for (uint32 i = 0; i < size; i ++)
		{
			cArray[i] = ' ';
		}
		cArray[size] = '\0';
	}
}
