#pragma once

#include "EditorCustomizationDetails.h"

namespace BHive
{
	struct FontAttributes;

	class FontEditorCustomizationDetails : public EditorCustomizationDetails
	{
	public:
		void CreateCustomizedDetails(class PropertyDetailsBuilder& detailsBuilder, class IAssetType* asset) override;
		void BeginNode(const std::string& id);
		void CreateFontNode(const std::string& name, FontAttributes& attributes);
		void EndNode();
		void CreateAddFontNode();
		void FontNode(const std::string& name, FontAttributes& attributes);
		void CreateFontFamilySettingsPanel();

	private:
		class PropertyDetailsBuilder* detailsBuilderPtr = nullptr;
		class FontFamily* fontFamily = nullptr;
		std::string newname = "";
	};
}