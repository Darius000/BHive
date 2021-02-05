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

		virtual void CreateMenuBar(class PropertyDetailsBuilder& detailsbuilder, class IAssetType* asset){};
		virtual void CreateCustomizedDetails(class PropertyDetailsBuilder& detailsBuilder, class IAssetType* asset) {};
	};
}