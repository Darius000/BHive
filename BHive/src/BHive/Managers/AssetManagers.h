#pragma once

#include "BHivePCH.h"
#include "BHive/Renderer/Texture.h"

namespace BHive
{
	template<class assetType>
	class AssetManager
	{
	private:
		AssetManager();

	public:
		static Ref<assetType> Get(const std::string& name);

		static void CreateAsset(const std::string& AssetName, Ref<assetType> Asset);

		static void Add(const std::string& AssetName, Ref<assetType> Asset);

		static void Remove(const std::string& name);

		static bool Exists(const std::string& name);

		static std::unordered_map<std::string, Ref<assetType>> GetAssets();

		static std::vector<std::string> GetNames();

		static void PrintAssetNames();

	private:
		static std::unordered_map<std::string, Ref<assetType>> s_Assets;
		static std::vector<std::string> s_Names;
	};

	template<class assetType>
	std::vector<std::string> AssetManager<assetType>::GetNames()
	{
		return s_Names;
	}

	template<class assetType>
	bool AssetManager<assetType>::Exists(const std::string& name)
	{
		return s_Assets.find(name) != s_Assets.end();
	}

	template<class assetType>
	void AssetManager<assetType>::CreateAsset(const std::string& AssetName, Ref<assetType> Asset)
	{
		if(Exists(AssetName)) BH_CORE_ERROR("Asset with name already exists");
		s_Assets.insert({AssetName, Asset});
		s_Names.push_back(AssetName);
	}

	template<class assetType>
	AssetManager<assetType>::AssetManager()
	{

	}

	template<class assetType>
	Ref<assetType> AssetManager<assetType>::Get(const std::string& name)
	{
		return Exists(name) ? s_Assets[name] : nullptr;
	}

	template<class assetType>
	void AssetManager<assetType>::Add(const std::string& AssetName, Ref<assetType> Asset)
	{
		if(!Exists(AssetName)) 
		{
			s_Assets.insert({ AssetName, Asset });
			s_Names.push_back(AssetName);
		}
	}

	template<class assetType>
	void AssetManager<assetType>::Remove(const std::string& name)
	{
		if(Exists(name)) 
		{
			s_Assets.erase(name);
			s_Names.erase(name);
		}
	}

	template<class assetType>
	std::unordered_map<BName, Ref<assetType>> BHive::AssetManager<assetType>::GetAssets()
	{
		return s_Assets;
	}

	template<class assetType>
	void AssetManager<assetType>::PrintAssetNames()
	{
		for (auto Asset : s_Assets)
		{
			BH_CORE_INFO("{0}", Asset.first);
		}
	}

	template<class assetType>
	std::unordered_map<std::string, Ref<assetType>> AssetManager<assetType>::s_Assets;

	template<class assetType>
	std::vector<std::string> AssetManager<assetType>::s_Names;

	class TextureManager : public AssetManager<Texture2D>
	{
	public:

	};
	
	
}