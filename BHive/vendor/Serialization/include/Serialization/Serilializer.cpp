#include "Serilializer.h"
#include "Archive.h"
#include "Serialize.h"

namespace Serialization
{
	void Serilializer::Load()
	{
		for (auto s : m_Serializables)
		{
			Archive FArchive(s->GetName());
			FArchive >> s;
		}
	}

	void Serilializer::Save()
	{
		for (auto s : m_Serializables)
		{
			Archive FArchive(s->GetName());
			FArchive << s;
		}
	}

	std::vector<ISerializable*> Serilializer::m_Serializables;

}