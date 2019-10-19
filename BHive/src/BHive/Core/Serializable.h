#pragma once

#include "Interface.h"

namespace BHive
{
	class ISerializableInterface : public IInterface
	{
	public:
		virtual std::ofstream& OnSave(std::ofstream& os) const = 0;
		virtual void OnLoad(std::ifstream& fs) = 0;
		virtual FString ToString() const = 0;
	};

	class ISerializable
	{
	public:
		ISerializable();
		virtual void OnSave(std::ofstream& resourceFile, const FString& resourceFilePath) = 0;
		virtual void OnLoad(std::ifstream& resourceFile) = 0;
		void DeleteResourceFile();
		FString GetFileName() const;
		FString GetFilePath() const;
		FString GetSaveFilePath();
		bool FileExists();
	public:
		void SetFilePath(const FString& resourceFilePath);
		void SetFileName(const FString& resourceFileName);	
	public:
		void Serialize();
	private:
		FString m_FilePath = "";
		FString m_FileName = "";
	};	

	inline std::ofstream& operator<<(std::ofstream& os, const ISerializableInterface& interface)
	{
		return interface.OnSave(os);
	}
}