#include "BHivePCH.h"
#include "EditorCustomizationDetails.h"
#include "imgui.h"

namespace BHive
{
	void TextureEditorCustomizationDetails::CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder, Asset*_asset)
	{
		Texture2D* asset = (Texture2D*)_asset;

		ImGui::Columns(2, "Columns");

		float ImageSize = 512.0f;
		uint32 ID = asset->GetRendererID();
		detailsBuilder.Image(ID, ImageSize);

		ImGui::NextColumn();

		if (detailsBuilder.Combo<TilingMethod, 5>("Tiling", s_TilingMethods, asset->m_TilingMethod)|
			detailsBuilder.Combo<MinColorMethod, 6>("Min-Filter", s_Min_ColorMethods, asset->m_MinFilterColorMethod)|
			detailsBuilder.Combo<MagColorMethod, 2>("Mag-Filter", s_Mag_ColorMethods, asset->m_MagFilterColorMethod)|
			detailsBuilder.Color4Property("Border Color", asset->m_BorderColor))
		{
			asset->InValidate();
		}

		detailsBuilder.StringProperty("Save Location", asset->m_SavedPath);

		if( detailsBuilder.Button("Save"))
		{
			asset->Serialize(asset->m_SavedPath.c_str());
		}
	}
}
