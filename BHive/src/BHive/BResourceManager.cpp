#include "BHivePCH.h"
#include "BResourceManager.h"
#include "Assets/BResource.h"
#include "Assets/Texture2D.h"
#include "Assets/Mesh.h"
#include "Assets/Shader.h"

namespace BHive
{

	BResourceManager::BResourceManager() = default;

	void BResourceManager::Create(const String& engineDirectory, const String& contentDirectory)
	{
		mEngineTreeGraph = std::make_unique<DirectoryTreeGraph>(engineDirectory);
		mEngineTreeGraph->OnFileEvent.AddBinding(BIND_EVENT_THREE_PARAMS(&BResourceManager::OnLoadAsset));
		mEngineTreeGraph->Construct();

		mDirectoryGraph = std::make_unique<DirectoryTreeGraph>(contentDirectory);
		mDirectoryGraph->Construct();	
	}

	void BResourceManager::ImportAsset(const String& to)
	{
		FileImportInfo fileInfo = OpenFileDialog();

		OnLoadAsset(fileInfo.name, fileInfo.path, fileInfo.ext);
	}

	void BResourceManager::OnLoadAsset(String name, String path, String ext)
	{
		if (ext == ".jpg" || ext == ".png")
		{
			LoadAsset<Texture>(name, path);
		}
	}

	BResource* BResourceManager::GetAsset(String name)
	{
		return m_Assets[name].get();
	}

	bool BResourceManager::DeleteAsset(BResource* asset)
	{
		/*int error = std::remove(asset->GetPath().c_str());

		if (error == 0)
		{
			asset->Destroy();

			return true;
		}*/

		return false;
	}

	FileImportInfo BResourceManager::OpenFileDialog(wchar_t *filter, HWND owner)
	{
		OPENFILENAME ofn;
		wchar_t name[MAX_PATH] = L"";
		ZeroMemory(&ofn, sizeof(ofn));

		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = owner;
		ofn.lpstrFilter = filter;
		ofn.lpstrFile = name;
		ofn.nMaxFile = MAX_PATH;
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
		ofn.lpstrDefExt = TEXT("");
		ofn.lpstrInitialDir = TEXT("Content\\");


		std::wstring filenameStr;
		String filePath = "";
		String fileName = "";
		String fileExtension = "";

		if (GetOpenFileName(&ofn))
		{
			filenameStr = name;

			filePath = String(filenameStr.begin(), filenameStr.end());
			auto path = std::filesystem::path(filePath);
			fileName = path.filename().string();
			fileExtension = path.extension().string();
		}

		return FileImportInfo(fileName, filePath, fileExtension);
	}
}

