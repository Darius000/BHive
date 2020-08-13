#include "BHivePCH.h"
#include "BHive/Managers/AssetManagers.h"
#include "AssetLoader.h"
#include "BHive/Renderer/Shader.h"

namespace BHive
{
	AssetLoader::AssetLoader()
		:m_TexExts({ "jpg", "png", "tga" })
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
				subPath.IsDirectory() ? OpenDirectory(subPath) : LoadFile(subPath);
			}
		}
	}

	void AssetLoader::LoadFile(const WinPath& path)
	{
		//BH_CORE_TRACE("found file: {0}", *filepath);

		BString ext = path.GetExtension();
		auto& it = std::find(m_TexExts.begin(), m_TexExts.end(), ext);

		if (ext == "glsl")
		{
			ShaderLibrary::Load(path);
		}
		else if (it != m_TexExts.end())
		{
			Texture2D::Create(path);
		}
	}
}