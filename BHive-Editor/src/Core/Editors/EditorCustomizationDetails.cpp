#include "EditorCustomizationDetails.h"
#include "imgui.h"
#include "BHive/Renderer/Mesh.h"

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

		if (detailsBuilder.Property<TilingMethod, 5>("Tiling", s_TilingMethods, asset->m_TilingMethod)|
			detailsBuilder.Property<MinColorMethod, 6>("Min-Filter", s_Min_ColorMethods, asset->m_MinFilterColorMethod)|
			detailsBuilder.Property<MagColorMethod, 2>("Mag-Filter", s_Mag_ColorMethods, asset->m_MagFilterColorMethod)|
			detailsBuilder.ColorProperty("Border Color", asset->m_BorderColor))
		{
			asset->InValidate();
		}

		detailsBuilder.Property("Save Location", asset->m_SavedPath);

		if( detailsBuilder.Button("Save"))
		{
			asset->Serialize(asset->m_SavedPath.c_str());
		}
	}

	void MaterialEditorCustomizationDetails::CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder, Asset* _asset)
	{
		Material* material = (Material*)_asset;
		detailsBuilder.Property("Shader", material->m_Shader);

		int i = 0;
		for (auto& uniform : ((Material*)_asset)->GetShaderUniforms())
		{
			ImGui::PushID(i++);
			switch (uniform.m_Type)
			{
			default:
				break;
			case ShaderUniformType::Bool:
				detailsBuilder.Property(uniform.m_DisplayName, *static_cast<bool*>(uniform.m_Value));
				break;
			case ShaderUniformType::Int:
				detailsBuilder.Property(uniform.m_DisplayName, *static_cast<int*>(uniform.m_Value));
				break;
			case ShaderUniformType::Float:
				detailsBuilder.Property(uniform.m_DisplayName, *static_cast<float*>(uniform.m_Value));
				break;
			case ShaderUniformType::Float2:
			case ShaderUniformType::Vec2:
				detailsBuilder.Property(uniform.m_DisplayName, *static_cast<FVector2*>(uniform.m_Value));
				break;
			case ShaderUniformType::Float3:
			case ShaderUniformType::Vec3:
				detailsBuilder.Property(uniform.m_DisplayName, *static_cast<FVector3*>(uniform.m_Value));
				break;
			case ShaderUniformType::Float4:
			case ShaderUniformType::Vec4:
				detailsBuilder.Property(uniform.m_DisplayName, *static_cast<FVector4*>(uniform.m_Value));
				break;
			case ShaderUniformType::Color3:
				detailsBuilder.ColorProperty(uniform.m_DisplayName, *static_cast<LinearColor3*>(uniform.m_Value), ImGuiColorEditFlags_None);
				break;
			case ShaderUniformType::Color4:
				detailsBuilder.ColorProperty(uniform.m_DisplayName, *static_cast<LinearColor4*>(uniform.m_Value), ImGuiColorEditFlags_None);
				break;
			case ShaderUniformType::Sampler:
				detailsBuilder.Property(uniform.m_DisplayName, *static_cast<Ref<Texture2D>*>(uniform.m_Value));
				break;
			}
			ImGui::PopID();
		}
	}

	void MeshEditorCustomizationDetails::CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder, Asset* _asset)
	{
		int i = 0;
		Model* model = (Model*)_asset;
		ImGui::Columns(2);
		size_t numMeshes = model->GetMeshes().size();
		for (auto& mesh : model->GetMeshes())
		{
			ImGui::PushID(i++);			
			detailsBuilder.Label(mesh.second->GetName().c_str());
			detailsBuilder.Property("Material", mesh.second->m_Material);		
			ImGui::PopID();
		}

		ImGui::NextColumn();

		ImVec2 canvassize = ImVec2(400, 400);
		float contentPadding = 10.0f;
		ImVec2 contentSize = ImVec2(canvassize.x - contentPadding, canvassize.y - contentPadding);
		if(ImGui::TreeNode("UVs"))
		{ 
			ImGui::BeginChild("##Uvs", ImVec2(canvassize.x, canvassize.y * (float)numMeshes), true);
			int m = 0;
			for (auto& mesh : model->GetMeshes())
			{
				ImDrawList* drawlist = ImGui::GetWindowDrawList();
			
				float offsetY = (float)((canvassize.x + contentPadding)* m++);
				ImVec2 canvaspos = ImGui::GetCursorScreenPos() + ImVec2(0, offsetY);
			
				drawlist->AddRectFilled(canvaspos, ImVec2(canvaspos.x + contentSize.x, canvaspos.y + contentSize.y), IM_COL32(50, 50, 50, 125));
				drawlist->AddRect(canvaspos, ImVec2(canvaspos.x + contentSize.x, canvaspos.y + contentSize.y), IM_COL32(255, 255, 255, 125));
				drawlist->PushClipRect(canvaspos, ImVec2(canvaspos.x + contentSize.x, canvaspos.y + contentSize.y), true);
				drawlist = ImGui::GetWindowDrawList();
			
				for (const auto& Face : mesh.second->m_Faces)
				{
					size_t numIndices = Face.indices.size();
					for (size_t k = 0; k < numIndices; k+= 3)
					{
						uint32 i0 = Face.indices[k];
						uint32 i1 = Face.indices[(k + 1) % numIndices];
						uint32 i2= Face.indices[(k + 2) % numIndices];

						FVertex& v0 = mesh.second->m_Vertices[i0];
						FVertex& v1 = mesh.second->m_Vertices[i1];
						FVertex& v2 = mesh.second->m_Vertices[i2];

						FVector2& tc0 = v0.m_TexCoord;
						FVector2& tc1 = v1.m_TexCoord;
						FVector2& tc2 = v2.m_TexCoord;

						float x0 = canvaspos.x + (tc0.x) * canvassize.x;
						float y0 = canvaspos.y + (1.0f - tc0.y) * canvassize.y;
						float x1 = canvaspos.x + (tc1.x) * canvassize.x;
						float y1 = canvaspos.y + (1.0f - tc1.y) * canvassize.y;
						float x2 = canvaspos.x + (tc2.x) * canvassize.x;
						float y2 = canvaspos.y + (1.0f - tc2.y) * canvassize.y;

						drawlist->AddTriangle(ImVec2(x0, y0), ImVec2(x1, y1), ImVec2(x2, y2), IM_COL32(255, 255, 255, 255), 2.0f);
					}	
				}
				drawlist->PopClipRect();
			}

			ImGui::EndChild();
			ImGui::TreePop();
		}

		
	}

	void ShaderEditorCustomizationDetails::CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder, Asset* _asset)
	{
		Shader* shader = (Shader*)_asset;
		for (auto& source : shader->m_Sources)
		{
			detailsBuilder.Property(ShaderTypesToString[source.first], &source.second);
			std::string buttonLabel = "Recompile##" + std::string(ShaderTypesToString[source.first]);
			std::string buttonLabel2 = "+##" + std::string(ShaderTypesToString[source.first]);
			std::string popupLabel = "Uniforms##" + std::string(ShaderTypesToString[source.first]);
			if (detailsBuilder.Button(buttonLabel2.c_str()))
			{
				shader->AddAttribute(new UniformAttribute());
			}
			
			ImGui::SameLine();
			if (detailsBuilder.Button(buttonLabel.c_str()))
			{
				shader->Compile();
			}
			
		}	

		for (int i = 0; i < shader->m_UniformAttribues.size(); i++)
		{
			UniformAttribute* uniformattr = shader->m_UniformAttribues[i].get();
			float width = ImGui::GetContentRegionAvailWidth() / 4.0f - 100.0f;
			ImGui::PushID(i);
			ImGui::PushItemWidth(width);
			detailsBuilder.Property("Name", uniformattr->m_Name);
			ImGui::SameLine();
			detailsBuilder.Property<ShaderUniformType, 15>("Type", ShaderUniformTypes, uniformattr->m_Type);
			ImGui::SameLine();
			detailsBuilder.Property("Sampler ID", uniformattr->m_SamplerIndex, 1.0f);
			ImGui::SameLine();
			if (detailsBuilder.Button("-"))
			{
				shader->RemoveAttribute(i);
			}
			ImGui::PopItemWidth();
			ImGui::PopID();
		}
	}

}
