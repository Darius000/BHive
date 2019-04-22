#pragma once

#include "Core.h"

namespace BHive
{
	class BHive_API Object
	{

	public:
		Object();
		Object(String name);
		virtual ~Object() {};

	public:
		String mDisplayName;
	private:
		bool mDestroyed;
		bool mEnabled;
		bool mActive;
		bool mSelected;
		unsigned int objectID;
		static unsigned int unusedID;

	public:
		String GetDisplayName() const;
		String GetClassDisplayName() const;

		void Select();
		void UnSelect();
		void SetEnabled(bool enable);
		bool IsEnabled() const;
		bool IsActive() const;
		bool IsSelected() const;
		void SetDisplayName(const String& name);
		virtual void OnSelection(bool selected);
		virtual void CreateContextMenuItems() {};
	public:
		void Destroy();
		bool IsDestroyed() const;

	protected:
		virtual void OnDestroyed();

		bool operator==(const Object& a) const
		{
			return (a.objectID == objectID);
		}
	};

	
}