#include "BHivePCH.h"
#include "BResource.h"
#include <filesystem>

namespace BHive
{
	/*BResource::BResource(const String& name)
		:Object(name)
	{

	}*/

	/*bool BResource::Load(const String& name, const String& path)
	{
		SetDisplayName(name);

		//SetPath(path);

		SetFilePath("Data\\" + name + ".bh");

		return true;
	}*/

	void BResource::OnDestroyed()
	{
		Object::OnDestroyed();
	}

	void BResource::CreateEditorWindow()
	{
		new AssetEditor(*this, "Asset Editor");
	}

	void BResource::CreateContextMenuItems()
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

			DeleteResourceFile();
		}

		ImGui::PopStyleColor();
	}

	unsigned int BResource::GetIconData() const
	{
		return m_IconData;
	}

	/*bool BResource::DoesAssetFileExist(String fileName)
	{
		return std::filesystem::exists(fileName);
	}*/

	void BResource::OnSave(std::ofstream& resourceFile, const String& resourceFilePath)
	{
		//resourceFile << GetClass();
	}

	void BResource::OnLoad(std::ifstream& resourceFile)
	{
		//throw std::logic_error("The method or operation is not implemented.");
	}

}