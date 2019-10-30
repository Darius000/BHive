#pragma once

#include "BHive/Core/Layer.h"
#include "BHive/Object/Actor.h"

namespace BHive
{
	class BHive_API ActorManager
	{

	public:
		static void Start();
		static void Shutdown();
		static void Update(const Time& time);

	private:
		static void ResfreshActors();

	public:

		static void AddActor(Scope<Actor>& actor);

	private:
		static std::vector<Scope<Actor>> m_Actors;
	};

	template<typename T, typename ... Params>
	T* SpawnActor(const ANSICHAR* name, Transform transform , Params&&... params)
	{
		Scope<T> uPtr = std::make_unique<T>(std::forward<Params>(params)...);
		T* e = uPtr.get();
		ActorManager::AddActor(uPtr);
		e->GetTransform().SetPosition(transform.GetPosition());
		e->GetTransform().SetRotation(transform.GetRotation());
		e->GetTransform().SetScale(transform.GetScale());
		e->SetDisplayName(name);
		return e;
	}
}