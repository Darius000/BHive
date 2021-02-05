#include "BHivePCH.h"
#include "BHive/Managers/AssetManagers.h"
#include "AssetLoader.h"
#include "BHive/Renderer/Shader.h"

namespace BHive
{
	AssetLoader::AssetLoader()
		:m_TexExts({ "jpg","jpeg", "tga", "png", "tga" })
	{

	}

	void AssetLoader::OpenDirectory(const WinPath& path)
	{
		auto& it = fs::directory_iterator(*path);
		if (it->exists())
		{
			//BH_CORE_TRACE("found directory: {0} ", *path);

			for (auto& sub : it)
			{
				WinPath subPath(sub.path().string().c_str());
				subPath.IsDirectory() ? OpenDirectory(subPath) : Import(subPath);
			}
		}
	}

	void AssetLoader::LoadFile(const WinPath& path)
	{

		BString ext = path.GetExtension();
		auto& it = std::find(m_TexExts.begin(), m_TexExts.end(), ext);

		if (ext == "glsl")
		{
			Ref<Shader> m_Shader = Shader::Create(path);
			AssetManager::Add(path.GetName(), m_Shader);
		}
		else if (it != m_TexExts.end())
		{
			Ref<Texture2D> m_Texutre = Texture2D::Create(path);
			AssetManager::Add(path.GetName(), m_Texutre);
		}
	}
}