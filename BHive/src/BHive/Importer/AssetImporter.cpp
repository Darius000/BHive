#include "BHivePCH.h"
#include "BHive/Managers/AssetManagers.h"
#include "AssetImporter.h"
#include "BHive/Renderer/Shader.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Model/Model.h"
#include "Managers/AssetManagers.h"

namespace BHive
{
	AssetImporter::AssetImporter()
	{

	}

	void AssetImporter::ImportDirectoryContents(const WinPath& path)
	{
		auto& it = fs::directory_iterator(*path);
		if (it->exists())
		{
			for (auto& sub : it)
			{
				WinPath subPath(sub.path().string().c_str());
				subPath.IsDirectory() ? ImportDirectoryContents(subPath) : Import(subPath);
			}

			return;
		}

		BH_CORE_ERROR("Directory doesn't exist!");
	}

	void AssetImporter::Import(const WinPath& path)
	{
		const BString ext = path.GetExtension();
		ESuccess importstatus = ESuccess::InProgress;
		Ref<IAssetType> assetRef = nullptr;
		bool importSuccessful = false;

		if (Shader::IsExtensionSupported(ext))
		{
			importSuccessful = OnImport<Shader>(path, assetRef, importstatus);
		}
		else if (Texture::IsExtensionSupported(ext))
		{
			importSuccessful = OnImport<Texture2D>(path, assetRef, importstatus);
		}
		else if (Model::IsExtensionSupported(ext))
		{
			importSuccessful = OnImport<Model>(path, assetRef, importstatus);
		}

		if (importSuccessful)
		{
			AssetManager::Add(path.GetName(), assetRef);

			return;
		}

		BH_CORE_ERROR("Asset failed to import from {0}", path.c_str());
	}
}