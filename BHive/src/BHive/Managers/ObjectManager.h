#pragma once

#include "Core.h"
#include "Singleton.h"

namespace BHive
{
	class Object;

	class ObjectManager : public Singleton<ObjectManager>
	{

	private:
		static Object* m_ActiveObject; // can only have one active object
		static std::vector<Object*> m_SelectedObjects; //can have multiple selected objects
		static int m_NumObjects; //number of objects added to selection
	public:
		static void SetActive(Object& object)
		{ 
			m_ActiveObject = &object; 
		}

		static Object* GetActive() 
		{ 
			return m_ActiveObject; 
		}

		static void AddSelectedObject(Object& object) 
		{ 
			auto* val = &std::find(m_SelectedObjects.begin(), m_SelectedObjects.end(), &object);
			if (!val)
			{
				m_SelectedObjects.emplace_back(&object);
				m_NumObjects++;
			}

			SetActive(object);
		}

		static void RemoveFromSelected(Object& object)
		{
			auto val = std::find(m_SelectedObjects.begin(), m_SelectedObjects.end(), &object);
			if (&object == m_ActiveObject)
			{
				if(m_SelectedObjects.size() > 0)
					m_ActiveObject = m_SelectedObjects.at(m_NumObjects -= 1);
			}
			if (val != m_SelectedObjects.end())
			{
				m_SelectedObjects.erase(val);
				m_NumObjects--;
			}
		}

		static std::vector<Object*> GetSelectedObjects() 
		{ 
			return m_SelectedObjects; 
		}
	};
}