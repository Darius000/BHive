#pragma once


#include <filesystem>


namespace BHive
{
	namespace fs = std::filesystem;

	enum class ESuccess : int
	{
		None,
		InProgress,
		Failed,
		Sucess	
	};

	class AssetImporter
	{
	
	public:
		AssetImporter();

		//go to a specific directory and try to import everything
		static void ImportDirectoryContents(const WinPath& path);

		//imports a new asset with the relative or absolute path
		static void Import(const WinPath& path);

		//Imports an asset fro
		template<typename T>
		static inline bool OnImport(const WinPath& path, Ref<IAssetType>& asset, ESuccess& importStatus);
	};

	template<typename T>
	bool AssetImporter::OnImport(const WinPath& path, Ref<IAssetType>& asset, ESuccess& importStatus)
	{
		importStatus = ESuccess::InProgress;

		asset = T::Create(path);
		importStatus = !asset ? ESuccess::Failed : ESuccess::Sucess;

		return importStatus == ESuccess::Sucess;
	}
}