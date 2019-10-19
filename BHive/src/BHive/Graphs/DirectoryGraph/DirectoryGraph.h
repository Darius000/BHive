#pragma once

#include "BHive/Graphs/NodeGraph/NodeGraph.h"
#include<filesystem>

namespace BHive
{
	DECLARE_ONE_PARAMETER_EVENT(GO, bool, meet)
	DECLARE_TWO_PARAMETER_EVENT(ME, int, size, bool, run)
	DECLARE_THREE_PARAMETER_EVENT(File, FString, FileName, FString, Path, FString, Ext)
	DECLARE_FOUR_PARAMETER_EVENT(File2, FString, FileName, FString, Path, FString, Ext, int, age)
	DECLARE_FIVE_PARAMETER_EVENT(File3, FString, FileName, FString, Path, FString, Ext, int, age, bool, old)

	class Directory;
	class FileEntry;

	class Entry
	{
	public:
		Entry(FString name, FString path);
		void SetParent(Directory& parent);

		FString GetName() const { return mName; }
		FString GetPath() const { return mPath; }
		Entry* GetParent() const { return mParent; }

		virtual bool IsDirectory() const { return false; }

		bool mSelected;

	private:
		FString mName;
		FString mPath;
		Entry* mParent;

	};

	class Directory : public Entry
	{
	public:
		Directory(FString name, FString path);
		void AddChild(std::unique_ptr<Directory>& directory);
		void AddChild(std::unique_ptr<FileEntry>& file);
		void RemoveChild(FString name);
		void MoveChild(FString name, Directory& directory);
		virtual bool IsDirectory() const override { return true; }

	public:
		std::unordered_map<AName, std::unique_ptr<Entry>> mChildren;
		int mNumChildDirectories;
	};

	class FileEntry : public Entry
	{
	public:
		FileEntry(FString name, FString path);

		FString extension;
	};

	class DirectoryTreeGraph
	{
	public:
		/*DirectoryTreeGraph(FString directory);

		virtual void Construct();
		void CreateDirectoryTree(Directory& parent, FString name, FString directory);
		void AddDirectory(Directory& parent, std::unique_ptr<Directory>& directory);
		void AddFile(Directory& parent, std::unique_ptr<FileEntry>& file, FString extension);
		void OnGUIRender();
		void OnGUIChildRender(Directory&  directory);
		void OnGUIFolderBrowser();
		void SelectDirectory(Directory& directory);
		void SelectPreviousDirectory();
		Directory* GetSelectedDirectory() const;

		FFileEvent OnFileEvent;
	private:
		Directory* mCurrentDirectory;
		Directory* mPreviousDirectory;
		
	private:
		std::unique_ptr<Directory> mRoot;
		FString mDirectory;*/
	};
}