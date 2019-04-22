#pragma once

#include "Core.h"
#include "Layer.h"

namespace BHive
{
	class EditorRenderLayer : public Layer
	{
	public:

		virtual void OnAttach() override;

		virtual void OnImGuiRender() override;

	};
}