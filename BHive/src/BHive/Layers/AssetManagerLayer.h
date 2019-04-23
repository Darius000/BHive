#pragma once

#include "Layer.h"
#include "BResourceManager.h"
#include <commdlg.h>

namespace BHive
{
	class AssetManagerLayer : public Layer
	{
		void OnAttach() override;

		void OnImGuiRender() override;

		bool BeginContextMenu(const String& id);
		void CreateObjectContextMenu(class Object& object);
		void CreateAssetContextMenu();
		void EndContextMenu();
		void AssetMenuBar();

	private:
		BResourceManager* mAssetmanager;
		BResource* mFolderImage;
		BResource* mBackImage;
		DirectoryTreeGraph* mDirectoryTreeGraph;
	};

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

	FileImportInfo OpenFileDialog(wchar_t *filter = L"All Files (*.*)\0*.*\0", HWND owner = NULL);
}

