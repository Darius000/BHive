#pragma once

namespace BHive
{
	enum class ENameCase : uint8
	{
		CaseSensitive = 0,
		IgnoreCase
	};

	enum EFindName
	{
		Find, Add
	};

	enum { NAME_SIZE = 1024 };

	struct FNameEntryID
	{
		FNameEntryID() : m_Value(0) {}

		bool operator<(FNameEntryID entry) const { return m_Value < entry.m_Value; }
		bool operator>(FNameEntryID entry) const { return m_Value > entry.m_Value; }
		bool operator==(FNameEntryID entry) const { return m_Value == entry.m_Value; }
		bool operator!=(FNameEntryID entry) const { return m_Value != entry.m_Value; }

		operator int32() const { return (int32)m_Value; }

	private:
		uint32 m_Value;
	};

	struct FNameEntry
	{
		FNameEntryID m_ComparsionID;

		union 
		{
			ANSICHAR AnsiName[NAME_SIZE];
			WIDECHAR WideName[NAME_SIZE];
		};

		FNameEntry(const FNameEntry&) = delete;
		FNameEntry(FNameEntry&&) = delete;
		FNameEntry& operator=(const FNameEntry&) = delete;
		FNameEntry& operator=(FNameEntry&&) = delete;
	};

	class Name
	{
	public:
		Name();
		Name(uint32 len, const ANSICHAR* c);
		Name(uint32 len, const WIDECHAR* wc);
		Name(const ANSICHAR* c);
		Name(const WIDECHAR* wc);
		virtual ~Name() = default;

	public:
		int32 Compare(const Name& other) const;
		uint32 GetSize() const { return m_Size; }
		uint32 GetNumber() const { return m_Number; }
		bool IsEqual(const Name& other, ENameCase nameCase);
		bool IsNone();
		void SetNumber(const int32 newNumber);
		FString ToString() const;
		void ToString(FString& out);
		FNameEntryID GetComparsionIndex() const { return m_ComparsionID; }
	public:

		bool operator==(const Name& name);
		//bool operator==(const ANSICHAR* name);
		//bool operator==(const WIDECHAR* name);
		//bool operator!=(const Name& name) const;

		template<typename charType>
		bool operator!=(const charType* other);

	private:
		uint32 m_Size;
		uint32 m_Number;

		union 
		{
			ANSICHAR m_Chars[NAME_SIZE];
			WIDECHAR m_WChars[NAME_SIZE];
		};

		FNameEntryID m_ComparsionID;

	public:
		bool operator==(const Name& name) const
		{
			return m_ComparsionID == name.m_ComparsionID;
		}
	};

	template<typename charType>
	bool Name::operator!=(const charType* other)
	{
		return false;
	}

	
}

template<>
struct std::hash<BHive::Name>
{
	size_t operator()(const BHive::Name& name) const
	{
		size_t const h1(std::hash<BHive::uint32>{}(name.GetNumber()));
		size_t const h2(std::hash<BHive::uint32>{}(name.GetComparsionIndex()));
		return h1 ^ (h2 << 1);
	}
};