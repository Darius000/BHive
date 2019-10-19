#pragma once

namespace BHive
{
	enum class ENameCase
	{
		CaseSensitive = 0,
		IgnoreCase
	};

	enum { NAME_SIZE = 1024 };

	class FName
	{
	public:
		FName();
		FName(uint32 len, const ANSICHAR* c);
		FName(uint32 len, const WIDECHAR* wc);
		FName(const ANSICHAR* c);
		FName(const WIDECHAR* wc);
		virtual ~FName() = default;

	public:
		int32 Compare(const FName& other) const;
		uint32 GetSize() const { return m_Size; }
		bool IsEqual(const FName& other, ENameCase nameCase);
		bool IsNone();
		void SetNumber(int32 newNumber);
		FString ToString() const;
		void ToString(const FString& out);

	public:

		bool operator==(const FName& name);
		bool operator==(const ANSICHAR* name);
		bool operator==(const WIDECHAR* name);
		bool operator!=(const FName& name) const;

		template<typename charType>
		bool operator!=(const charType* other);

	private:
		uint32 m_Size;

		union 
		{
			ANSICHAR m_Chars[NAME_SIZE];
			WIDECHAR m_WChars[NAME_SIZE];
		};

	public:
		uint64 operator()(const FName& n) const;
	};

	template<typename charType>
	bool FName::operator!=(const charType* other)
	{

	}

}