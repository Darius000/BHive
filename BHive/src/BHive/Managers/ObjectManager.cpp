#include "BHivePCH.h"
#include "ObjectManager.h"

namespace BHive
{

	Object* ObjectManager::m_ActiveObject = nullptr;

	std::vector<Object*> ObjectManager::m_SelectedObjects;

	int ObjectManager::m_NumObjects = 0;

}