#pragma once

#include "BHive/Core/Layer.h"

namespace BHive
{
	class TextureEditorLayer : public Layer
	{
	public:
		TextureEditorLayer();

		static Ref<Texture2D> TextureToEdit;
		
		void OnImGuiRender() override;
		static void ShowEditor(Ref<Texture2D> texture);
		static void CloseEditor();
		void DisplayTextureEditor();

	private:
		static bool m_ShowEditor;
	};
}