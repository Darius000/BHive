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

		
		//for internal use only for importing
		static void ImportInternal(const WinPath& path);

		//Imports an asset fro
		template<typename T>
		static void OnImport(WinPath path, Ref<IAssetType>& asset);

		static void ShowProgressBar();

		static ESuccess s_ImportStatus;
	};

	template<typename T>
	void AssetImporter::OnImport(WinPath path, Ref<IAssetType>& asset)
	{
		s_ImportStatus = ESuccess::InProgress;

		asset = T::Create(path);
		s_ImportStatus = !asset ? ESuccess::Failed : ESuccess::Sucess;
	}
}