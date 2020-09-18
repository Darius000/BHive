#pragma once

#include "BHive.h"
#include "BHive/Renderer/Asset.h"

namespace BHive
{
	class ImGuiPanel
	{
	public:
		ImGuiPanel(const char* label);
		virtual ~ImGuiPanel();

		virtual void OnImGuiRender() = 0;
	
		bool m_isOpen = true;
		const char* m_Label;
	};

	class BaseEditor : public ImGuiPanel
	{
	public:
		BaseEditor(const char* label) : ImGuiPanel(label){};

		void OnImGuiRender() override {};
	};

	template<class T = Asset>
	class Editor : public BaseEditor
	{
	public:
		Editor(const char* label, T* asset)
			:BaseEditor(label), m_Asset(asset){}

		void OnImGuiRender() override {};

	protected:
		Ref<T> m_Asset;
	};
}