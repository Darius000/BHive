#pragma once

#include "Core.h"
#include "DataStructures/DirectoryGraph.h"
#include <commdlg.h>

namespace BHive
{
	class BResource;
	class Texture;
	class Mesh;
	class Shader;
	class Texture2D;

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

	class BResourceManager
	{
	public:
		BResourceManager();

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

		template<typename T>
		void LoadResource(const String& name, const String& path);

	private:
		
		void OnLoadAsset(String name, String path, String ext);
		FileImportInfo OpenFileDialog(wchar_t *filter = L"All Files (*.*)\0*.*\0", HWND owner = NULL);
	};	
}

#include "BResourceManager.inl"