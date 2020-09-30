#pragma once


namespace BHive
{
	class ClassRegistry
	{
	public:
		using ClassRegistryList = std::vector<const char*>;
				
		ClassRegistry() = default;

		static void RegisterClassName(const char* classname);
		
		static ClassRegistryList& GetClassRegistryList();
		static ClassRegistryList& GetFactoryRegistryList() { return s_ClassRegistry; }
	
	private:
		
		static ClassRegistryList s_ClassRegistry;
	};

}