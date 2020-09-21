#pragma once

#include "BHive/Core/ComponentDetails/EditorCustomizationDetails.h"
#include "BHive/Core/ComponentDetails/DetailsCustomization.h"

namespace BHive
{
	class ClassRegistry
	{
	public:
		using ClassRegistryList = std::vector<const char*>;
		using ClassDetailPropertyList = std::unordered_map<const char*, Ref<DetailsCustomization>>;
		using AssetEditorList = std::unordered_map<std::string, Ref<EditorCustomizationDetails>>;

		ClassRegistry() = default;

		static void RegisterClassDetails(const char* classname, Ref<DetailsCustomization> detailsCustomization);
		static void RegisterClassName(const char* classname);
		static void RegisterEditorCustomizationDetailsForAsset(const std::string& assetType, Ref<EditorCustomizationDetails> customization);

		static Ref<DetailsCustomization> GetDetailsCustomizationInstance(const char* className);
		static ClassRegistryList& GetClassRegistryList();
		static ClassRegistryList& GetFactoryRegistryList() { return s_ClassRegistry; }
		static Ref<EditorCustomizationDetails> GetEditorForAsset(const std::string& type) { return s_AssetEditors[type]; }

	private:
		static ClassDetailPropertyList s_PropertyRegistry;
		static ClassRegistryList s_ClassRegistry;
		static AssetEditorList s_AssetEditors;
	};
}