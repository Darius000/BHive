#include "BHivePCH.h"
#include "Serializable.h"
#include <filesystem>

namespace BHive
{
	ISerializable::ISerializable() :mInstanceIndex(mNumInstances)
	{
		mSerializables.emplace_back(this);
		//BH_INFO("IsSerialized!");
	}

	ISerializable::~ISerializable()
	{
		auto& item = std::find(mSerializables.begin(), mSerializables.end(), this);

		if(item != mSerializables.end())
			mSerializables.erase(item);
	}

	void ISerializable::Serialize(String fileName, ISerializable& serializableObject)
	{
		std::fstream file;

		if (!std::filesystem::exists(fileName))
		{
			file.open(fileName, std::ios::out | std::ios::app);
			serializableObject.OnSave(file);
			file.close();
		}
		else
		{
			
			file.open(fileName, std::ios::in | std::ios::ate);
			serializableObject.OnLoad(file);
			file.close();
		}
	}

	std::vector<ISerializable*> ISerializable::mSerializables;

	int ISerializable::mNumInstances;

	String ISerializable::mSaveDirectory = "";
}