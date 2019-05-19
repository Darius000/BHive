#pragma once

#include "BHive/Layer.h"
#include "World.h"

namespace BHive
{
	class BHive_API RenderLayer : public Layer
	{
	public:
		RenderLayer();
		~RenderLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;

		World* m_DefaultWorld;

		//unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	};
}