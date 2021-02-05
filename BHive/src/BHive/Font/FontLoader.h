#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

namespace BHive
{
	

	class FontLoader
	{
	public:
		static Ref<class Font> LoadFont(const WinPath& font, uint32 size = 12);

	private:
		static void ProcessANSICHARFontCharacters(FT_Face face, Ref<class Font>& font);
		static struct FontCharacter GenerateGlyph(FT_Face face);
	};
}
