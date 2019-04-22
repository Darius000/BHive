#pragma once

#include "Core.h"
#include "Interface.h"
#include "imgui.h"

namespace BHive
{	
	class IGuiInterface : public IInterface
	{
	public:
		IGuiInterface() {};
		virtual void OnGUIRender() = 0;
	};
}