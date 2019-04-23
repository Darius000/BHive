#include "BHivePCH.h"
#include "Object.h"
#include "imgui.h"

namespace BHive
{

	Object::Object(String name)
		:mDisplayName(name), mDestroyed(false), mSelected(false), 
		mActive(false), mEnabled(true), objectID(unusedID)
	{
		
	}

	Object::Object()
		:mDisplayName("Object" + std::to_string(unusedID)), mDestroyed(false), mSelected(false),
		mActive(false), mEnabled(true), objectID(unusedID)
	{
		unusedID++;
	}

	unsigned int Object::unusedID = 0;

	std::string Object::GetDisplayName() const
	{
		return mDisplayName;
	}

	std::string Object::GetClassDisplayName() const
	{
		return typeid(this).name();
	}

	void Object::Select()
	{
		mActive = true;

		mSelected = true;

		OnSelection(true);
	}

	bool Object::IsSelected() const
	{
		return mSelected;
	}

	void Object::SetDisplayName(const String& name) 
	{
		mDisplayName = name;
	}

	void Object::OnSelection(bool selected)
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

		OnDestroyed();
	}

	bool Object::IsDestroyed() const
	{
		return mDestroyed;
	}

	void Object::OnDestroyed()
	{

	}

	void Object::UnSelect()
	{

		mActive = false;

		mSelected = false;

		OnSelection(false);
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