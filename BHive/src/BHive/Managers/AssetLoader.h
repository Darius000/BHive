#pragma once


#include <filesystem>

namespace BHive
{
	namespace fs = std::filesystem;

	class AssetLoader
	{
	
	public:
		AssetLoader(const WinPath& path);
		~AssetLoader();

		void OpenDirectory(const WinPath& path);
		void LoadFile(const WinPath& filename);

		std::vector<BString> m_TexExts;
	};

	

}