#include "BHivePCH.h"
#include "Object.h"
#include "imgui.h"

namespace BHive
{
	
	Object::Object()
		:mDisplayName(GetClass()), m_Destroyed(false), m_Enabled(true), m_ObjectID(s_IDGenerator.GenerateID())
	{

#ifdef BH_DEBUG
		//BH_CORE_TRACE("Name:{0} ; ID:{1}", GetClass(), m_ObjectID);
#endif

		OnSelectedEvent.AddBinding(BIND_EVENT_ONE_PARAM(Object::OnSelected));
		OnActiveEvent.AddBinding(BIND_EVENT_ONE_PARAM(Object::OnActive));
	}

	BString Object::GetDisplayName() const
	{
		return mDisplayName;
	}

	void Object::SetDisplayName(const BString& name) 
	{
		mDisplayName = name;
	}

	void Object::Destroy()
	{
		m_Destroyed = true;

		m_Enabled = false;

		s_IDGenerator.DeleteID(m_ObjectID);

		OnDestroyed();
	}

	bool Object::IsPendingDestroy() const
	{
		return m_Destroyed;
	}

	SelectedObjects Object::s_SelectedObjects;

	Object* Object::s_ActiveObject = nullptr;

	IDGenerator Object::s_IDGenerator;

	void Object::OnDestroyed()
	{
		
	}

	void Object::SetEnabled(bool enable)
	{
		m_Enabled = enable;
	}

	bool Object::IsEnabled() const
	{
		return m_Enabled;
	}

	void Object::OnActive(bool active)
	{
		if (!active) return;

		if(s_ActiveObject) s_ActiveObject->SetActive(false);
		s_ActiveObject = this;
		m_Active = true;
	}

	void Object::OnSelected(bool select)
	{
		auto& it = s_SelectedObjects.find(m_ObjectID);

		if (it != s_SelectedObjects.end()) return;

		if (select)
		{
			s_SelectedObjects[m_ObjectID] = this;
			this->m_Selected = select;
			this->SetActive(true);
			BH_CORE_TRACE("{0} : {1} selected", m_ObjectID, GetDisplayName());
		}
	}

	bool Object::IsSelected()
	{
		return m_Selected;
	}

	void Object::Select(bool selected)
	{
		OnSelectedEvent.Broadcast(selected);
	}

	void Object::ToggleSelection()
	{
		Select(!m_Selected);
	}

	bool Object::IsActive()
	{
		return m_Active;
	}

	void Object::SetActive(bool active)
	{
		OnActiveEvent.Broadcast(true);
	}

	void ObjectManager::Add(uint64 id, Scope<Object>& obj)
	{
		s_Objects[id] = std::move(obj);
	}

	void ObjectManager::Remove(uint64 id)
	{
		s_Objects.erase(id);
	}


	void ObjectManager::Refresh()
	{
		CheckPendingDestroy();
	}

	void ObjectManager::CheckPendingDestroy()
	{
		for (auto& object : s_Objects)
		{
			if (object.second->IsPendingDestroy())
			{
				object.second->Destroy();
				Remove(object.first);
			}
		}
	}

	class Object* ObjectManager::Get(uint64 id)
	{
		class Object* obj = s_Objects[id].get();

		if (obj) return obj;

		return nullptr;
	}

	std::unordered_map<uint64, Scope<class Object>> ObjectManager::s_Objects;

}