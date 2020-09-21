#include "BHivePCH.h"
#include "ClassRegistry.h"

namespace BHive
{
	void ClassRegistry::RegisterClassDetails(const char* classname, Ref<DetailsCustomization> detailsCustomization)
	{
		s_PropertyRegistry.insert({ classname, detailsCustomization });
	}

	Ref<DetailsCustomization> ClassRegistry::GetDetailsCustomizationInstance(const char* className)
	{
		return s_PropertyRegistry[className];
	}

	ClassRegistry::ClassRegistryList& ClassRegistry::GetClassRegistryList()
	{
		return s_ClassRegistry;
	}

	void ClassRegistry::RegisterClassName(const char* classname)
	{
		s_ClassRegistry.push_back(classname);
	}

	void ClassRegistry::RegisterEditorCustomizationDetailsForAsset(const std::string& assetType, Ref<EditorCustomizationDetails> customization)
	{
		s_AssetEditors.insert({ assetType, customization });
	}

	ClassRegistry::ClassDetailPropertyList ClassRegistry::s_PropertyRegistry;

	ClassRegistry::ClassRegistryList ClassRegistry::s_ClassRegistry;

	ClassRegistry::AssetEditorList ClassRegistry::s_AssetEditors;

}