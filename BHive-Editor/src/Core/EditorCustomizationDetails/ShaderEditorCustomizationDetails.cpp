#include "BHivePCH.h"
#include "ShaderEditorCustomizationDetails.h"

namespace BHive
{
	void ShaderEditorCustomizationDetails::CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder, IAssetType* _asset)
	{
		Shader* shader = (Shader*)_asset;

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save"))
				{
					Serialize(shader, "Assets/" + shader->m_Name);
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		for (auto& source : shader->m_Sources)
		{
			detailsBuilder.MultiStringProperty(ShaderTypesToString[source.first], source.second, FVector2(1000.0f, 300.0f));
			std::string buttonLabel = "Recompile##" + std::string(ShaderTypesToString[source.first]);

			if (detailsBuilder.Button(buttonLabel.c_str()))
			{
				shader->Compile();
			}
		}
	}
}