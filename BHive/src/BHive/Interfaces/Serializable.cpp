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
		if (!std::filesystem::exists(fileName))
		{
			std::ofstream file;
			file.open(fileName, std::ifstream::binary | std::ifstream::out);
			serializableObject.OnSave(file);
			file.close();
		}
		else
		{
			std::ifstream file;
			file.open(fileName, std::ifstream::binary | std::ifstream::in);
			serializableObject.OnLoad(file);
			file.close();
		}
	}

	std::vector<ISerializable*> ISerializable::mSerializables;

	int ISerializable::mNumInstances;

	String ISerializable::mSaveDirectory = "";
}