#pragma once

#include "BHive/Core/IDGenerator.h"

namespace BHive
{
	enum ClassCategory
	{
		Class_None = 0,
		ObjectCategory = BIT(0),
		EntityCategory = BIT(1),
		ResourceCategory = BIT(2),
		ComponentCategory = BIT(3),
		PrimitiveCategory = BIT(4),
		MeshCategory = BIT(5)
	};

#define BCLASS(name, category, base)\
		BCLASS_BASE(base)\
		BCLASS_NAME(name)\
		BCLASS_CATEGORY(category)

#define BCLASS_BASE(base)\
		private:\
			typedef base Super;

#define BCLASS_NAME(name)\
		public:\
			static name GetStaticClass() {return name::name();}\
			virtual BString GetClass() const override {return #name;}

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
		BString mDisplayName;
	public:
		static Object GetStaticClass() { return Object::Object(); }
		virtual BString GetClass() const { return "Object"; }
		virtual int32 GetClassCategory() const { return ObjectCategory; }
		inline bool IsComponent() { return GetClassCategory() == ObjectCategory; }
	protected:
		virtual void OnDestroyed();
	public:
		void SetDisplayName(const BString& name);
		void SetEnabled(bool enable);
		void Destroy();
	
		BString ToString() const { return GetDisplayName(); }
		BString GetDisplayName() const;
		bool IsEnabled() const;
		bool IsPendingDestroy() const;
		uint64 GetObjectID()  const { return mObjectID; }

	private:
		bool mDestroyed;
		bool mEnabled;
		uint64 mObjectID;
		static IDGenerator s_IDGenerator;
	};	

	inline bool operator==(const Object& a, const Object& b)
	{
		return (a.GetObjectID() == b.GetObjectID());
	}

	inline std::ostream& operator<<(std::ostream& os, const Object& object)
	{
		return os << object.ToString();
	}
}