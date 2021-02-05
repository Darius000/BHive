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
}