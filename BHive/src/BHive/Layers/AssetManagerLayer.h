#pragma once

#include "Layer.h"
#include "BResourceManager.h"
#include "BHive/Assets/Texture.h"

namespace BHive
{
	class AssetManagerLayer : public Layer
	{
	public:
		AssetManagerLayer(BResourceManager& resourceManager);
		void OnAttach() override;
		void OnImGuiRender() override;
		bool BeginContextMenu(const String& id);
		void CreateObjectContextMenu(class Object& object);
		void CreateAssetContextMenu();
		void EndContextMenu();
		void AssetMenuBar();

	private:
		BResourceManager& mAssetmanager;
		BResource* mFolderImage;
		BResource* mBackImage;
	};
}

