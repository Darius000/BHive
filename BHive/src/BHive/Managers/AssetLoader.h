#pragma once


#include <filesystem>
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Model.h"
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

	static void LoadingBar(int32* success)
	{
		float progress = 0.0f;

		while (*success == (int32)ESuccess::INPROGRESS)
		{
			BH_CORE_TRACE("Progress {0}", progress);

			progress += .01f;
		}
	
		BH_CORE_TRACE("Complete!");
	}

	template<typename T>
	inline ESuccess OnImport(const WinPath& path)
	{
		ESuccess success = ESuccess::INPROGRESS;
		int32* Progess = &(int32)success;
		//std::future<void> BeginLoading = std::async(std::launch::async, LoadingBar, Progess);

		Ref<T> obj = T::Create(path);	
		if (!obj) success = ESuccess::FAILED;

		success = ESuccess::SUCESSS;

		//Add to asset manager if successful
		if (success == ESuccess::SUCESSS)
		{
			AssetManager::Add(path.GetName(), obj);
		}

		return success;
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