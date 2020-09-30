#include "EditorClassRegistry.h"

namespace BHive
{
	void EditorClassRegistry::RegisterEditorCustomizationDetailsForAsset(const std::string& assetType, Ref<EditorCustomizationDetails> customization)
	{
		s_AssetEditors.insert({ assetType, customization });
	}

	void EditorClassRegistry::RegisterClassDetails(const char* classname, Ref<DetailsCustomization> detailsCustomization)
	{
		s_PropertyRegistry.insert({ classname, detailsCustomization });
	}

	Ref<DetailsCustomization> EditorClassRegistry::GetDetailsCustomizationInstance(const char* className)
	{
		return s_PropertyRegistry[className];
	}

	EditorClassRegistry::ClassDetailPropertyList EditorClassRegistry::s_PropertyRegistry;

	EditorClassRegistry::AssetEditorList EditorClassRegistry::s_AssetEditors;

}