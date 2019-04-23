#pragma once

#include "Core.h"
#include "imgui.h"

namespace BHive
{
	class BResource;

	class AssetEditor
	{
	public:
		AssetEditor(BResource& asset, const std::string& editorName);
		~AssetEditor();
		AssetEditor(const AssetEditor& assetEditor);

	protected:
		BResource* m_Asset;

		std::string m_EditorName;

		bool m_ShowEditor;

	protected:
		ImGuiWindowFlags_ m_WindowFlags;

	public:
		void ImGuiRender();

	protected:
		virtual void OnImGuiRender(); //Display custom UI to edit asset

	private:
		void BeginImGuiRender();
		void EndImGuiRender();
		unsigned int m_Instance;
	
	protected:
		static unsigned int s_Instances;

	public:
		static std::vector<AssetEditor*> s_AssetEditors;
	};
}