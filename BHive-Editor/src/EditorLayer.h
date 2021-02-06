#pragma once

#include "BHive.h"



namespace BHive
{ 
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		~EditorLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(const Time& time) override;
		void OnImGuiRender() override;
		void OnEvent(Event& event) override;

	public:

	private:
		//Editor Windows
		void DisplayMenuBar();

	private:
		Ref<Texture2D> m_Texture;
		Ref<Texture2D> m_Texture2;
		Entity actor0;
		
		Entity Camera2;
		Entity pl;
		Entity Light;
		Entity tri;

		Ref<Viewport> m_Viewport;

		bool b_ShowDemoWindow = false;
	};	
}