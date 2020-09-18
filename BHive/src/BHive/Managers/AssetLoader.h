#pragma once


#include <filesystem>
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Mesh.h"
#include "AssetManagers.h"

namespace BHive
{
	namespace fs = std::filesystem;

	class AssetLoader
	{
	
	public:
		AssetLoader();

		void OpenDirectory(const WinPath& path);
		void LoadFile(const WinPath& path);
		

		std::vector<BString> m_TexExts;
	};

	enum class ESuccess : int
	{
		INPROGRESS,
		FAILED,
		SUCESSS
	};


	template<typename T>
	inline ESuccess OnImport(const WinPath& path)
	{
		Ref<T> obj = T::Create(path);
		AssetManager::Add(obj);
		if (!obj) return  ESuccess::FAILED;
		return ESuccess::SUCESSS;
	}
	
	inline void Import(const WinPath& path)
	{
		static std::vector<BString> texExts = {"jpg", "png", "tga"};
		BString ext = path.GetExtension();
		auto& it = std::find(texExts.begin(), texExts.end(), ext);

		if (ext == "glsl")
		{
			OnImport<Shader>(path);
		}
		else if (it != texExts.end())
		{
			OnImport<Texture2D>(path);
		}
		else if (Model::IsExtensionSupported(ext))
		{
			OnImport<Model>(path);
		}
	}

}