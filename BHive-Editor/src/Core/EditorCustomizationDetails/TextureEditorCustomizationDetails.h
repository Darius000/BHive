#pragma once

#include "EditorCustomizationDetails/EditorCustomizationDetails.h"

namespace BHive
{
	class TextureEditorCustomizationDetails : public EditorCustomizationDetails
	{
	public:
		void CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder, IAssetType* _asset) override;
	};
}