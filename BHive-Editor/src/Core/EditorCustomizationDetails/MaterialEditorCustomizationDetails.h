#pragma once

#include "EditorCustomizationDetails/EditorCustomizationDetails.h"

namespace BHive
{
	class MaterialEditorCustomizationDetails : public EditorCustomizationDetails
	{
	public:
		void CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder, IAssetType* _asset) override;
	};
}


