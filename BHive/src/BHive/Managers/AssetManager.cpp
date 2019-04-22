#include "BHivePCH.h"
#include "AssetManager.h"


namespace BHive
{
	void AssetManager::OnConstruction()
	{
		mEngineTreeGraph = std::make_unique<DirectoryTreeGraph>("Resources\\Engine");
		mEngineTreeGraph->OnFileEvent.AddBinding(BIND_EVENT_THREE_PARAM(&AssetManager::OnLoadAsset));
		mEngineTreeGraph->Construct();

		mDirectoryGraph = std::make_unique<DirectoryTreeGraph>(m_ContentDirectory);
		mDirectoryGraph->OnFileEvent.AddBinding(BIND_EVENT_THREE_PARAM(&AssetManager::OnLoadAsset));
		mDirectoryGraph->Construct();	
	}

	void AssetManager::OnLoadAsset(String name, String path, String ext)
	{
		if (ext == ".jpg" || ext == ".png")
		{
			LoadAsset<Texture2D>(name, path);
		}
	}

	Asset* AssetManager::GetAsset(String name)
	{
		return m_Assets[name].get();
	}

	bool AssetManager::DeleteAsset(Asset* asset)
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

