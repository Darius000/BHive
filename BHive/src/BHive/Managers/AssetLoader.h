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
		if (!obj) return  ESuccess::FAILED;
		AssetManager::Add(obj);
		return ESuccess::SUCESSS;
	}
	
	inline void Import(const WinPath& path)
	{	
		BString ext = path.GetExtension();

		if (ext == "glsl")
		{
			OnImport<Shader>(path);
		}
		else if (Texture::IsExtensionSupported(ext))
		{
			OnImport<Texture2D>(path);
		}
		else if (Model::IsExtensionSupported(ext))
		{
			OnImport<Model>(path);
		}
	}

}