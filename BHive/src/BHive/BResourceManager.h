#pragma once

#include "Core.h"
#include "Assets/BResource.h"
#include "Assets/Texture2D.h"
#include "Assets/Mesh.h"
#include "Assets/Shader.h"
#include "DataStructures/DirectoryGraph.h"
#include <commdlg.h>

namespace BHive
{
	struct FileImportInfo;

	class BResourceManager
	{
	public:
		BResourceManager() = default;

	private:

		std::unordered_map<String, std::unique_ptr<BResource>> m_Assets;
	public:
		std::unique_ptr<DirectoryTreeGraph> mDirectoryGraph;
		std::unique_ptr<DirectoryTreeGraph> mEngineTreeGraph;
		BResource* mSelectedAsset;

		void Create(const String& engineDirectory, const String& contentDirectory);
		void ImportAsset(const String& to);

		BResource* GetAsset(String name);
		bool DeleteAsset(BResource* asset);

		template<typename T>
		void LoadAsset(String name, String loadPath);

	private:
		void OnLoadAsset(String name, String path, String ext);
		FileImportInfo OpenFileDialog(wchar_t *filter = L"All Files (*.*)\0*.*\0", HWND owner = NULL);
	};	

	template<typename T>
	void BResourceManager::LoadAsset(String name, String loadPath)
	{
		std::unique_ptr<T> asset = std::make_unique<T>();

		if (asset->Load(name, loadPath))
		{
			m_Assets.emplace(std::make_pair(name, std::move(asset))); 
		}
	}

	struct FileImportInfo
	{
		FileImportInfo(String _name, String _path, String _ext)
			:name(_name), path(_path), ext(_ext)
		{

		}

		String name;
		String path;
		String ext;
	};
}