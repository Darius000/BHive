#include "Registry.h"
#include "PrimitiveProperties.h"

namespace Reflection
{

	void Registry::Initialize()
	{
		Register(new charType());
		Register(new intType());
		Register(new floatType());
		Register(new stringType());
	}

	void Registry::Shutdown()
	{
		RemoveFromRegistry<char>();
		RemoveFromRegistry<int>();
		RemoveFromRegistry<float>();
		RemoveFromRegistry<stringType>();
	}

}

