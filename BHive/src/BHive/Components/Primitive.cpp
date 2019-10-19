#include "BHivePCH.h"
#include "Primitive.h"

namespace BHive
{

	PrimitiveComponent::PrimitiveComponent()
	{
		OnUpdatePrimitive.AddBinding(BIND_EVENT(&PrimitiveComponent::CreatePrimitive));
	}

	void PrimitiveComponent::ComponentInit()
	{
		CreatePrimitive();
	}

	void PrimitiveComponent::UpdatePrimitive()
	{
		OnUpdatePrimitive.Broadcast();
	}

}
