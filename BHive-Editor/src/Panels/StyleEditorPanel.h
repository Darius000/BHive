#pragma once


#include "../Editors/Editor.h"

namespace BHive
{ 
	class StyleEditorPanel : public ImGuiPanel
	{
	public:
		StyleEditorPanel() : ImGuiPanel("Style Editor"){}
		void OnImGuiRender() override;

	};

	class DemoWindowPanel : public ImGuiPanel
	{
	public:
		DemoWindowPanel() : ImGuiPanel("Demo Window"){}
		void OnImGuiRender() override;
	};
}

