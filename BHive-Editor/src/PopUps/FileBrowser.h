#pragma once

#include "BHive.h"
#include "Core/UndoRedo.h"
#include "PopUp.h"

namespace BHive
{
	
	class IFileBrowser : public PopUp
	{
	public:
		IFileBrowser(): PopUp("File Browser"){}
		void OnImGuiRender() override;

	private:
		void RenderFileBrowser();
		void ShowFolderAndFiles();
		void ShowButtons();
		void ChangeDirectory(const WinPath& directory);
		void GoBack();
		void GoForward();
		void ShowFooter();

	private:
		static WinPath m_CurrentDirectory;
		static WinPath m_DefaultDirectory;
		static ImVec2 m_ModalSize;
		static IUndoRedo<WinPath> m_DirectoryHistory;
		static WinPath m_SelectedFile;
		static WinPath subPath;
		static bool m_ShowExtenstions;
	};
}