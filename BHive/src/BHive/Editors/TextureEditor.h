#pragma once

#include "AssetEditor.h"

namespace BHive
{
	class TextureEditor : public AssetEditor
	{
	public:
		TextureEditor(Asset& asset, String editorName);
	public:
		void OnImGuiRender() override;
	};
}