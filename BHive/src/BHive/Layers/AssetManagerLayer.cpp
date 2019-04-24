#include "BHivePCH.h"
#include "AssetManagerLayer.h"
#include "imgui.h"
#include "Application.h"

namespace BHive
{

	AssetManagerLayer::AssetManagerLayer(BResourceManager& resourceManager)
		:mAssetmanager(resourceManager)
	{
	
	}

	void AssetManagerLayer::OnAttach()
	{
		mFolderImage = mAssetmanager.GetAsset("folder.png");
		mBackImage = mAssetmanager.GetAsset("back.png");
	}

	void AssetManagerLayer::OnImGuiRender()
	{
	
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_None;

		int i = 0;

		static bool show = true;

		ImGui::Begin("Asset Browser", &show ,ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar);
		ImGui::SetWindowSize(ImVec2((float)Application::Get().GetWindow().GetWidth(), 300.0f), ImGuiCond_FirstUseEver);	//Set Window Size of Asset Browser
		
		/////////////////////////////////////////////////
		//Menu Bar for the browser window
		AssetMenuBar();
		//////////////////////////////////////////////////

		ImVec2 wSize = ImGui::GetContentRegionMax();
		float columnWidth = wSize.x - (wSize.x / 54.0f);

		mAssetmanager.mDirectoryGraph->OnGUIRender();
		
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ChildBg, (ImVec4)ImColor(.8f, .8f, .8f));
		ImGui::BeginChild("Assets", ImVec2(columnWidth, wSize.y), true);

		if (mAssetmanager.mDirectoryGraph->GetSelectedDirectory())
		{
			static bool showContextMenu = false;

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 0.0f));

			for (auto& entry : mAssetmanager.mDirectoryGraph->GetSelectedDirectory()->mChildren)
			{
				String name = entry.second->GetName();
				bool isDirectory = entry.second->IsDirectory();

				if (isDirectory)
				{
					//Show folder image here
					ImGui::ImageButton((void*)(intptr_t)mFolderImage->GetData(), ImVec2(128.0f, 128.0f), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
					if (ImGui::IsItemClicked(0))
					{
						Directory* dir = dynamic_cast<Directory*>(entry.second.get());
						mAssetmanager.mDirectoryGraph->SelectDirectory(*dir);
					}
				}
				else
				{
					//Display asset icon here
					BResource* asset = mAssetmanager.GetAsset(name);

					if (asset)
					{
						ImGui::ImageButton((void*)(intptr_t)asset->GetData(), ImVec2(128.0f, 128.0f), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
						if (ImGui::IsItemClicked(1))
						{
							mAssetmanager.mSelectedAsset = asset;
							ImGui::OpenPopup("objectContextMenu");
						}
						ImGui::Text(asset->mDisplayName.c_str());
						
					}
				}
			}

			if (BeginContextMenu("objectContextMenu"))
			{
				CreateObjectContextMenu(*mAssetmanager.mSelectedAsset);
				EndContextMenu();
			}

			ImGui::PopStyleColor();
		}

		ImGui::EndChild();
		ImGui::PopStyleColor();
		ImGui::End();
	}

	bool AssetManagerLayer::BeginContextMenu(const String& id)
	{
		
		if (ImGui::BeginPopupContextItem(id.c_str()))
		{
			ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(1.0f, .3f, .3f, .5f));
			ImGui::SetWindowPos(ImGui::GetMousePos(), ImGuiCond_FirstUseEver);
			ImGui::SetWindowSize(ImVec2(100.0f, 200.0f));
			return true;
		}

		return false;
	}

	void AssetManagerLayer::CreateObjectContextMenu(class Object& object)
	{
			if (&object)
				object.CreateContextMenuItems();
	}

	void AssetManagerLayer::CreateAssetContextMenu()
	{
		
	}

	void AssetManagerLayer::EndContextMenu()
	{
		ImGui::PopStyleColor();
		ImGui::EndPopup();
	}

	void AssetManagerLayer::AssetMenuBar()
	{
		ImGui::BeginMenuBar();
		bool backBtnPressed = ImGui::MenuItem("Back");
		bool importBtnPressed = ImGui::MenuItem("Import");
		ImGui::EndMenuBar();

		if (backBtnPressed)
		{
			mAssetmanager.mDirectoryGraph->SelectPreviousDirectory();

			BH_INFO("Back");
		}

		if (importBtnPressed)
		{
			BH_INFO("Import");

			String importDir = mAssetmanager.mDirectoryGraph->GetSelectedDirectory()->GetPath();

			mAssetmanager.ImportAsset(importDir);
		}
	}
}