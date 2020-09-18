#pragma once

#include "BHive.h"
#include "BHive/Renderer/Texture.h"
#include "Editor.h"

namespace BHive
{
	
	class TextureEditor : public Editor<Texture2D>
	{
	public:
		TextureEditor(Texture2D* asset)
		:Editor<Texture2D>(asset->GetName().c_str(), asset){}

		void OnImGuiRender() override;
	};
}