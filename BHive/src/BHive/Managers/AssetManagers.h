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
		static Ref<assetType> Get(const BName& name);

		static void CreateAsset(BName AssetName, Ref<assetType> Asset);

		static void Add(BName AssetName, Ref<assetType> Asset);

		static void Remove(const BName& name);

		static bool Exists(const BName& name);

		static std::unordered_map<BName, Ref<assetType>> GetAssets();

		static void PrintAssetNames();

	private:
		static std::unordered_map<BName, Ref<assetType>> s_Assets;
	};

	template<class assetType>
	bool BHive::AssetManager<assetType>::Exists(const BName& name)
	{
		return s_Assets.find(name) != s_Assets.end();
	}

	template<class assetType>
	void BHive::AssetManager<assetType>::CreateAsset(BName AssetName, Ref<assetType> Asset)
	{
		if(Exists(AssetName)) BH_CORE_ERROR("Asset with name already exists");
		s_Assets.insert({AssetName, Asset});
	}

	template<class assetType>
	BHive::AssetManager<assetType>::AssetManager()
	{

	}

	template<class assetType>
	BHive::Ref<assetType> BHive::AssetManager<assetType>::Get(const BName& name)
	{
		return Exists(name) ? s_Assets[name] : nullptr;
	}

	template<class assetType>
	void BHive::AssetManager<assetType>::Add(BName AssetName, Ref<assetType> Asset)
	{
		if(!Exists(AssetName)) s_Assets.insert({ AssetName, Asset });
	}

	template<class assetType>
	void BHive::AssetManager<assetType>::Remove(const BName& name)
	{
		if(Exists(name)) s_Assets.erase(name);
	}

	template<class assetType>
	std::unordered_map<BName, Ref<assetType>> BHive::AssetManager<assetType>::GetAssets()
	{
		return s_Assets;
	}

	template<class assetType>
	void BHive::AssetManager<assetType>::PrintAssetNames()
	{
		for (auto Asset : s_Assets)
		{
			BH_CORE_INFO("{0}", Asset.first);
		}
	}

	template<class assetType>
	std::unordered_map<BName, Ref<assetType>> AssetManager<assetType>::s_Assets;


	class TextureManager : public AssetManager<Texture2D>
	{
	public:

	};
	
	
}