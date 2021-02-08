#pragma once

#include <Reflection/Property.h>
#include <Reflection/ClassSpecifiers.h>
#include <Reflection/PropertySpecifiers.h>

#include "imgui.h"
#include "imgui_internal.h"

#include "Core/DataTypes.h"

namespace BHive
{
	template<typename T>
	class BaseProperty : public Reflection::Property<T>
	{

	public:
		BaseProperty(){};
		BaseProperty(const std::string& propertyName, T* val, T defaultValue = (T)0, bool UseButton = false, LinearColor4 color = {.5f, .5f, .5f, 1.0f}, bool UseColumnSpacing = true,
			Reflection::PropertyTags tags = (Reflection::PropertyTags)0,
			Reflection::PropertyMetaData metaData = (Reflection::PropertyMetaData)0, FunctionCallback callback = nullptr)
			:Reflection::Property<T>(propertyName, val, defaultValue, tags, metaData, callback), b_UseButton(UseButton),
			b_UseColumnSpacing(UseColumnSpacing), m_ButtonColor(color) 
		{

		}

	protected:
		void OnImGuiBegin() override
		{
			if (b_UseColumnSpacing) ImGui::Columns(2, name.c_str(), false);

			//enable disabled state for if property is read only
			if (tags && Reflection::PropertyTags::ReadOnly)
			{
				ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
				ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
			}

			if (b_UseButton)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, LColorToImCol32(m_ButtonColor));

				float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
				ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

				if (ImGui::Button(name.c_str(), buttonSize))
				{
					ResetValue();
					CallCallbackFunction();
				};
			}
			else
			{
				ImGui::Text(name.c_str());
			}

			b_UseColumnSpacing ? ImGui::NextColumn() : ImGui::SameLine();
		};

		void OnImGuiDraw() override
		{
			
		}

		void OnImGuiEnd() override
		{
			if (ImGui::BeginPopupContextItem(name.c_str()))
			{
				if (ImGui::MenuItem(("Reset " + name).c_str()))
				{
					ResetValue();

					CallCallbackFunction();
				}

				ImGui::EndPopup();
			}

			if (b_UseButton) ImGui::PopStyleColor();

			//disable disabled state for next item
			if (tags && Reflection::PropertyTags::ReadOnly)
			{
				ImGui::PopItemFlag();
				ImGui::PopStyleVar();
			}

			if (b_UseColumnSpacing) ImGui::Columns();	
		};

		bool b_UseButton = false;
		bool b_UseColumnSpacing = true;
		LinearColor4 m_ButtonColor;
	};

	template<typename Type>
	class BH_Property : public BaseProperty<Type>
	{
	public:
		BH_Property() {};
	};
}