#pragma once

#include "Core.h"

namespace BHive
{
	class BHive_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//defined in client
	Application* CreateApplication();
}

