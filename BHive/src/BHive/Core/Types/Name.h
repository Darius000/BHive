#pragma once

#include "BHive/Core/IDGenerator.h"

namespace BHive
{
	#define  NAME_None "None"

	enum class ENameCase : uint8
	{
		CaseSensitive = 0,
		IgnoreCase
	};

	enum class ENameSearch : uint8 
	{
		NAME_Find,
		NAME_Add
	};

	enum { NAME_SIZE = 1024 };

	template<typename charType>
	class Name 
	{
	public:
		Name();
		Name(const charType* c, ENameSearch searchCase = ENameSearch::NAME_Add);
		Name(const Name& other);
		~Name();

	public:
		FString ToString() const { return String(m_Characters, m_Size); };
		uint32 GetComparsionIndex() const { return m_ComparsionID; }
		void FromString(const String<charType>& other);

	public:
		
		bool operator>(const Name& other);
		bool operator<(const Name& other);
		Name& operator=(const Name&) = delete;
		const charType* operator*() const;
		
	private:
		uint32 m_ComparsionID;
		charType* m_Characters;

		template<typename>
		friend class String;

		static IDGenerator s_IDGenerator;

	};

	template<typename charType>
	bool operator==(const Name<charType>& a, const Name<charType>& b)
	{
		return a.GetComparsionIndex() == b.GetComparsionIndex();
	}

	typedef Name<ANSICHAR> FName;
	typedef Name<WIDECHAR> WName;
}
	
template<>
struct std::hash<BHive::FName>
{
	size_t operator()(const BHive::FName& name) const
	{
		size_t const h(std::hash<BHive::uint32>{}(name.GetComparsionIndex()));
		return h;
	}
};

template<>
struct std::hash<BHive::WName>
{
	size_t operator()(const BHive::WName& name) const
	{
		size_t const h(std::hash<BHive::uint32>{}(name.GetComparsionIndex()));
		return h;
	}
};

#include "Name.inl"