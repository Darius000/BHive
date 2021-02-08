#pragma once

#include <vector>


namespace Serialization
{
	class ISerializable;

	//The save and loading manager for ISerializbale objects
	class Serilializer
	{
	public:
		//Loads all ISerializable objects with this derived class
		static void Load();

		//Saves all ISerializable objects with this derived class
		static void Save();

		static std::vector<ISerializable*> m_Serializables;
	};
}