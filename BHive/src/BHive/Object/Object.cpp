#include "BHivePCH.h"
#include "Object.h"
#include "imgui.h"

namespace BHive
{
	Object::Object()
		:mDisplayName(GetClass() + std::to_string(unusedID)), mDestroyed(false), mSelected(false),
		mActive(false), mEnabled(true), mObjectID(GetNextID())
	{
		
	}

	unsigned int Object::unusedID = 0;

	std::vector<unsigned int> Object::deletedIDs;

	unsigned int Object::GetNextID()
	{
		if (deletedIDs.size() > 0)
		{
			unsigned int id = deletedIDs[0];
			deletedIDs.erase(deletedIDs.begin());
			return id;
		}
		
		unusedID++;
		return unusedID;
	}

	std::string Object::GetDisplayName() const
	{
		return mDisplayName;
	}

	void Object::Select()
	{
		mActive = true;

		mSelected = true;

		OnSelected(true);
	}

	bool Object::IsSelected() const
	{
		return mSelected;
	}

	void Object::SetDisplayName(const String& name) 
	{
		mDisplayName = name;
	}

	void Object::OnSelected(bool selected)
	{

	}

	void Object::Destroy()
	{
		mDestroyed = true;

		if (IsSelected())
		{
			UnSelect();
		}

		mEnabled = false;

		mActive = false;

		deletedIDs.emplace_back(unusedID);

		OnDestroyed();
	}

	bool Object::IsDestroyed() const
	{
		return mDestroyed;
	}

	void Object::OnDestroyed()
	{
		bool active = Object::GetStaticClass().mActive;
	}

	void Object::UnSelect()
	{
		mActive = false;

		mSelected = false;

		OnSelected(false);
	}

	void Object::SetEnabled(bool enable)
	{
		mEnabled = enable;
	}

	bool Object::IsEnabled() const
	{
		return mEnabled;
	}

	bool Object::IsActive() const
	{
		return mActive;
	}
}