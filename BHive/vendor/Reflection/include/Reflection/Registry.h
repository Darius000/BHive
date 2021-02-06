#pragma once

#include <unordered_map>
#include "Type.h"

namespace Reflection
{
	class Registry
	{
	public:
		template<typename T>
		using RegisteredTypes = Type<T>*;

		Registry() = default;
		virtual ~Registry() = default;

		virtual void Initialize();

		virtual void Shutdown();

		template<typename T>
		void Register(Type<T>* type)
		{
			m_RegisteredTypes<T> = type;
		}

		template<typename T>
		void RemoveFromRegistry()
		{
			m_RegisteredTypes<T> = nullptr;
		}

		template<typename T>
		Type<T>* GetRegisteredType(T* obj)
		{
			return m_RegisteredTypes<T>[registerable];
		}

		template<typename T>
		static RegisteredTypes<T> m_RegisteredTypes;
	};

	template<typename T>
	Registry::RegisteredTypes<T> Registry::m_RegisteredTypes;

}