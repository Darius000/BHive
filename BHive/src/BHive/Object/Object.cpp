#include "BHivePCH.h"
#include "Object.h"
#include "imgui.h"

namespace BHive
{
	Object::Object()
		:mDisplayName(GetClass()), mDestroyed(false), mEnabled(true), mObjectID(s_IDGenerator.GenerateID())
	{

#ifdef BH_DEBUG
		BH_CORE_TRACE("Name:{0} ; ID:{1}", GetClass(), mObjectID);
#endif
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
		mDestroyed = true;

		mEnabled = false;

		s_IDGenerator.DeleteID(mObjectID);

		OnDestroyed();
	}

	bool Object::IsPendingDestroy() const
	{
		return mDestroyed;
	}

	IDGenerator Object::s_IDGenerator;

	void Object::OnDestroyed()
	{
		
	}

	void Object::SetEnabled(bool enable)
	{
		mEnabled = enable;
	}

	bool Object::IsEnabled() const
	{
		return mEnabled;
	}
}