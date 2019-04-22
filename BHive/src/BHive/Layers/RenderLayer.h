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

		void SetOpenGLStates();
		void PrintMaxVertexAttributes();
		void PrintOpenglInfo();

		bool openGLInitialized;

		World* mDefaultWorld;
	};
}