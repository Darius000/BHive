#pragma once

#include "BHive/Components/MeshComponent.h"

namespace BHive
{
	class BHive_API PrimitiveComponent : public MeshComponent
	{

	public:
		PrimitiveComponent() {};

		virtual void ComponentInit() override;

	protected:
		virtual void CreatePrimitive() = 0;
		void UpdatePrimitive();
	};
}