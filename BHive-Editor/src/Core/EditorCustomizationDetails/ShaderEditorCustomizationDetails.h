#pragma once

#include "EditorCustomizationDetails/EditorCustomizationDetails.h"

namespace BHive
{
	class ShaderEditorCustomizationDetails : public EditorCustomizationDetails
	{
	public:
		void CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder, IAssetType* _asset) override;

	};
}