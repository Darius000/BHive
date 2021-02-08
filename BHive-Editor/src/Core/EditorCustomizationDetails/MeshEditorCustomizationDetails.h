#pragma once

#include "EditorCustomizationDetails.h"
#include "Properties/FloatProperty.h"
#include "Properties/BaseProperty.h"
#include "Properties/Vector2Property.h"
#include "Properties/LinearColor4Property.h"

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
		static LinearColor4 m_UvColor;
		static float m_UvThickness;


		static FloatProperty m_UvThicknessProp;
		static FloatProperty m_UvCanvasSizeProp;
		static FVector2Property m_UvPaddingProp;
		static LColor4Property m_UvColorProp;
	};
}