#include "BHivePCH.h"
#include "Object.h"

namespace BHive
{

	Object::Object()
		:displayName("Object"), destroyed(false)
	{

	}

	Object::~Object()
	{

	}

	std::string Object::GetDisplayName()
	{
		return displayName;
	}

	std::string Object::GetClassDisplayName()
	{
		return std::string(typeid(this).name());
	}

	void Object::SetDisplayName(const std::string& string)
	{
		displayName = string;
	}

	void Object::Destroy()
	{
		destroyed = true;

		OnDestroyed();
	}

	bool Object::IsDestroyed()
	{
		return destroyed;
	}

	void Object::OnDestroyed()
	{

	}

}