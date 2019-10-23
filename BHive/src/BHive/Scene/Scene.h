#pragma once

#include "BHive/Object/Entity.h"
#include "BHive/Components/CameraComponents.h"

namespace BHive
{
	class Scene
	{
	public:
		Scene(CameraComponent& camera);

	public:
		void Begin();
		void Update(const Time& time);
		void End();
		void Refresh();

		template<typename T>
		T* AddEntity();

	private:
		struct SceneData
		{
			SceneData(CameraComponent& camera);

			glm::mat4 m_VPM;
			std::vector<Scope<Entity>> m_Entities;
			CameraComponent* m_Camera;
		};

		SceneData* m_SceneData;
	};

	template<typename T>
	T* BHive::Scene::AddEntity()
	{
		Scope<T> uPtr = std::make_unique<T>();
		T* e = uPtr.get();
		m_SceneData->m_Entities.emplace_back(std::move(uPtr));
		return e;
	}
}