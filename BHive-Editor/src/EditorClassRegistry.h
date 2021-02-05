#pragma once

#include "BHive.h"
#include "BHive/Core/Registry/ClassRegistry.h"
#include "ComponentDetails/DetailsCustomization.h"
#include "EditorCustomizationDetails/EditorCustomizationDetails.h"


namespace BHive
{
	class EditorClassRegistry : public ClassRegistry
	{
	public:
		using AssetEditorList = std::unordered_map<std::string, Ref<EditorCustomizationDetails>>;
		using ClassDetailPropertyList = std::unordered_map<const char*, Ref<DetailsCustomization>>;

		static void RegisterClassDetails(const char* classname, Ref<DetailsCustomization> detailsCustomization);
		static void RegisterEditorCustomizationDetailsForAsset(const std::string& assetType, Ref<EditorCustomizationDetails> customization);

		static Ref<DetailsCustomization> GetDetailsCustomizationInstance(const char* className);
		static Ref<EditorCustomizationDetails> GetEditorForAsset(const std::string& type) { return s_AssetEditors[type]; }

		static ClassDetailPropertyList s_PropertyRegistry;
		static AssetEditorList s_AssetEditors;
	};
}

#include "EditorCustomizationDetails/CustomizationDetailsInclude.inl"