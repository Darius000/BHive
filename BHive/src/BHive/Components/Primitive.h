#pragma once

#include "RenderComponent.h"

namespace BHive
{
	//Add bind event for updating primitive

	DECLARE_EVENT(PrimitiveUpdate);

	class BHive_API PrimitiveComponent : public RenderComponent
	{

	public:
		PrimitiveComponent();

		virtual void ComponentInit() override;

	protected:
		virtual void CreatePrimitive() = 0;
		virtual void UpdatePrimitive();

		FPrimitiveUpdateEvent OnUpdatePrimitive;
	};
}