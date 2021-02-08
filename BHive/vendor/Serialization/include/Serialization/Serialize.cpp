#include "Serialize.h"
#include "Serilializer.h"

namespace Serialization
{ 
	ISerializable::ISerializable()
	{
		Serilializer::m_Serializables.push_back(this);
	}
}
