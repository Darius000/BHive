#include "BHivePCH.h"
#include "Name.h"

namespace BHive
{
	template<typename charType>
	Name<charType>::Name()
		:Name(NAME_None)
	{

	}

	template<typename charType>
	Name<charType>::Name(const charType* c, ENameSearch searchCase)
		:m_Characters(nullptr), m_ComparsionID(s_IDGenerator.GenerateID())
	{
		uint32 size = CharacterArrayHelper::GetCharArraySize(c);
		uint32 nameSize = NAME_SIZE;

		BH_CORE_ASSERT(!(size > nameSize), "Name longer than acceptable size of 1024 characters");

		m_Characters = new char[NAME_SIZE];

		CharacterArrayHelper::CopyCharacters(m_Characters, c);
		
		if (m_Characters != NAME_None)
		{
			switch (searchCase)
			{
			case ENameSearch::NAME_Add:
				break;
			case ENameSearch::NAME_Find:
				break;
			}
		}

		//Check what this generates
		BH_CORE_TRACE("{0}", m_Characters);
	}

	template<typename charType>
	Name<charType>::Name(const Name<charType>& other)
	{
		m_Characters = new char[NAME_SIZE];
		CharacterArrayHelper::CopyCharacters(m_Characters, other.m_Characters);
		m_ComparsionID = s_IDGenerator.GenerateID();
	}

	template<typename charType>
	Name<charType>::~Name()
	{
		s_IDGenerator.DeleteID(m_ComparsionID);

		delete[] m_Characters;
	}

	template<typename charType>
	void Name<charType>::FromString(const String<charType>& other)
	{
		CharacterArrayHelper::CopyCharacters(m_Characters, other.m_Characters);
	}

	template<typename charType>
	bool Name<charType>::operator>(const Name<charType>& other)
	{
		return GetComparsionIndex() > other.GetComparsionIndex();
	}

	template<typename charType>
	bool Name<charType>::operator<(const Name<charType>& other)
	{
		return GetComparsionIndex() < other.GetComparsionIndex();
	}

	template<typename charType>
	const charType* Name<charType>::operator*() const
	{
		return m_Characters;
	}


	template<typename charType>
	IDGenerator Name<charType>::s_IDGenerator;
}

