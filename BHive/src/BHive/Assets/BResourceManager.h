#pragma once

#include "Core.h"
#include "BHive/DataStructures/DirectoryGraph.h"
#include "BHive/Assets/BResource.h"
#include <commdlg.h>

namespace BHive
{
	class BResource;
	//class Texture;
	//class Mesh;
	//class Shader;
	//class Texture2D;

	struct FileImportInfo
	{
		FileImportInfo(FString _name, FString _path, FString _ext)
			:name(_name), path(_path), ext(_ext)
		{

		}

		FString name;
		FString path;
		FString ext;
	};

	class BResourceManager
	{
	public:
		BResourceManager();

	private:

		std::unordered_map<FString, std::unique_ptr<BResource>, FStringHashFunction> m_Assets;

	public:
		std::unique_ptr<DirectoryTreeGraph> mDirectoryGraph;
		std::unique_ptr<DirectoryTreeGraph> mEngineTreeGraph;

		BResource* mSelectedAsset;

		void Create(const FString& engineDirectory, const FString& contentDirectory);
		void ImportAsset(const FString& to);
		
		BResource* GetAsset(FString name);
		bool DeleteAsset(BResource* asset);

		template<typename T>
		void LoadAsset(FString name, FString loadPath)
		{
			std::unique_ptr<T> asset = std::make_unique<T>();
			//asset->SetDisplayName(name);
			//asset->SetFileName(name);
			//asset->SetFilePath(loadPath);
			//asset->Serialize();
			m_Assets.emplace(std::make_pair(name, std::move(asset)));
		}

		template<typename T>
		void LoadResource(const FString & name, const FString & path)
		{
			std::unique_ptr<T> asset = std::make_unique<T>()
			//asset->SetDisplayName(name);
			//asset->SetFileName(name);
			//asset->SetFilePath(path);
			//asset->Serialize();
			m_Assets.emplace(std::make_pair(name, std::move(asset)));
		}

	private:
		
		void OnLoadAsset(FString name, FString path, FString ext);
		FileImportInfo OpenFileDialog(wchar_t *filter = L"All Files (*.*)\0*.*\0", HWND owner = NULL);
	};	
}
