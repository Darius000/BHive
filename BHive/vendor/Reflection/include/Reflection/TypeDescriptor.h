#pragma once

#include "Type.h"
#include "Registry.h"

namespace Reflection
{
	template<typename T>
	Type<T>* GetTypeDescriptor(T* obj)
	{
		return Registry::GetRegisteredType(obj);
	}
}