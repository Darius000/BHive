#include "BHivePCH.h"
#include "Primitive.h"

namespace BHive
{
	void PrimitiveComponent::ComponentInit()
	{
		UpdatePrimitive();
	}

	void PrimitiveComponent::UpdatePrimitive()
	{
		CreatePrimitive();

		UpdateBuffers();
	}
}
