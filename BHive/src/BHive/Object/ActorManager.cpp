#include "BHivePCH.h"
#include "ActorManager.h"


namespace BHive
{

	void ActorManager::Start()
	{
		for (auto& actor : m_Actors)
		{
			actor->Start();
		}
	}

	void ActorManager::Shutdown()
	{
		for (auto& actor : m_Actors) {
			actor->Destroy();
		}

		ResfreshActors();
	}

	void ActorManager::Update(const Time& time)
	{
		for (auto& actor : m_Actors) {
			actor->Update(time);
		}

		ResfreshActors();
	}

	void ActorManager::ResfreshActors()
	{
		m_Actors.erase(std::remove_if(std::begin(m_Actors), std::end(m_Actors),
			[](const std::unique_ptr<Actor>& actor)
			{
				return actor->IsPendingDestroy();
			}), std::end(m_Actors));
	}

	void ActorManager::AddActor(Scope<Actor>& actor)
	{
		m_Actors.emplace_back(std::move(actor));
	}

	std::vector<Scope<Actor>> ActorManager::m_Actors;
}