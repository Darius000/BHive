#pragma once

#include "Core.h"

namespace BHive
{
	enum ClassCategory
	{
		Class_None = 0,
		ObjectCategory = BIT(0),
		EntityCategory = BIT(1),
		ResourceCategory = BIT(2),
		ComponentCategory = BIT(3),
		PrimitiveCategory = BIT(4)
	};

#define BCLASS(name, category, base)\
		BCLASS_BASE(base)\
		BCLASS_NAME(name)\
		BCLASS_CATEGORY(category)

#define BCLASS_BASE(base)\
		typedef base Super;

#define BCLASS_NAME(name)\
		public:\
			static name GetStaticClass() {return name::name();}\
			virtual String GetClass() const override {return #name;}

#define BCLASS_CATEGORY(category)\
		public:\
			virtual int GetClassCategory() const override {return category; }

	class BHive_API Object
	{
	public:
	
	public:
		Object();
		virtual ~Object() {};
	public:
		String mDisplayName;
	public:
		static Object GetStaticClass() { return Object::Object(); }
		virtual String GetClass() const { return "Object"; }
		virtual int GetClassCategory() const { return ObjectCategory; }
		virtual void OnSelected(bool selected);
		virtual void CreateContextMenuItems() {};
		inline bool IsComponent() { return GetClassCategory() == ObjectCategory; }
	protected:
		virtual void OnDestroyed();
	public:
		void SetDisplayName(const String& name);
		void Select();
		void UnSelect();
		void SetEnabled(bool enable);
		void Destroy();
	
		String ToString() const { return GetDisplayName(); }
		String GetDisplayName() const;
		bool IsEnabled() const;
		bool IsActive() const;
		bool IsSelected() const;
		bool IsDestroyed() const;
		unsigned int GetObjectID()  const { return mObjectID; }

	private:
		bool mDestroyed;
		bool mEnabled;
		bool mActive;
		bool mSelected;
		unsigned int mObjectID;
		static unsigned int unusedID;
		static std::vector<unsigned int> deletedIDs;
		static unsigned int GetNextID();
	};	

	inline bool operator==(const Object& a, const Object& b);
	inline std::ostream& operator<<(std::ostream& os, const Object& object);

	#include "Object.inl"
}