#include "BHivePCH.h"
#include "TextureEditorCustomizationDetails.h"

namespace BHive
{
	void TextureEditorCustomizationDetails::CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder, IAssetType* _asset)
	{
		Texture2D* asset = (Texture2D*)_asset;

		ImGui::Columns(2, "Columns");

		ImVec2 availableSize = ImGui::GetContentRegionAvail();
		float ImageSize = MathLibrary::Min(availableSize.x, availableSize.y);

		detailsBuilder.Image(asset, ImageSize);

		ImGui::NextColumn();

		//Info panel
		ImGui::BeginChild("##Info", ImVec2(0, 100), true);
		ImGui::Text("Size: %dx%d", asset->GetWidth(), asset->GetWidth());
		std::string hasAlpha = asset->HasAlphaChannel() ? "true" : "false";
		ImGui::Text("Has Alpha Channel: %s", hasAlpha.c_str());
		ImGui::EndChild();

		bool changed = false;
		//Editor panel
		ImGui::BeginChild("##Properties", ImVec2(0, 0), true);

		changed |= detailsBuilder.EnumProperty<TilingMethod, 5>("Tiling", s_TilingMethods, asset->m_TilingMethod);
		changed |= detailsBuilder.EnumProperty<MinColorMethod, 6>("Min-Filter", s_Min_ColorMethods, asset->m_MinFilterColorMethod);
		changed |= detailsBuilder.EnumProperty<MagColorMethod, 2>("Mag-Filter", s_Mag_ColorMethods, asset->m_MagFilterColorMethod);
		changed |= detailsBuilder.Color4Property("Border Color", asset->m_BorderColor);

		if (changed)
		{
			asset->InValidate();
		}

		ImGui::EndChild();
	}
}