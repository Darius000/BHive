#pragma once

namespace BHive
{
	class ISerializable
	{
	public:
		ISerializable();
		virtual ~ISerializable();
		virtual void OnSave(std::fstream& file) = 0;
		virtual void OnLoad(std::fstream& file) = 0;
		static void Serialize(String fileName, ISerializable& serializableObject);

	public:
		///Functions to save variables
		///Save an unsigned char to file
		void SaveUnsignedChar(std::fstream& file, unsigned char*& var);

		String mName;

	private:
		int mInstanceIndex;

	public:
		static std::vector<ISerializable*> mSerializables;
		static int mNumInstances;
		static String mSaveDirectory;

		template<typename T>
		void SaveVariable(std::fstream& file, const T& var)
		{
			file.write((char*)(&var), sizeof(var));
		}

		template<typename T>
		void LoadVariable(std::fstream& file, T& var)
		{
			file.read((char*)(var), sizeof(var));
		}
	};	
}