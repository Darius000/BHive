#pragma once

#include "ComponentSystem.h"

namespace BHive
{
	class RenderSystem : public ComponentSystem
	{

	public:
		RenderSystem() = default;
		void OnInitialize() override;
		void OnUpdate(const Time& time, entt::registry& componentRegistry) override;
		void OnViewportResize(uint32 width, uint32 height, entt::registry& componentRegistry);

	private:
		uint32 m_ViewportWidth = 0;
		uint32 m_ViewportHeight = 0;
		
	};
}