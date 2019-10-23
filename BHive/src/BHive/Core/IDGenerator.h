#pragma once


namespace BHive
{
	class IDGenerator
	{
	public:
		IDGenerator();
		uint32 GenerateID();
		void DeleteID(uint32 id);

	private:
		uint32 m_NextAvailableUndeletedID;
		std::vector<uint32> m_AvailableDeletedIDs;
	};
}