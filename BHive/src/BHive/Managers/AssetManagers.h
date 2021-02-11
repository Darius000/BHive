#pragma once

#include "BHivePCH.h"
#include "Assets/Asset.h"


namespace BHive
{
	
	//template<class T = IAssetType>
	using Assets = std::unordered_map<std::string, Ref<IAssetType>>;

	//template<class T = IAssetType>
	class AssetList
	{
		
	public:
		static Assets s_Assets;

		friend class AssetManager;
	};


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

		template<typename T>
		static Assets GetAssetsOfType();

		//template<class T = IAssetType>
		static Assets GetAssets();
	};

	template<class T>
	Ref<T> AssetManager::Get(const std::string& name)
	{
		BH_CORE_ASSERT(Exists<T>(name), "Asset doesn't exist");

		return CastPointer<T>(AssetList::s_Assets[name]);
	}

	template<class T>
	bool AssetManager::Exists(const std::string& name)
	{
		if (AssetList::s_Assets.find(name) != AssetList::s_Assets.end())
		{
			if(Cast<T>(AssetList::s_Assets[name].get()))
			{ 
				return true;
			}

			return true;
		}
			
		return false;
	}

	template<class T, typename... Args>
	Ref<T> AssetManager::CreateAsset(const std::string& name, Args&& ... args)
	{
		Ref<T> asset = Make_Ref<T>(std::forward<Args>(args)...);
		asset->SetName(name);
		if (Exists<T>(name)) BH_CORE_ERROR("Asset with name already exists");
		AssetList::s_Assets.insert({ name, asset });
		return asset;
	}

	template<class T>
	void AssetManager::Add(const std::string& name, Ref<T> asset)
	{
		asset->SetName(name);
		if (!Exists<T>(name))
		{
			AssetList::s_Assets.insert({ name, asset });
		}
	}

	template<class T>
	void AssetManager::Remove(const std::string& name)
	{
		if (Exists<T>(name))
		{
			AssetList::s_Assets.erase(name);
		}
	}

	template<typename T>
	Assets AssetManager::GetAssetsOfType()
	{
		Assets assets;
		
		for (auto asset : AssetList::s_Assets)
		{
			if (CastPointer<T>(asset.second))
			{
				assets.emplace(asset.first, asset.second);
			}
		}

		return assets;
	}
}