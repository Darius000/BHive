#pragma once

#include "BHivePCH.h"
#include "BHive/Renderer/Texture.h"

namespace BHive
{
	template<class assetType>
	class AssetManager
	{
		using AssetList = std::unordered_map<BName, Ref<assetType>>;

	private:
		AssetManager() {}

	public:
		static Ref<assetType> Get(const BName& name)
		{
			return s_Assets[name];
		}

		static void Add(Ref<assetType>& texture)
		{
			s_Assets[texture->GetName()] = texture;
		}

		static void Remove(const BName& name)
		{
			s_Assets.erase(name);
		}

		static AssetList GetTextures()
		{
			return s_Assets;
		}

	private:
		static AssetList s_Assets;
	};

	template<class assetType>
	std::unordered_map<BName, Ref<assetType>> AssetManager<assetType>::s_Assets;


	class TextureManager : public AssetManager<Texture2D>
	{

	};
	
	
}