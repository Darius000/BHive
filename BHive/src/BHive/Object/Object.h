#pragma once

#include "BHive/Core/IDGenerator.h"
#include "BHive/Interfaces/SelectableInterface.h"

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

	using SelectedObjects = std::unordered_map< uint64 , class Object*>;

	DECLARE_ONE_PARAMETER_EVENT(Selected, bool, selected)
	DECLARE_ONE_PARAMETER_EVENT(Active, bool, active)

	class BHive_API Object: public ISelectable
	{
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
		uint64 GetObjectID()  const { return m_ObjectID; }

	public:
		FSelectedEvent OnSelectedEvent;
		FActiveEvent OnActiveEvent;

	private:
		void OnActive(bool active);
		void OnSelected(bool select);

		//Start ISelectable
	public:
		virtual bool IsSelected() override;
		virtual void Select(bool selected) override;
		virtual void ToggleSelection() override;
		virtual bool IsActive() override;
		virtual void SetActive(bool active = true) override;
		//End ISelectable

	private:
		bool m_Destroyed;
		bool m_Enabled;
		bool m_Selected;
		bool m_Active;
		uint64 m_ObjectID;
		static SelectedObjects s_SelectedObjects;
		static Object* s_ActiveObject;
		static IDGenerator s_IDGenerator;
	};	

	inline bool operator==(const Object& a, const Object& b)
	{
		return (a.GetObjectID() == b.GetObjectID());
	}

	inline bool operator!=(const Object& a, const Object& b)
	{
		return (a.GetObjectID() != b.GetObjectID());
	}

	inline std::ostream& operator<<(std::ostream& os, const Object& object)
	{
		return os << object.ToString();
	}

	class ObjectManager
	{
	public:
		static void Add(uint64 id, Scope<Object>& obj);
		static void Remove(uint64 id);
		static void CheckPendingDestroy();
		static Object* Get(uint64 id);

	private:
		static std::unordered_map<uint64, Scope<class Object>> s_Objects;
	};

	template<typename T, typename ... Params>
	T* ConstructObject(const ANSICHAR* name, Params&&... params)
	{
		Scope<T> uPtr = std::make_unique<T>(std::forward<Params>(params)...);
		T* e = uPtr.get();
		ObjectManager::Add(e->GetObjectID(), uPtr);
		e->SetDisplayName(name);
		return e;
	};

	template<typename To, typename From>
	inline To* Cast(From* FromPtr)
	{
		return dynamic_cast<To*>(FromPtr);
	};

	template<typename To, typename From>
	inline To* StaticCast(From* FromPtr)
	{
		return static_cast<To*>(FromPtr);
	};

	template<typename T>
	inline bool IsValid(T* Obj)
	{
		return T* == nullptr? false : true;
	};

	template<typename T>
	inline bool CheckIsValid(Ref<T> Obj)
	{
		if(Obj == nullptr || Obj.use_count() == 0) return false;
		if (Object* ObjectPtr = Cast<Object>(Obj.get()))
		{
			if (ObjectPtr->IsPendingDestroy())
			{
				return false;
			}
		}

		return true;
	};

	inline bool CheckIsValid(Object* Obj)
	{
		if (Obj == nullptr) return false;
		if (Object* ObjectPtr = Cast<Object>(Obj))
		{
			if (ObjectPtr->IsPendingDestroy())
			{
				return false;
			}
		}

		return true;
	};

	#define ISVALID(From) IsValid(From)
	#define CHECKVALID(ptr) CheckIsValid(ptr)
}