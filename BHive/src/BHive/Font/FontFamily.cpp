#include "BHivePCH.h"
#include "FontFamily.h"
#include "imgui.h"

namespace BHive
{

	FontFamily::FontFamily(const FontFamily& font)
	{
		m_Fonts = font.m_Fonts;
	}

	void FontFamily::AddFontToFamily(const std::string& name, Ref<Font>& font)
	{
		if(!DoesFontExist(name))
		{ 
			FontAttributes attr = {name, font};
			m_Fonts.insert({name, attr});
			return;
		}

		BH_CORE_WARN("Font name already exist in Family!");
	}

	void FontFamily::ReplaceFont(const std::string& name, const WinPath& filepath)
	{
		if (DoesFontExist(name))
		{
			Ref<Font> font = LoadFont(filepath, m_Size);
			m_Fonts[name].m_Font = font;
			return;
		}
		
		BH_CORE_WARN("Font name doesnt exist in Family!");
	}

	void FontFamily::RemoveFromFamily(const std::string& name)
	{
		if (DoesFontExist(name))
		{
			m_Fonts.erase(name);
			return;
		}

		BH_CORE_WARN("Font name doesnt exist in Family!");
	}

	void FontFamily::RenameFont(const std::string& name, const std::string& newname)
	{
		bool hasFont = DoesFontExist(name);
		bool hasFontWithNewName = DoesFontExist(newname);
		if ( hasFont && !hasFontWithNewName)
		{
			auto nodehandler = m_Fonts.extract(name);
			nodehandler.key() = newname;
			BH_CORE_INFO("{0} in {1} renamed to {2}", name, m_Name, newname);
			return;
		}

		if(hasFont) BH_CORE_WARN("Font name doesnt exist in Family!");
		if(hasFontWithNewName) BH_CORE_WARN("Cannnot rename font to font that already exists");
	}

	bool FontFamily::DoesFontExist(const std::string& name)
	{
		auto font = m_Fonts.find(name);
		return font != m_Fonts.end();
	}

	Ref<Font> FontFamily::LoadFont(const WinPath& file, float size)
	{
		if(file.Empty()) return nullptr;

		m_Size = size;
		
		return Font::Create(file);
	}

}