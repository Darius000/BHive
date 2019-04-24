#include "BHivePCH.h"
#include "BResource.h"
#include <filesystem>

namespace BHive
{
	BResource::BResource(const String& name)
		:Object(name)
	{

	}

	bool BResource::Load(const String& name, const String& path)
	{
		SetDisplayName(name);

		SetPath(path);

		return true;
	}

	void BResource::OnDestroyed()
	{
		Object::OnDestroyed();

		//Remove from asset manager 
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
		}
		ImGui::PopStyleColor();
	}

	bool BResource::DoesAssetFileExist(String fileName)
	{
		return std::filesystem::exists(fileName);
	}
}