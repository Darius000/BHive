#pragma once

namespace BHive
{
	#define DEFAULT_STRING_CAP 24
	#define MAX_FLOAT_DIGITS DBL_MAX_10_EXP + 2
	#define MAX_INT_DIGITS 11
	#define MAX_UINT_DIGITS 10
	#define NULL_TERMINATOR '\0'
	#define NEW_LINE '\n'
	#define NEW_LINE_RETURN '\r\n'
	#define RESERVE_SIZE 1024
	#define MAKE_SCOPED_ARRAY(size, type) std::make_unique<type[]>(size)

	namespace ESearchCase
	{
		enum Type
		{
			CaseSensitive,
			IgnoreCase
		};
	}

	template<typename charType>
	class String
	{
	public:
		String() : String("") {}

		String(const charType* c) : m_Size(GetCharArraySize(c)), m_Chars(MAKE_SCOPED_ARRAY(m_Size, charType)) 
		{
			CopyCharArray(m_Chars.get(), c, m_Size, m_IsNumeric);
		}

		String(const charType* c, uint32 len)
		{
			m_Size = len;
			CopyCharArray(m_Chars.get(), c, len, m_IsNumeric);
		}

		explicit String(uint32 length)
		{
			m_Size = length;
			m_Chars = MAKE_SCOPED_ARRAY(m_Size, ANSICHAR);
			InitCharArray(m_Chars.get(), m_Size);
		}

		String(const String& other) 
		{
			m_Size = other.m_Size;
			m_Chars = MAKE_SCOPED_ARRAY(m_Size, charType);
			CopyCharArray(m_Chars.get(), other.m_Chars.get(), m_Size, m_IsNumeric);
		}

		String(String&& other)
		{
			m_Size = other.m_Size;
			m_Chars = MAKE_SCOPED_ARRAY(m_Size, charType);
			CopyCharArray(m_Chars.get(), other.m_Chars.get(), m_Size, m_IsNumeric);
			//Release the data from other object
			other.m_Chars = nullptr;
			other.m_Size = 0;
		}

		virtual ~String() {};

	private:
		Scope<charType[]> m_Chars;
		uint32 m_Size;

	public:
		charType GetCharacter(uint32 index) const 
		{ 
			BH_CORE_ASSERT(!IsValidIndex(index), "Invalid Index");
			return m_Chars[index]; 
		}

		uint32 Size() const { return m_Size; }

		void Resize(uint32 size)
		{
			const charType* temp = m_Chars.get();
			m_Chars = MAKE_SCOPED_ARRAY(size, charType);
			CopyCharArray(m_Chars.get(), temp, m_Size, m_IsNumeric);
			m_Size = size;
		}

		void Reset(const charType* chars, uint32 size)
		{
			m_Size = size;
			m_Chars = MAKE_SCOPED_ARRAY(size, charType);
			CopyCharArray(m_Chars.get(), m_Chars.get(), size, m_IsNumeric);
		}

		bool IsEmpty() const { return m_Size == 0; }

		bool IsNumeric() const { return m_IsNumeric; }

		bool IsValidIndex(const uint32& index) const { return index < m_Size && index > 0; }

		String Append(const String& a, const String b)
		{
			return String();
		}

		uint32 Find(const charType* subString, uint32 start) const
		{
			return -1;
		}

		uint32 Find_First_Of(const charType* subString) const
		{
			return -1;
		}

		uint32 Find_Last_Of(const charType* subString) const
		{
			return -1;
		}

		void GetSubString(const uint32& start, const uint32& end, String& out) const
		{
			
		}

		void Split(const charType* substring, String& first, String& second, uint32 start) const
		{
			BH_CORE_ASSERT(!IsValidIndex(start), "Invalid Index");

			uint32 index = Find(substring, start);

			if (index != INDEX_NONE)
			{
				GetSubString(0, index - 1, first);
				GetSubString(index + 1, m_Size, second);
			}
		}

		void Swap(const uint32& a, const uint32& b)
		{
			BH_CORE_ASSERT(!IsValidIndex(a) || !IsValidIndex(b), "Invalid Index");

			const charType tmpA = m_Chars[a];
			const charType tmpB = m_Chars[b];

			SetCharacter(a, tmpB);
			SetCharacter(b, tmpA);
		}

