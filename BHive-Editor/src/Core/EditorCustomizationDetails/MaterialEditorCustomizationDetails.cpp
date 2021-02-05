#include "BHivePCH.h"
#include "MaterialEditorCustomizationDetails.h"

namespace BHive
{
	void MaterialEditorCustomizationDetails::CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder, IAssetType* _asset)
	{
		Material* material = (Material*)_asset;
		detailsBuilder.AssetProperty("Shader", material->m_Shader);

		int i = 0;
		for (auto& uniform : ((Material*)_asset)->m_Shader->GetUniforms())
		{
			ImGui::PushID(i++);
			uniform.second->OnRenderGui();
			ImGui::PopID();
		}
	}
}