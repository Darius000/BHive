#include <BHive.h>
#include "EditorLayer.h"
#include "BHive/Core/EntryPoint.h"

namespace BHive
{ 
	class BHiveEditor : public Application
	{
	public:
		BHiveEditor()
			:Application("BHive Editor")
		{
			PushLayer(new EditorLayer());
		}

		~BHiveEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new BHiveEditor();
	}
}