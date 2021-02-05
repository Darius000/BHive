#include "BHivePCH.h"
#include "MeshEditorCustomizationDetails.h"
#include "BHive/Renderer/Mesh.h"

namespace BHive
{
	void MeshEditorCustomizationDetails::CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder, IAssetType* _asset)
	{
		ImGui::Columns(2, "Columns##MeshEditor");

		ImGui::NextColumn();

		DrawMeshMaterialSelector(detailsBuilder, _asset);

		Model* model = (Model*)_asset;
		DrawModelUvs(model);

	}

	void MeshEditorCustomizationDetails::CreateMenuBar(PropertyDetailsBuilder& detailsBuilder, IAssetType* asset)
	{
		if (ImGui::BeginMenu("Edit"))
		{
			//UV Display Settings
			detailsBuilder.Label("Settings");
			detailsBuilder.ColorProperty8("Uv Color", m_UvColor);
			detailsBuilder.FloatProperty("Uv Thickness", m_UvThickness, 1.0f, 2.0f, 6.0f, 2.0f);
			detailsBuilder.Vector2Property("Uv Padding",  m_UvPadding, 1.0f, 2.0f, 10.0f, 10.0f);
			detailsBuilder.FloatProperty("Uv Window Size", m_UVCanvasSize, 1.0f, 100.0f, 400.0f, 400.0f);

			ImGui::EndMenu();
		}
	}

	void MeshEditorCustomizationDetails::DrawMeshMaterialSelector(PropertyDetailsBuilder& detailsBuilder, IAssetType* _asset)
	{
		if (ImGui::TreeNode("Materials"))
		{
			auto model = (Model*)_asset;

			size_t numMeshes = model->GetMeshes().size();
			float ProptrColumnSizeHeight = 50.0f * numMeshes;

			//Draw Mesh material drop downs for each mesh in the model
			int i = 0;
			for (auto& mesh : model->GetMeshes())
			{			
				ImGui::BeginChild("Mesh Label", ImVec2(m_UVCanvasSize, ProptrColumnSizeHeight), true);	

				auto& material = mesh.second->m_Material;
				auto& submesh = mesh.second;
				auto id = std::to_string(mesh.first);

				detailsBuilder.AssetProperty(id, material);

				ImGui::EndChild();
			
			}

			ImGui::TreePop();
		}
	}

	void MeshEditorCustomizationDetails::DrawModelUvs(Model* _asset) const
	{
		size_t numMeshes = _asset->GetMeshes().size();

		auto WindowSize = ImVec2(m_UVCanvasSize, m_UVCanvasSize * numMeshes + m_UvPadding.y / 2.0f * numMeshes);

		if (ImGui::TreeNode("UVs"))
		{
			//Set window padding to 0
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			ImGui::BeginChild("##MeshEditor", WindowSize, true);
			for (const auto& mesh : _asset->GetMeshes())
			{
				ImDrawList* drawlist = ImGui::GetWindowDrawList();
				DrawUvCanvas(drawlist, mesh.second, mesh.first, numMeshes);
			}

			//End sub window
			ImGui::EndChild();
			ImGui::PopStyleVar();
			ImGui::TreePop();
		}
	}

	void MeshEditorCustomizationDetails::DrawUvCanvas(ImDrawList* drawlist, const Ref<FMesh>& mesh, uint32 id, size_t  numMeshes) const
	{
		ImVec2 contentSize = ImVec2(m_UVCanvasSize - m_UvPadding.x * 2.0f + 1.0f, m_UVCanvasSize - m_UvPadding.y + 1.0f);

		ImVec2 canvaspos = ImGui::GetCursorScreenPos() + ImVec2(m_UvPadding.x, (contentSize.y * id) + (m_UvPadding.y * (id + 1)));

		//Draw background	
		drawlist->AddRectFilled(canvaspos, ImVec2(canvaspos.x + contentSize.x, canvaspos.y + contentSize.y), IM_COL32(50, 50, 50, 255));

		////Draw Border
		drawlist->AddRect(canvaspos, ImVec2(canvaspos.x + contentSize.x , canvaspos.y + contentSize.y), IM_COL32(255, 255, 255, 255));

		drawlist->PushClipRect(canvaspos, ImVec2(canvaspos.x + contentSize.x, canvaspos.y + contentSize.y), true);

		for (const auto& Face : mesh->m_Faces)
		{
			size_t numIndices = Face.indices.size();
			for (size_t k = 0; k < numIndices; k += 3)
			{
				uint32 i0 = Face.indices[k];
				uint32 i1 = Face.indices[(k + 1) % numIndices];
				uint32 i2 = Face.indices[(k + 2) % numIndices];

				FVertex& v0 = mesh->m_Vertices[i0];
				FVertex& v1 = mesh->m_Vertices[i1];
				FVertex& v2 = mesh->m_Vertices[i2];

				FVector2& tc0 = v0.m_TexCoord;
				FVector2& tc1 = v1.m_TexCoord;
				FVector2& tc2 = v2.m_TexCoord;

				float x0 = canvaspos.x + (tc0.x) * contentSize.x;
				float y0 = canvaspos.y + (1.0f - tc0.y) * contentSize.y;
				float x1 = canvaspos.x + (tc1.x) * contentSize.x;
				float y1 = canvaspos.y + (1.0f - tc1.y) * contentSize.y;
				float x2 = canvaspos.x + (tc2.x) * contentSize.x;
				float y2 = canvaspos.y + (1.0f - tc2.y) * contentSize.y;

				drawlist->AddTriangle(ImVec2(x0, y0), ImVec2(x1, y1), ImVec2(x2, y2), ColorToImCol32(m_UvColor), m_UvThickness);
			}
		}

		drawlist->PopClipRect();
	}


	float MeshEditorCustomizationDetails::m_UVCanvasSize = 400.0f;

	FVector2 MeshEditorCustomizationDetails::m_UvPadding = { 10.0f, 10.0f };

	Color MeshEditorCustomizationDetails::m_UvColor = Color(255, 0, 0, 255);

	float MeshEditorCustomizationDetails::m_UvThickness = 2.0f;
}