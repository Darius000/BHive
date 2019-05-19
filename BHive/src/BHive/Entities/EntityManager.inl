#pragma once

namespace BHive
{
	template<typename T>
	T* EntityManager::AddEntity()
	{
		T* e = new T();
		std::unique_ptr<T> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return e;
	}
}