#include "EditorStack.h"

namespace BHive
{
	EditorStack::EditorStack()
		:m_CurrentPanelID(0)
	{
		
	}

	EditorStack::~EditorStack()
	{
		
	}

	void EditorStack::Update()
	{		
	
		RenderWindows();
		//render popups on top, from newest to oldest
		RenderPopUps();

	}

	void EditorStack::RenderPopUps()
	{
		for (auto it = m_PopUps.begin(); it != m_PopUps.end();)
		{
			auto id = it->first;
			auto popup = it->second.get();

			if (popup && popup->IsOpen())
			{
				popup->OnRender();
				++it;
			}
			else
			{
				it++;
				 ClosePopup(id);
			}
		}
	}

	void EditorStack::RenderWindows()
	{
		for (auto it = m_Editors.begin(); it != m_Editors.end();)
		{
			auto panel = it->second.get();
			auto id = it->first;

			if (panel && panel->IsOpen())
			{
				RenderCurrentWindow(panel);
				++it;
			}
			else
			{
				it++;
				ClosePanel(id);
			}
		}
	}

	void EditorStack::ClosePanel(const uint64& PanelID)
	{
		//Check if panel exists before trying to close it
		if(!GetPanelFromID(PanelID))
		{ 
			BH_CORE_INFO("Panel with id {0} doesn't exist", PanelID);
			return;
		}

		//remove panel from list
		auto iterator = m_Editors.find(PanelID);
		m_Editors.erase(iterator);

		m_DestroyedPanelsIDList.push_back(m_CurrentPanelID);
	}

	void EditorStack::ClosePopup(const uint64& PanelID)
	{
		//Check if popup exists before trying to close it
		if (!GetPopUpFromID(PanelID))
		{
			BH_CORE_INFO("Panel with id {0} doesn't exist", PanelID);
			return;
		}

		//remove popup from list
		auto iterator = m_PopUps.find(PanelID);
		m_PopUps.erase(iterator);

		m_DestroyedPopUpIDList.push_back(m_PopUpID);
	}

	void EditorStack::ClosePopup(const PopUp& popup)
	{
		ClosePopup(popup.GetID());
	}

	void EditorStack::ExecutePanelEvents(Event& event)
	{
		for (auto it = m_Editors.begin(); it != m_Editors.end();)
		{
			auto panel = it->second.get();
			auto id = it->first;

			if (panel && panel->IsOpen())
			{
				if(panel->IsFocusedAndHoverd())
					panel->OnRecieveEvent(event);

				++it;
			}
			else
			{
				it++;
			}
		}
	}

	EditorStack* EditorStack::s_EditorStack = nullptr;

	void EditorStack::RenderCurrentWindow(ImGuiPanel* Panel)
	{	
		Panel->OnRender();
	}

	Scope<ImGuiPanel>& EditorStack::GetPanelFromID(uint64 PanelID)
	{
		Editors::iterator it = m_Editors.find(PanelID);
		return it->second;
	}

	Scope<PopUp>& EditorStack::GetPopUpFromID(uint64 PanelID)
	{
		PopUps::iterator it = m_PopUps.find(PanelID);
		return it->second;
	}

	uint64 EditorStack::GetNewPanelID()
	{
		uint64 newID = m_CurrentPanelID++;

		//check if any ids were deleted beforehand and set the id to the first element
		if (m_DestroyedPanelsIDList.empty() == false)
		{
			newID = m_DestroyedPanelsIDList[0];
			
			//remove first id from list
			auto firstID = m_DestroyedPanelsIDList.begin();
			m_DestroyedPanelsIDList.erase(firstID);
		}

		return newID;	
	}

	uint64 EditorStack::GetNewPopupID()
	{
		uint64 newID = m_PopUpID++;

		//check if any ids were deleted beforehand and set the id to the first element
		if (m_DestroyedPopUpIDList.empty() == false)
		{
			newID = m_DestroyedPopUpIDList[0];

			//remove first id from list
			auto firstID = m_DestroyedPopUpIDList.begin();
			m_DestroyedPopUpIDList.erase(firstID);
		}

		return newID;
	}

}