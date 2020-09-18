#pragma once

#include "BHive.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/AssetBrowserPanel.h"
#include "Panels/ViewportPanel.h"
#include "Panels/StyleEditorPanel.h"
#include "PopUps/FileBrowser.h"
#include "Editors/EditorStack.h"

namespace BHive
{ 
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(const Time& time) override;
		void OnImGuiRender() override;
		void OnEvent(Event& event) override;

	public:
	//events
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);

	private:
		//Editor Windows
		void DisplayMenuBar();

	private:
		Ref<Texture2D> m_Texture;
		Ref<Texture2D> m_Texture2;
		Entity actor0;
		//Entity m_Camera;
		Entity Camera2;
		Entity pl;
		Entity Light;
		Entity tri;

		SceneHierarchyPanel* m_SceneHierarchyPanel = nullptr;
		AssetBrowserPanel* m_AssetBrowserPanel = nullptr;
		Viewport* m_Viewport = nullptr;
		Viewport* m_Viewport2 = nullptr;
		ViewportPanel* m_ViewportPanel = nullptr;
		ViewportPanel* m_ViewportPanel2 = nullptr;
		StyleEditorPanel* m_StyleEditorPanel = nullptr;
		DemoWindowPanel* m_DemoWindowPanel = nullptr;
	};	
}