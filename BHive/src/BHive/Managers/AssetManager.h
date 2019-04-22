#pragma once

#include "Core.h"
#include "Singleton.h"
#include "Assets/Asset.h"
#include "Assets/Texture2D.h"
#include "Assets/Mesh.h"
#include "Assets/Shader.h"
#include "DataStructures/DirectoryGraph.h"

namespace BHive
{
	class AssetManager : public Singleton<AssetManager>
	{
		
	private:

		String m_ContentDirectory = "Content";
		std::unordered_map<String, std::unique_ptr<Asset>> m_Assets;

	public:
		std::unique_ptr<DirectoryTreeGraph> mDirectoryGraph;
		std::unique_ptr<DirectoryTreeGraph> mEngineTreeGraph;
		Asset* mSelectedAsset;

		virtual void OnConstruction() override;

		Asset* GetAsset(String name);
		bool DeleteAsset(Asset* asset);

		template<typename T>
		void LoadAsset(String name, String path);

	private:
		void OnLoadAsset(String name, String path, String ext);
	};	

	template<typename T>
	void AssetManager::LoadAsset(String name, String path)
	{
		std::unique_ptr<T> asset = std::make_unique<T>();

		asset->SetPath(path);

		//ISerializable::Serialize("text.txt" , *asset.get());

		asset->Load(name, path);

		m_Assets.emplace(std::make_pair(name, std::move(asset))); //move ptr to map
	}

}