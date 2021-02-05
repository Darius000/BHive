#include "BHivePCH.h"
#include "FontLoader.h"
#include "imgui.h"
#include "Font.h"
#include "Renderer/Texture.h"

namespace BHive
{
	Ref<Font> FontLoader::LoadFont(const WinPath& fontpath, uint32 size)
	{
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
		{
			BH_CORE_ERROR("Could not init FreeType Library!");
		}

		FT_Face face;
		if (FT_New_Face(ft, fontpath.c_str(), 0, &face))
		{
			BH_CORE_ERROR("Could not load font!");

			return nullptr;
		}

		BH_CORE_INFO("Loaded font {0}", fontpath.GetName());

		FT_Set_Pixel_Sizes(face, 0, size);

		Ref<Font> font = Make_Ref<Font>();
		ProcessANSICHARFontCharacters(face, font);
		font->SetName(fontpath.GetName());

		//free freetype resources
		FT_Done_Face(face);
		FT_Done_FreeType(ft);

		return font;
	}

	void FontLoader::ProcessANSICHARFontCharacters( FT_Face face, Ref<class Font>& font)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte alignment restriction

		for (uint32 c = 0; c < 128; c++)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				BH_CORE_ERROR("Error::Freetype: failed to load glyph");
				continue;
			}

			//generate tetxure
			font->m_Characters.insert({c, GenerateGlyph(face)});
		}		
	}

	struct FontCharacter FontLoader::GenerateGlyph(FT_Face face)
	{
		uint32 width = face->glyph->bitmap.width;
		uint32 rows = face->glyph->bitmap.rows;
		uint8* buffer = face->glyph->bitmap.buffer;
		uint32 left = face->glyph->bitmap_left;
		uint32 top = face->glyph->bitmap_top;
		uint32 advance = static_cast<uint32>(face->glyph->advance.x);

		Ref<Texture2D> texture = Texture2D::Create(width, rows, GL_R8, GL_RED, buffer);
		texture->SetParameters(TilingMethod::ClampToEdge, MinColorMethod::Linear, MagColorMethod::Linear);

		/*uint32 texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width,
		rows, 0, GL_RED, GL_UNSIGNED_BYTE, buffer);

		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);*/

		return {texture, IVector2(width, rows), IVector2(left, top), advance};
	}

}