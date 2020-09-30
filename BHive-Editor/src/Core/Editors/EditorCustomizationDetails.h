#pragma once

#include "Core/ComponentDetails/PropertyDetailsBuilder.h"

namespace BHive
{
	class EditorCustomizationDetails 
	{
	public:
		EditorCustomizationDetails() = default;
		EditorCustomizationDetails(const EditorCustomizationDetails&) = default;
		virtual ~EditorCustomizationDetails() = default;

		virtual void CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder, Asset* asset) {};
	};

	class TextureEditorCustomizationDetails : public EditorCustomizationDetails
	{
	public:
		void CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder, Asset* _asset) override;
	};

	class MaterialEditorCustomizationDetails : public EditorCustomizationDetails
	{
	public:
		void CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder, Asset* _asset) override;
	};

	class MeshEditorCustomizationDetails : public EditorCustomizationDetails
	{
	public:
		void CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder, Asset* _asset) override;
	};

	class ShaderEditorCustomizationDetails : public EditorCustomizationDetails
	{
	public:
		void CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder, Asset* _asset) override;

	};
}