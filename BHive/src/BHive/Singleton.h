#pragma once

#include "Core.h"

namespace BHive
{
	template<typename T>
	class Singleton;

	template<typename T>
	class BHive_API Singleton
	{
		
	private: 
		static std::unique_ptr<T> s_Instance;

	protected:
		
		Singleton<T>() {  }

	public:
		virtual void OnConstruction() {};

		static T* GetInstance() 
		{
			if (nullptr == s_Instance)
			{
				s_Instance = std::make_unique<T>();
				s_Instance.get()->OnConstruction();
			}

			return s_Instance.get();
		}
	};

	template<typename T>
	std::unique_ptr<T> Singleton<T>::s_Instance;

}