		void ToUpper(String& s) const
		{
			uint32 i = 0;
			while (i < m_Size)
			{
				s[i] = toupper(m_Chars[i]);
			}
		}

		void ToLower(String& s) const
		{
			uint32 i = 0;
			while (i < m_Size)
			{
				s[i] = tolower(m_Chars[i]);
			}
		}

		void SetCharacter(const uint32& index, const char& character)
		{
			BH_CORE_ASSERT(!IsValidIndex(index), "Invalid Index");

			m_Chars[index] = character;
		}

		bool ToBool() const
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

		int32 ToNumber() const
		{
			if (IsNumeric())
			{
				return atoi(m_Chars.get());
			}

			return INDEX_NONE;
		}

		static bool Compare(const String& a, const String& b, ESearchCase::Type searchCase = ESearchCase::IgnoreCase) 
		{ 
			return a.Equals(b); 
		}

		bool Equals(const String& other, ESearchCase::Type searchCase = ESearchCase::IgnoreCase) const
		{
			if (m_Size != other.m_Size)
				return false;

			if (searchCase == ESearchCase::CaseSensitive)
			{
				//Check characters for case as well
				for (uint32 i = 0; i < m_Size; i++)
				{
					if (m_Chars[i] != other[i])
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
					if (tolower(m_Chars[i]) != tolower(other[i]))
					{
						return false;
					}
				}
			}

			return true;
		}

		template<typename T>
		static String FromNumber(const T n)
		{
			BH_CORE_ASSERT(false, "Type not supported!");
			return String();
		}

		String AsFormatedNumber(const int32 number)
		{
			String s = String::FromNumber(number);

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

		const charType* c_str() const 
		{
			return m_Chars.get();
		}

		const charType* operator*() const 
		{ 
			return m_Chars.get(); 
		}

		String operator+(const String& other)
		{	
			return Append(*this, other);
		}

		template<typename T>
		String operator+(T n)
		{	
			return Append(*this, FromNumber(n));
		}

		String operator+=(const String& other)
		{		
			return *this = Append(*this, other);;
		}

		String& operator=(const String& other)
		{
			m_Size = other.m_Size;
			Resize(m_Size);
			CopyCharArray(m_Chars.get(), other.m_Chars.get(), m_Size, m_IsNumeric);
			return *this;
		}

		template<typename T>
		String& operator=(const T& n) 
		{ 
			return *this = FromNumber(n); 
		}

		bool operator==(const String& other) const 
		{ 
			return this->Equals(other, ESearchCase::CaseSensitive); 
		}

		charType& operator[](const uint32 index) 
		{ 
			return m_Chars[index]; 
		}

		const charType& operator[](const uint32 index) const 
		{ 
			return m_Chars[index]; 
		}

		static const uint32 npos = INDEX_NONE;

	public:
		static uint32 GetCharArraySize(const charType* c)
		{
			BH_CORE_ASSERT(c == nullptr , "null char pointer");

			uint32 i = 0;
			while (c[i] != NULL_TERMINATOR) { i++; }
			return i;
		}

		static void InitCharArray(charType* c,const uint32 len)
		{
			BH_CORE_ASSERT(c == nullptr, "null char pointer")

			uint32 i = 0;
			while (i < len) { c[i] = " "; }
			c[len] = NULL_TERMINATOR;
		}

		static void CopyCharArray(charType* to, const charType* from, const uint32 len, bool& numeric)
		{
			BH_CORE_ASSERT(to == nullptr || from == nullptr, "null char pointer");

			uint32 i = 0;
			bool temp = true;
			while (i < len && from[i] != NULL_TERMINATOR)
			{
				to[i] = from[i];
				if (!isdigit(to[i]) && temp == true)
				{
					temp = false;
					numeric = temp;
				}

				i++;
			}

			to[len] = NULL_TERMINATOR;
		}

	private:
		bool m_IsNumeric;
	};

	template<typename charType>
	std::ostream& operator<<(std::ostream& os, const String<charType>& s)
	{
		return os << *s;
	}

	template<typename charType>
	std::istream& operator>>(std::istream& is, const String<charType>& s)
	{
		return is >> *s;
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

	using FString =  String<ANSICHAR>;
	using WString =  String<WIDECHAR>;
	using Path = String<ANSICHAR>;
}
