#include "FileBrowser.h"
#include "Managers/AssetLoader.h"

namespace BHive
{
	void IFileBrowser::OnImGuiRender()
	{
		RenderFileBrowser();
	}

	void IFileBrowser::RenderFileBrowser()
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1,1));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(1,1));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(20, 20, 20, 255));
		
		if(ImGui::BeginPopupModal(m_Label, &m_IsOpen, ImGuiWindowFlags_AlwaysAutoResize))
		{ 
			m_ModalSize = ImGui::GetContentRegionAvail();

			if (!m_CurrentDirectory.IsValid())
			{
				m_CurrentDirectory = m_DefaultDirectory;
				FileHistoryNode* node = new FileHistoryNode(m_CurrentDirectory);
				m_DirectoryHistory.InsertHistory(node);
		
			}
			ShowButtons();			
			ShowFolderAndFiles();	
			ShowFooter();

			ImGui::EndPopup();
		}
		
		ImGui::PopStyleColor();
		ImGui::PopStyleVar(); 
		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
	
		//if(m_IsOpen) m_DirectoryHistory.m_History.OnImGuiRender();
	}

	void IFileBrowser::ShowFolderAndFiles()
	{
		ImGui::BeginChild("Files", ImVec2(500, 200), true, ImGuiWindowFlags_HorizontalScrollbar);

		auto& it = fs::directory_iterator(*m_CurrentDirectory);
		
		if (it->exists())
		{
			//static int index = 0;
			for (auto& item : it)
			{
				subPath = WinPath(item.path().string().c_str());
				if (ImGui::Selectable(m_ShowExtenstions ? subPath.GetNameWithExtentsion() : subPath.GetName(), subPath == m_SelectedFile))
				{
					bool bIsDirectory = subPath.IsDirectory();
					if (bIsDirectory)
					{
						ChangeDirectory(subPath);
					}
					else
					{
						m_SelectedFile = subPath;
					}
				}
			}
		}
		
		ImGui::EndChild();
	}

	void IFileBrowser::ShowButtons()
	{
		ImGui::BeginChild("Buttons", ImVec2(500, 25));
		if (ImGui::Button("Back"))
		{	
			GoBack();
		}

		ImGui::SameLine();

		if (ImGui::Button("Forward"))
		{
			GoForward();	
		}
		ImGui::EndChild();
	}

	void IFileBrowser::ChangeDirectory(const WinPath& directory)
	{
		FileHistoryNode* node = new FileHistoryNode(directory);
		m_DirectoryHistory.InsertHistory(node);
		m_CurrentDirectory = directory;
	}

	void IFileBrowser::GoBack()
	{
		m_CurrentDirectory = m_DirectoryHistory.Undo()->m_Data;
	}

	void IFileBrowser::GoForward()
	{
		m_CurrentDirectory = m_DirectoryHistory.Redo()->m_Data;
	}

	void IFileBrowser::ShowFooter()
	{
		
		ImGui::BeginChild("File Path", ImVec2(500, 100), true, ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::PushItemWidth(200);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10,0));
		ImGui::Columns(2);
		ImGui::PopStyleVar();
		ImGui::PopItemWidth();

		static char buffer[256] = "";
		if (ImGui::InputText("File", buffer, IM_ARRAYSIZE(buffer), ImGuiInputTextFlags_EnterReturnsTrue))
		{
			const char* pathBuffer = buffer;
			ChangeDirectory(WinPath(pathBuffer));
		}

		ImGui::PushItemWidth(200);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 0));
		ImGui::NextColumn();
		ImGui::PopStyleVar();
		ImGui::PopItemWidth();

		static int item = 0;
		const char* exts = "All";
		ImGui::Combo("", &item, exts);
		if (ImGui::Button("Import"))
		{
			m_IsOpen = false;
			Import(m_SelectedFile);
		}
		if (ImGui::Button("Cancel")) { m_IsOpen = false; }
		ImGui::EndChild();
	}

	WinPath IFileBrowser::subPath = "";

	bool IFileBrowser::m_ShowExtenstions = true;

	WinPath IFileBrowser::m_CurrentDirectory = "";

	WinPath IFileBrowser::m_DefaultDirectory = "../BHive/Assets";

	ImVec2 IFileBrowser::m_ModalSize = ImVec2();

	IUndoRedo<WinPath> IFileBrowser::m_DirectoryHistory;

	WinPath IFileBrowser::m_SelectedFile = "";

}
