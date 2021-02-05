#pragma once

#include "BHive.h"
#include "ImGuiPanel.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/AssetBrowserPanel.h"
#include "Panels/ViewportPanel.h"
#include "Panels/PropertiesPanel.h"

namespace BHive
{
	class EditorStack
	{
	public:
		using Editors = std::map<uint64, Scope<ImGuiPanel>>;
		using PanelIdList = std::vector<uint64>;
	
	private:
		EditorStack() ;
		~EditorStack();

	public:
		//Only one instance of an editor stack is needed
		static EditorStack* Get()
		{
			if (s_EditorStack == nullptr)
			{
				s_EditorStack = new EditorStack();

				return s_EditorStack;
			}

			return s_EditorStack;
		}

	public:
		template<typename T = ImGuiPanel, typename ... Args>
		void OpenPanel( Args&& ... args)
		{
			uint64 PanelID = GetNewPanelID();
			auto newPanel = CreateNewPanel<T>(std::forward<Args>(args)...);
			m_Editors.emplace(PanelID, newPanel);
		}

		//Updates the window stack
		void Update();

		/*Remove particular panel from stack with its given id*/
		void ClosePanel(const uint64& PanelID);

		//Send events to panels
		void ExecutePanelEvents(Event& event);

	private:
		Editors m_Editors;

		uint64 m_CurrentPanelID;

		PanelIdList m_DestroyedPanelsIDList;

		static EditorStack* s_EditorStack;

	private:

		void RenderCurrentWindow(ImGuiPanel* Panel);

		Scope<ImGuiPanel>& GetPanelFromID(uint64 PanelID);

		uint64 GetNewPanelID();

		template<typename T = ImGuiPanel, typename ... Args>
		ImGuiPanel* CreateNewPanel(Args&& ... args)
		{
			return new T(std::forward<Args>(args)..., m_CurrentPanelID);
		}
	};
}