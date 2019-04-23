#pragma once

#include "Core.h"
#include "Singleton.h"
#include "Assets/BResource.h"
#include "Assets/Texture2D.h"
#include "Assets/Mesh.h"
#include "Assets/Shader.h"
#include "DataStructures/DirectoryGraph.h"

namespace BHive
{
	class BResourceManager : public Singleton<BResourceManager>
	{
		
	private:

		String m_ContentDirectory = "Content";
		std::unordered_map<String, std::unique_ptr<BResource>> m_Assets;

	public:
		std::unique_ptr<DirectoryTreeGraph> mDirectoryGraph;
		std::unique_ptr<DirectoryTreeGraph> mEngineTreeGraph;
		BResource* mSelectedAsset;

		virtual void OnConstruction() override;

		BResource* GetAsset(String name);
		bool DeleteAsset(BResource* asset);

		template<typename T>
		void LoadAsset(String name, String path);

	private:
		void OnLoadAsset(String name, String path, String ext);
	};	

	template<typename T>
	void BResourceManager::LoadAsset(String name, String path)
	{
		std::unique_ptr<T> asset = std::make_unique<T>();

		if (asset->Load(name, path))
		{
			m_Assets.emplace(std::make_pair(name, std::move(asset))); 
		}
	}

}