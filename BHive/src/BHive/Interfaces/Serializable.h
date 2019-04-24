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
		virtual void OnImport(std::ifstream& file) = 0;
		void Serialize(String fileName);

	public:

		String mName;

	private:
		int mInstanceIndex;

	public:
		static std::vector<ISerializable*> mSerializables;
		static int mNumInstances;
	};	
}