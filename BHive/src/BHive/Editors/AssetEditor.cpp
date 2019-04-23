#include "BHivePCH.h"
#include "AssetEditor.h"


namespace BHive
{

	AssetEditor::AssetEditor(BResource& asset,const std::string& editorName)
		:m_EditorName(editorName)
	{
		m_Asset = &asset;
		m_WindowFlags = ImGuiWindowFlags_NoResize;
		m_Instance = s_Instances;
		s_Instances++;
		s_AssetEditors.emplace_back(this);
		BH_TRACE("{0}", s_Instances);
	}

	AssetEditor::AssetEditor(const AssetEditor& assetEditor)
	{
		m_Asset = assetEditor.m_Asset;
		m_EditorName = assetEditor.m_EditorName;
		m_ShowEditor = assetEditor.m_ShowEditor;
		m_WindowFlags = assetEditor.m_WindowFlags;
	}

	AssetEditor::~AssetEditor()
	{
		s_Instances--;
		s_AssetEditors.erase(s_AssetEditors.begin(), s_AssetEditors.end()+m_Instance);
	}

	void AssetEditor::ImGuiRender()
	{
		if (m_ShowEditor)
		{
			BeginImGuiRender();
			OnImGuiRender();
			EndImGuiRender();
		}
	}

	void AssetEditor::OnImGuiRender()
	{	
		ImGui::SetWindowSize(ImVec2(600.0f, 300.0f), ImGuiCond_Always);	
	}

	void AssetEditor::BeginImGuiRender()
	{
		ImGui::Begin((m_EditorName + "##" + std::to_string(m_Instance)).c_str(), &m_ShowEditor, m_WindowFlags);
	}

	void AssetEditor::EndImGuiRender()
	{
		ImGui::End();
	}

	unsigned int AssetEditor::s_Instances;

	std::vector<AssetEditor*> AssetEditor::s_AssetEditors;

}