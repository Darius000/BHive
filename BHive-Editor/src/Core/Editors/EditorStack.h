#pragma once

#include "BHive.h"
#include "ImGuiPanel.h"
#include "PopUps/PopUp.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/AssetBrowserPanel.h"
#include "Panels/ViewportPanel.h"
#include "Panels/PropertiesPanel.h"

namespace BHive
{
	class EditorStack
	{
	public:
		using Editors = std::unordered_map<uint64, Scope<ImGuiPanel>>;
		using PopUps = std::unordered_map<uint64, Scope<PopUp>>;
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

		template<typename T = PopUp, typename ... Args>
		PopUp* OpenPopup(Args&& ... args)
		{
			auto newpopup = CreateNewPopup<T>(std::forward<Args>(args)...);
			m_PopUps.emplace(GetNewPopupID(), newpopup);
			return newpopup;
		}

		//Updates the window stack
		void Update();

		void RenderPopUps();
		void RenderWindows();

		/*Remove particular panel from stack with its given id*/
		void ClosePanel(const uint64& PanelID);

		/*Remove particular panel from stack with its given id*/
		void ClosePopup(const uint64& PanelID);
		void ClosePopup(const PopUp& popup);

		//Send events to panels
		void ExecutePanelEvents(Event& event);

	private:
		Editors m_Editors;

		PopUps m_PopUps;

		uint64 m_CurrentPanelID = 0;

		uint64 m_PopUpID = 0;

		PanelIdList m_DestroyedPanelsIDList;

		PanelIdList m_DestroyedPopUpIDList;

		static EditorStack* s_EditorStack;

	private:

		void RenderCurrentWindow(ImGuiPanel* Panel);

		Scope<ImGuiPanel>& GetPanelFromID(uint64 PanelID);
		Scope<PopUp>& GetPopUpFromID(uint64 PanelID);

		uint64 GetNewPanelID();
		uint64 GetNewPopupID();

		template<typename T = ImGuiPanel, typename ... Args>
		ImGuiPanel* CreateNewPanel(Args&& ... args)
		{
			return new T(std::forward<Args>(args)..., m_CurrentPanelID);
		}

		template<typename T = ImGuiPanel, typename ... Args>
		PopUp* CreateNewPopup(Args&& ... args)
		{
			return new T(std::forward<Args>(args)..., m_PopUpID);
		}
	};
}