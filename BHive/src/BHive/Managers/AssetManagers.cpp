#include "BHivePCH.h"
#include "AssetManagers.h"

namespace BHive
{
	AssetManager::AssetManager()
	{

	}

	Assets AssetManager::GetAssets()
	{
		return AssetList::s_Assets;
	}

	Assets AssetList::s_Assets;
}
