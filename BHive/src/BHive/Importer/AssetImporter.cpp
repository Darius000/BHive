#include "BHivePCH.h"
#include "BHive/Managers/AssetManagers.h"
#include "AssetImporter.h"
#include "BHive/Renderer/Shader.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Model/Model.h"
#include "Font/Font.h"
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
		ImportInternal(path);
	}

	void AssetImporter::ImportInternal(const WinPath& path)
	{
		const BString ext = path.GetExtension();
		Ref<IAssetType> assetRef = nullptr;

		if (Shader::IsExtensionSupported(ext))
		{
			OnImport<Shader>(path, assetRef);
		}
		else if (Texture::IsExtensionSupported(ext))
		{
			OnImport<Texture2D>(path, assetRef);
		}
		else if (Model::IsExtensionSupported(ext))
		{
			OnImport<Model>(path, assetRef);
		}
		else if(Font::IsExtensionSupported(ext))
		{
			OnImport<Font>(path, assetRef);
		}

		if (s_ImportStatus == ESuccess::Sucess)
		{
			
			AssetManager::Add(path.GetName(), assetRef);

			BH_CORE_INFO("Successfully Imported {0}", path.GetName());			
		}
		else
		{
			BH_CORE_ERROR("Asset failed to import from {0}", path.c_str());
		}

		s_ImportStatus = ESuccess::None;
	}

	ESuccess AssetImporter::s_ImportStatus;
}