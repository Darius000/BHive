#pragma once


namespace BHive
{
	class IDGenerator
	{
	public:
		IDGenerator();
		uint64 GenerateID();
		void DeleteID(uint64 id);

	private:
		uint64 m_NextAvailableUndeletedID;
		std::vector<uint64> m_AvailableDeletedIDs;
	};
}