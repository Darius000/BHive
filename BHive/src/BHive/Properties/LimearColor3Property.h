#pragma once

#include "BaseProperty.h"

namespace BHive
{
	using LColor3Property = BH_Property<LinearColor3>;

	template<>
	class BH_Property<LinearColor3> : public BaseProperty<LinearColor3>
	{
	public:
		BH_Property(const std::string& propertyName, LinearColor3* val, LinearColor3 defaultValue,
			Reflection::PropertyTags tags = Reflection::PropertyTags::None, Reflection::PropertyMetaData metaData = Reflection::PropertyMetaData::None,
			FunctionCallback callback = nullptr)
			:BaseProperty(propertyName, val, defaultValue, false, { 0.0f }, true, tags, metaData, callback)
		{

		}

		void OnImGuiDraw() override
		{
			auto flags = ImGuiColorEditFlags_::ImGuiColorEditFlags_Float;
			//if (m_HDR) flags += ImGuiColorEditFlags_HDR;

			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImVec2 buttonSize = { ImGui::CalcItemWidth(), lineHeight };

			ImVec4 color = { value->r, value->g, value->b, 1.0f };
			if (ImGui::ColorButton(name.c_str(), color, 0, buttonSize))
			{
				// open a picker
				ImGui::OpenPopup("ColorPicker");
			}

			if (ImGui::BeginPopup("ColorPicker"))
			{
				ImGui::ColorPicker3(name.c_str(), &value->r, flags);

				ImGui::EndPopup();
			}
		}
	};
}