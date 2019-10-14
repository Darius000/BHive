#pragma once

#include "RenderComponent.h"

namespace BHive
{
	class BHive_API CollisionComponent : public RenderComponent
	{
		BCLASS(CollisionComponent, ComponentCategory, RenderComponent)

	public:
		CollisionComponent();
		~CollisionComponent();
	};
}

