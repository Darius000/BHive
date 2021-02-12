#pragma once

#include "Assets/Asset.h"
#include "imgui.h"


namespace BHive
{
	struct FontCharacter
	{
		Ref<class Texture2D> m_Texture; //id of glyph texture
		IVector2 m_Size; //size of glyph
		IVector2 m_Bearing; //offset form baseline to left-top of glyph
		uint32 m_Advance; //offset to advance to next glyph
	};

	class Font : public IAssetType
	{
		DEFINE_ASSET_BODY(Font, "Font")

	public:
		Font();
		Font(ImFont* font);

		static Ref<Font> Create(const WinPath& path);

		ImFont* m_Font;

		std::map<ANSICHAR, FontCharacter> m_Characters;

		static bool IsExtensionSupported(const std::string& ext);

	private:
		static std::vector<std::string> s_SupportedExtensions;
		static float s_DefaultSize;
	};
}