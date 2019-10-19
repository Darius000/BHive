#include "BHivePCH.h"
#include "Serializable.h"
#include <filesystem>

namespace BHive
{
	ISerializable::ISerializable()
		:m_FilePath(""), m_FileName("")
	{

	}

	void ISerializable::Serialize()
	{
		bool exists = FileExists();
		if (!exists)
		{
			std::ofstream file;
			file.open(*GetSaveFilePath(), std::ofstream::binary | std::ofstream::out);
			OnSave(file, GetFilePath());
			file.close();
		}
		else
		{
			std::ifstream file;
			file.open(*GetSaveFilePath(), std::ifstream::binary | std::ifstream::in);
			OnLoad(file);
			file.close();
		}
	}

	void ISerializable::DeleteResourceFile()
	{
		if (FileExists())
		{
			std::filesystem::remove(*m_FilePath);
		}
	}

	FString ISerializable::GetFileName() const
	{
		return m_FileName;
	}

	FString ISerializable::GetFilePath() const
	{
		return m_FilePath;
	}

	FString ISerializable::GetSaveFilePath()
	{
		return FString("Data\\") + GetFileName() + ".bh";
	}

	void ISerializable::SetFilePath(const FString& resourceFilePath)
	{
		m_FilePath = resourceFilePath;
	}

	void ISerializable::SetFileName(const FString& resourceFileName)
	{
		m_FileName = resourceFileName;
	}

	bool ISerializable::FileExists()
	{
		return std::filesystem::exists(*GetSaveFilePath());
	}
}