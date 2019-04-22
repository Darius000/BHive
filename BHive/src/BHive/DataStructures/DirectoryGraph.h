#pragma once

#include "Core.h"
#include "NodeGraph.h"
#include<filesystem>

namespace BHive
{
	DECLARE_THREE_PARAMETER_EVENT(File, String, FileName, String, Path, String, Ext);

	class Directory;
	class FileEntry;

	class Entry
	{
	public:
		Entry(String name, String path);
		void SetParent(Directory& parent);

		String GetName() const { return mName; }
		String GetPath() const { return mPath; }
		Entry* GetParent() const { return mParent; }

		virtual bool IsDirectory() const { return false; }

		bool mSelected;

	private:
		String mName;
		String mPath;
		Entry* mParent;

	};

	class Directory : public Entry
	{
	public:
		Directory(String name, String path);

		//Add child entry to directory and set ownership to this
		void AddChild(std::unique_ptr<Directory>& directory);
		void AddChild(std::unique_ptr<FileEntry>& file);

		//Remove child entry from directory
		void RemoveChild(String name);

		//Move entry to another directory
		void MoveChild(String name, Directory& directory);

		virtual bool IsDirectory() const override { return true; }

	public:
		std::unordered_map<String, std::unique_ptr<Entry>> mChildren;
		int mNumChildDirectories;
	};

	class FileEntry : public Entry
	{
	public:
		FileEntry(String name, String path);

		String extension;
	};

	class DirectoryTreeGraph: public IGuiInterface
	{
	public:
		DirectoryTreeGraph(String directory);

		virtual void Construct();
		void CreateDirectoryTree(Directory& parent, String name, String directory);
		void AddDirectory(Directory& parent, std::unique_ptr<Directory>& directory);
		void AddFile(Directory& parent, std::unique_ptr<FileEntry>& file, String extension);
		void OnGUIRender() override;
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
		String mDirectory;
	};
}