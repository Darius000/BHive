#pragma once

namespace BHive
{
	class ISerializable
	{
	protected:
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
		String m_FilePath;
		String m_FileName;
	};	
}