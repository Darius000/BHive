#pragma once

#include "Layer.h"
#include "Managers/AssetManager.h"


namespace BHive
{
	class AssetManagerLayer : public Layer
	{
		void OnAttach() override;

		void OnImGuiRender() override;

		bool BeginContextMenu(const String& id);
		void CreateObjectContextMenu(class Object& object);
		void CreateAssetContextMenu();
		void EndContextMenu();
		void AssetMenuBar();

	private:
		AssetManager* mAssetmanager;
		Asset* mFolderImage;
		Asset* mBackImage;
		DirectoryTreeGraph* mDirectoryTreeGraph;
	};
}