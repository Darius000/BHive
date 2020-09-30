#include "BHivePCH.h"
#include "ClassRegistry.h"

namespace BHive
{

	ClassRegistry::ClassRegistryList& ClassRegistry::GetClassRegistryList()
	{
		return s_ClassRegistry;
	}

	void ClassRegistry::RegisterClassName(const char* classname)
	{
		s_ClassRegistry.push_back(classname);
	}

	ClassRegistry::ClassRegistryList ClassRegistry::s_ClassRegistry;

}