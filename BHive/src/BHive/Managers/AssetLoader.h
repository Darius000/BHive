#pragma once


#include <filesystem>

namespace BHive
{
	namespace fs = std::filesystem;

	class AssetLoader
	{
	
	public:
		AssetLoader();

		void OpenDirectory(const WinPath& path);
		void LoadFile(const WinPath& filename);

		std::vector<BString> m_TexExts;
	};

	

}