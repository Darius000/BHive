#include "BHivePCH.h"
#include "IDGenerator.h"

namespace BHive
{
	IDGenerator::IDGenerator()
		:m_NextAvailableUndeletedID(0)
	{

	}

	uint32 IDGenerator::GenerateID()
	{
		uint32 id = -1;

		if (m_AvailableDeletedIDs.size() > 0)
		{
			id = m_AvailableDeletedIDs[0];
			auto& begin = m_AvailableDeletedIDs.begin();
			m_AvailableDeletedIDs.erase(begin);
			return id;
		}

		id = m_NextAvailableUndeletedID;
		m_NextAvailableUndeletedID++;
		return id;
	}

	void IDGenerator::DeleteID(uint32 id)
	{
		m_AvailableDeletedIDs.emplace_back(id);
	}
}