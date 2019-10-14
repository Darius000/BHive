#include "BHivePCH.h"
#include "DirectoryGraph.h"
#include "BHive/Assets/BResourceManager.h"

namespace BHive
{

	Entry::Entry(FString name, FString path) 
		:mPath(path), mName(name), mSelected(false)
	{

	}

	void Entry::SetParent(Directory& parent)
	{
		mParent = &parent;
	}

	Directory::Directory(FString name, FString path)
		:Entry(name, path), mNumChildDirectories(0)
	{

	}

	void Directory::AddChild(std::unique_ptr<Directory>& directory)
	{
		mChildren.emplace(std::make_pair(directory->GetName(), std::move(directory)));
		mNumChildDirectories++;
	}

	void Directory::AddChild(std::unique_ptr<FileEntry>& file)
	{
		mChildren.emplace(std::make_pair(file->GetName(), std::move(file)));
	}

	void Directory::RemoveChild(FString name)
	{
		mChildren.erase(name);
	}

	void Directory::MoveChild(FString name, Directory& directory)
	{
		mChildren[name]->SetParent(directory);
	}

	FileEntry::FileEntry(FString name, FString path)
		:Entry(name, path)
	{

	}

	DirectoryTreeGraph::DirectoryTreeGraph(FString directory)
		: mDirectory(directory), mCurrentDirectory(nullptr), mPreviousDirectory(nullptr)
	{

	}

	void DirectoryTreeGraph::Construct()
	{
		mRoot = std::make_unique<Directory>(mDirectory, mDirectory);

		mCurrentDirectory = mRoot.get();

		CreateDirectoryTree(*mRoot.get(), mDirectory, mDirectory);
	}

	void DirectoryTreeGraph::CreateDirectoryTree(Directory& parent, FString name, FString directory)
	{
		bool exists = std::filesystem::exists(*directory);
		bool isDirectory = std::filesystem::is_directory(*directory);

		if (exists && isDirectory)
		{
			for (const auto& entry : std::filesystem::directory_iterator(*directory))
			{
				FString entryName = entry.path().filename().string().c_str();
				FString path = directory + "\\" + entryName;

				if (std::filesystem::is_directory(entry.status()))
				{
					std::unique_ptr<Directory> dirPtr = std::make_unique<Directory>(entryName, path);
					Directory* dir = dirPtr.get();

					AddDirectory(parent, dirPtr);

					CreateDirectoryTree(*dir, entryName, path);
				}
				else
				{
					//Add File to graph
					FString extension = entry.path().extension().string().c_str();

					std::unique_ptr<FileEntry> filePtr = std::make_unique<FileEntry>(entryName, path);

					AddFile(parent, filePtr, extension);
				}
			}
		}
	}

	void DirectoryTreeGraph::AddDirectory(Directory& parent, std::unique_ptr<Directory>& directory)
	{
		if (&parent == nullptr)
		{
			directory->SetParent(*mRoot.get());
			mRoot->AddChild(std::move(directory));
		}
		else
		{
			directory->SetParent(parent);
			parent.AddChild(std::move(directory));
		}
	}

	void DirectoryTreeGraph::AddFile(Directory& parent, std::unique_ptr<FileEntry>& file, FString extension)
	{
		file->extension = extension;
		if (&parent == nullptr)
		{
			file->SetParent(*mRoot.get());
			mRoot->AddChild(std::move(file));
		}
		else
		{
			file->SetParent(parent);
			OnFileEvent.Broadcast(file->GetName(), file->GetPath(), extension);
			parent.AddChild(std::move(file));
		}
	}

	void DirectoryTreeGraph::OnGUIRender()
	{
		OnGUIFolderBrowser();
	}

	void DirectoryTreeGraph::OnGUIChildRender(Directory& directory)
	{
		bool node = directory.mNumChildDirectories == 0 ?
			ImGui::TreeNodeEx(*directory.GetName(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_Leaf) :
			ImGui::TreeNodeEx(*directory.GetName(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnDoubleClick);

		if (node)
		{
			if (ImGui::IsItemClicked())
			{
				SelectDirectory(directory);
				//BH_TRACE("{0}", directory.GetName());
			}

			for (auto& child : directory.mChildren)
			{
				if (child.second->IsDirectory())
				{
					Directory* dir = dynamic_cast<Directory*>(child.second.get());

					OnGUIChildRender(*dir);
				}
			}

			ImGui::TreePop();
		}
	}

	void DirectoryTreeGraph::OnGUIFolderBrowser()
	{
		static Directory* currentSelectedDirectory = nullptr;

		ImVec2 wSize = ImGui::GetContentRegionMax();
		float columnWidth = (wSize.x / 5.0f) - 20.0f;

		ImGui::BeginChild("Folder_Browser", ImVec2(columnWidth, wSize.y), true);

		if (mRoot)
		{
			OnGUIChildRender(*mRoot.get());
		}

		ImGui::EndChild();
	}

	void DirectoryTreeGraph::SelectDirectory(Directory& directory)
	{
		mPreviousDirectory = mCurrentDirectory;
		mCurrentDirectory = &directory;
	}

	void DirectoryTreeGraph::SelectPreviousDirectory()
	{
		if (mPreviousDirectory)
		{
			Directory* temp = mCurrentDirectory;
			mCurrentDirectory = mPreviousDirectory;
			mPreviousDirectory = temp;

			return;
		}

		return;
	}

	Directory* DirectoryTreeGraph::GetSelectedDirectory() const
	{
		return mCurrentDirectory;
	}

}