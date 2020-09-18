#pragma once

#include "BHivePCH.h"
#include "BHive/Renderer/Asset.h"
#include "BHive/Renderer/Texture.h"

namespace BHive
{
	
	template<class T = Asset>
	using Assets = std::unordered_map<std::string, Ref<T>>;

	template<class T = Asset>
	class AssetList
	{
		
	public:
		static Assets<T> s_Assets;

		friend class AssetManager;
	};

	template<class T>
	Assets<T> AssetList<T>::s_Assets;

	class AssetManager
	{
	private:
		AssetManager();

	public:
		template<class T = Asset>
		static Ref<T> Get(const std::string& name);

		template<class T= Asset>
		static void CreateAsset(Ref<T> asset);

		template<class T = Asset>
		static void Add(Ref<T> asset);

		template<class T = Asset>
		static void Remove(const std::string& name);

		template<class T = Asset>
		static bool Exists(const std::string& name);

		template<class T = Asset>
		static Assets<T> GetAssets();
	};

	template<class T>
	Ref<T> AssetManager::Get(const std::string& name)
	{
		if(Exists<T>(name) )
			return AssetList<T>::s_Assets[name];
		else
			return nullptr;
	}

	template<class T>
	bool AssetManager::Exists(const std::string& name)
	{
		return AssetList<T>::s_Assets.find(name) != AssetList<T>::s_Assets.end()
		&& AssetList<Asset>::s_Assets.find(name) != AssetList<Asset>::s_Assets.end();
	}

	template<class T>
	void AssetManager::CreateAsset(Ref<T> asset)
	{
		std::string& name = asset->GetName();
		if (Exists<T>(name)) BH_CORE_ERROR("Asset with name already exists");
		AssetList<T>::s_Assets.insert({ name, asset });
		AssetList<Asset>::s_Assets.insert({name, asset});
	}

	template<class T>
	void AssetManager::Add(Ref<T> asset)
	{
		std::string& name = asset->GetName();
		if (!Exists<T>(name))
		{
			AssetList<T>::s_Assets.insert({ name, asset });
			AssetList<Asset>::s_Assets.insert({ name, asset });
		}
	}

	template<class T>
	void AssetManager::Remove(const std::string& name)
	{
		if (Exists<T>(name))
		{
			AssetList<T>::s_Assets.erase(name);
			AssetList<Asset>::s_Assets.erase(name);
		}
	}

	template<class T>
	Assets<T> AssetManager::GetAssets()
	{
		return AssetList<T>::s_Assets;
	}
}