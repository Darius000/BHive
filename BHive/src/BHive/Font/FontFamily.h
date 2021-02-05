#pragma once

#include "FontAttributes.h"

namespace BHive
{
	class FontFamily : public IAssetType
	{
		DEFINE_ASSET_BODY(FontFamily, "FontFamily")

	public:
		FontFamily() = default;
		FontFamily(const FontFamily& font);
		~FontFamily() = default;

		using Fonts = std::unordered_map<std::string, FontAttributes>;
		
		void AddFontToFamily(const std::string& name, const WinPath& file);
		void ReplaceFont(const std::string& name, const WinPath& filepath);
		void RemoveFromFamily(const std::string& name);
		void RenameFont(const std::string& name, const std::string& newname);
		void Resize(float size);
		//Call after changing size
		void Resize();
		//const Fonts& GetFonts() const { return m_Fonts; }
		Fonts& GetFonts() { return m_Fonts;}

	private:
		bool DoesFontExist(const std::string& name);
		Ref<Font> LoadFont(const WinPath& file, float size);

	private:
		Fonts m_Fonts;
		float m_Size = 18.0f;

		friend class FontEditorCustomizationDetails;
	};
}