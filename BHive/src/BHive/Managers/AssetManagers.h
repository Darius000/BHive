#pragma once

#include "BHivePCH.h"
#include "Assets/Asset.h"


namespace BHive
{
	
	template<class T = IAssetType>
	using Assets = std::unordered_map<std::string, Ref<T>>;

	template<class T = IAssetType>
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
		template<class T = IAssetType>
		static Ref<T> Get(const std::string& name);

		template<class T= IAssetType, typename... Args>
		static Ref<T> CreateAsset(const std::string& name, Args&& ... args);

		template<class T = IAssetType>
		static void Add(const std::string& name, Ref<T> asset);

		template<class T = IAssetType>
		static void Remove(const std::string& name);

		template<class T = IAssetType>
		static bool Exists(const std::string& name);

		template<class T = IAssetType>
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
		&& AssetList<IAssetType>::s_Assets.find(name) != AssetList<IAssetType>::s_Assets.end();
	}

	template<class T, typename... Args>
	Ref<T> AssetManager::CreateAsset(const std::string& name, Args&& ... args)
	{
		Ref<T> asset = Make_Ref<T>(std::forward<Args>(args)...);
		asset->SetName(name);
		if (Exists<T>(name)) BH_CORE_ERROR("Asset with name already exists");
		AssetList<T>::s_Assets.insert({ name, asset });
		AssetList<IAssetType>::s_Assets.insert({name, asset});
		return asset;
	}

	template<class T>
	void AssetManager::Add(const std::string& name, Ref<T> asset)
	{
		asset->SetName(name);
		if (!Exists<T>(name))
		{
			AssetList<T>::s_Assets.insert({ name, asset });
			AssetList<IAssetType>::s_Assets.insert({ name, asset });
		}
	}

	template<class T>
	void AssetManager::Remove(const std::string& name)
	{
		if (Exists<T>(name))
		{
			AssetList<T>::s_Assets.erase(name);
			AssetList<IAssetType::s_Assets.erase(name);
		}
	}

	template<class T>
	Assets<T> AssetManager::GetAssets()
	{
		return AssetList<T>::s_Assets;
	}
}