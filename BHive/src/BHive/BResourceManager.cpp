#include "BHivePCH.h"
#include "BResourceManager.h"


namespace BHive
{
	void BResourceManager::OnConstruction()
	{
		mEngineTreeGraph = std::make_unique<DirectoryTreeGraph>("Resources\\Engine");
		mEngineTreeGraph->OnFileEvent.AddBinding(BIND_EVENT_THREE_PARAM(&BResourceManager::OnLoadAsset));
		mEngineTreeGraph->Construct();

		mDirectoryGraph = std::make_unique<DirectoryTreeGraph>(m_ContentDirectory);
		mDirectoryGraph->OnFileEvent.AddBinding(BIND_EVENT_THREE_PARAM(&BResourceManager::OnLoadAsset));
		mDirectoryGraph->Construct();	
	}

	void BResourceManager::OnLoadAsset(String name, String path, String ext)
	{
		if (ext == ".jpg" || ext == ".png")
		{
			LoadAsset<Texture2D>(name, path);
		}
	}

	BResource* BResourceManager::GetAsset(String name)
	{
		return m_Assets[name].get();
	}

	bool BResourceManager::DeleteAsset(BResource* asset)
	{
		int error = std::remove(asset->GetPath().c_str());

		if (error == 0)
		{
			asset->Destroy();

			return true;
		}

		return false;
	}

	
}

