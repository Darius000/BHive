#pragma once

#include "AssetEditor.h"

namespace BHive
{
	class TextureEditor : public AssetEditor
	{
	public:
		TextureEditor(BResource& asset, FString editorName);
	public:
		void OnImGuiRender() override;
	};
}