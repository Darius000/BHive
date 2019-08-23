#pragma once

#include "Interface.h"
#include "DataTypes.h"

namespace BHive
{
	class ISerializableInterface : public IInterface
	{
	public:
		virtual std::ofstream& OnSave(std::ofstream& os) const = 0;
		virtual void OnLoad(std::ifstream& fs) = 0;
		virtual String ToString() const = 0;
	};

	class ISerializable
	{
	public:
		ISerializable();
		virtual void OnSave(std::ofstream& resourceFile, const String& resourceFilePath) = 0;
		virtual void OnLoad(std::ifstream& resourceFile) = 0;
		void DeleteResourceFile();
		String GetFileName() const;
		String GetFilePath() const;
		String GetSaveFilePath();
		bool FileExists();
	public:
		void SetFilePath(const String& resourceFilePath);
		void SetFileName(const String& resourceFileName);	
	public:
		void Serialize();
	private:
		String m_FilePath = "";
		String m_FileName = "";
	};	

	inline std::ofstream& operator<<(std::ofstream& os, const ISerializableInterface& interface)
	{
		return interface.OnSave(os);
	}
}