#include "BHivePCH.h"
#include "Font.h"

namespace BHive
{

	Font::Font(ImFont* font)
	{
		m_Font = font;
	}

	Font::Font()
		:m_Font(nullptr)
	{

	}

	Ref<Font> Font::Create(const WinPath& path)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImFont* font = io.Fonts->AddFontFromFileTTF(path.c_str(), s_DefaultSize);

		return font ? Make_Ref<Font>(font) : nullptr;
	}

	bool Font::IsExtensionSupported(const std::string& ext)
	{
		return std::find(s_SupportedExtensions.begin(), s_SupportedExtensions.end(), ext) !=
			s_SupportedExtensions.end();
	}

	std::vector<std::string> Font::s_SupportedExtensions = { "ttf" };

	float Font::s_DefaultSize = 12.0f;

}