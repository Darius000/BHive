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
		void Start();
		void Update(const Time& time);
		void Refresh();

		template<typename T>
		T* AddEntity()
		{
			T* e = new T();
			std::unique_ptr<T> uPtr{ e };
			m_Entities.emplace_back(std::move(uPtr));
			return e;
		}

	private:
		std::vector<std::unique_ptr<Entity>> m_Entities;
		CameraComponent* m_Camera;
	};
}