#include "BHivePCH.h"
#include "MaterialEditorCustomizationDetails.h"

namespace BHive
{
	void MaterialEditorCustomizationDetails::CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder, IAssetType* _asset)
	{
		Material* material = (Material*)_asset;
		if (detailsBuilder.AssetProperty("Shader", material->m_Shader))
		{
			material->QueryUniformsFromShader();
		}

		int i = 0;
		for (auto& uniform : ((Material*)_asset)->GetParameters())
		{
			ImGui::PushID(i++);
			uniform.second->OnRenderGui();
			ImGui::PopID();
		}
	}
}