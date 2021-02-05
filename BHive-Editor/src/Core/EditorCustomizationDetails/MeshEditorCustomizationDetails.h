#pragma once

#include "EditorCustomizationDetails.h"

namespace BHive
{
	class MeshEditorCustomizationDetails : public EditorCustomizationDetails
	{
	public:
		void CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder, IAssetType* _asset) override;

	private:
		//Menu Bar
		void CreateMenuBar(PropertyDetailsBuilder& detailsBuilder, IAssetType* asset) override;

		//Draws the drop downs for the mesh materials
		void DrawMeshMaterialSelector(PropertyDetailsBuilder& detailsBuilder, IAssetType* _asset);

		//Draw all the model's meshes uvs
		void DrawModelUvs(class Model* _asset) const;

		//Draw a single mesh uvs
		void DrawUvCanvas(ImDrawList* drawlist, const Ref<FMesh>& mesh, uint32 id, size_t numMeshes) const;

	private:
		static float m_UVCanvasSize;
		static FVector2 m_UvPadding;
		static Color m_UvColor;
		static float m_UvThickness;
	};
}