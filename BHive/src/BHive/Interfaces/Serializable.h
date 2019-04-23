#pragma once

namespace BHive
{
	class ISerializable
	{
	public:
		ISerializable();
		virtual ~ISerializable();
		virtual void OnSave(std::ofstream& file) = 0;
		virtual void OnLoad(std::ifstream& file) = 0;
		static void Serialize(String fileName, ISerializable& serializableObject);

	public:
		///Functions to save variables
		///Save an unsigned char to file
		//void SaveUnsignedChar(std::fstream& file, unsigned char*& var);

		String mName;

	private:
		int mInstanceIndex;

	public:
		static std::vector<ISerializable*> mSerializables;
		static int mNumInstances;
		static String mSaveDirectory;

		template<typename T>
		void SaveVariable(std::ofstream& file,const T& var)
		{
			//file.write((char*)(&var), sizeof(var));

			//file << *var << std::endl;

			//file.write(&var, sizeof(var));

			//size_t size = sizeof(var);

			//file << var << "\0" <<  std::endl;
		}

		template<typename T>
		void LoadVariable(std::ifstream& file, T& var)
		{
			//file.read((char*)(var), sizeof(var));

			//file >> var;
		}
	};	
}