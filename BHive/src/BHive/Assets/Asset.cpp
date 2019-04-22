#include "BHivePCH.h"
#include "Asset.h"
#include "Managers/AssetManager.h"

namespace BHive
{
	Asset::Asset(String name)
		:Object(name)
	{

	}

	Asset::Asset()
		:Object()
	{

	}

	bool Asset::Load(std::string name, std::string path)
	{
		SetDisplayName(name);

		mName = name;

		m_Path = path;

		return false;
	}

	void Asset::OnDestroyed()
	{
		Object::OnDestroyed();

		//Remove from asset manager 
	}

	void Asset::CreateEditorWindow()
	{
		new AssetEditor(*this, "Asset Editor");
	}

	void Asset::CreateContextMenuItems()
	{
		ImVec2 ButtonSize = ImVec2(100.0f, 20.0f);

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		if (ImGui::Button("Edit", ButtonSize))
		{
			CreateEditorWindow();
		}

		if (ImGui::Button("Delete",ButtonSize))
		{
			BH_INFO("Delete");

			AssetManager::GetInstance()->DeleteAsset(this);
		}
		ImGui::PopStyleColor();
	}

	void Asset::OnSave(std::fstream& file)
	{
		//throw std::logic_error("The method or operation is not implemented.");

		//SaveVariable(file, mDisplayName.c_str());

		BH_INFO("Saved");
	}

	void Asset::OnLoad(std::fstream& file)
	{
		//throw std::logic_error("The method or operation is not implemented.");
		//LoadVariable(file, mDisplayName);

		BH_INFO("Loaded");
	}

}