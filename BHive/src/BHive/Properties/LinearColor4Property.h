#pragma once

#include "BaseProperty.h"

namespace BHive
{
	using LColor4Property = BH_Property<LinearColor4>;

	template<>
	class BH_Property<LinearColor4> : public BaseProperty<LinearColor4>
	{
	public:
		BH_Property(const std::string& propertyName, LinearColor4* val, LinearColor4 defaultValue, bool hdr,
			Reflection::PropertyTags tags = (Reflection::PropertyTags)0, Reflection::PropertyMetaData metaData = (Reflection::PropertyMetaData)0,
			FunctionCallback callback = nullptr)
			:BaseProperty(propertyName, val, defaultValue, false, {0.0f}, true, tags, metaData, callback), m_HDR(hdr)
		{

		}

		void OnImGuiDraw() override
		{
			auto flags = ImGuiColorEditFlags_::ImGuiColorEditFlags_Float;
			if (m_HDR) flags | ImGuiColorEditFlags_::ImGuiColorEditFlags_HDR;

			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImVec2 buttonSize = { ImGui::CalcItemWidth(), lineHeight };

			ImVec4 color = { value->r, value->g, value->b, value->a };
			if (ImGui::ColorButton(name.c_str(), color, 0, buttonSize))
			{
				// open a picker
				ImGui::OpenPopup("ColorPicker");
			}

			if (ImGui::BeginPopup("ColorPicker"))
			{
				ImGui::ColorPicker4(name.c_str(), &value->r, flags);
	
				ImGui::EndPopup();
			}
		}

	private:
		bool m_HDR;
	};
}