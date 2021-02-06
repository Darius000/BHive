#include "PropertyDetailsBuilder.h"


namespace BHive
{
	

	void PropertyDetailsBuilder::SetEntity(Entity& entity)
	{
		m_Entity = entity;
	}

	void PropertyDetailsBuilder::Label(const char* label)
	{
		ImGui::Text(label);
	}

	bool PropertyDetailsBuilder::Button(const char* label, const FVector2&& size)
	{
		if (ImGui::Button(label, ImVec2(size.x, size.y)))
		{
			return true;
		}

		return false;
	}

	void PropertyDetailsBuilder::Image(const Texture* texture, FVector2 size)
	{
		if(texture == nullptr) return;
		ImGui::Image((void*)*texture, ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0));
	}

	void PropertyDetailsBuilder::BeginProperty(const std::string& label)
	{
		ImGui::Columns(2, label.c_str(), false);

		ImGui::Text(label.c_str());

		ImGui::NextColumn();

		ImGui::PushID(label.c_str());
	}

	void PropertyDetailsBuilder::EndProperty()
	{
		ImGui::Columns();
		
		ImGui::PopID();
	}

	std::string PropertyDetailsBuilder::GetID(const std::string& label)
	{
		return (std::string("##") + label);
	}

	void PropertyDetailsBuilder::SearchBar(std::string& filter, float width )
	{
		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), filter.c_str());
		auto searchBarlabel = "##SearchBar";

		ImGui::BeginGroup();
		ImGui::PushItemWidth(width);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(2.0f, 0.0f));
		if (ImGui::InputText(searchBarlabel, buffer, sizeof(buffer)))
		{
			filter = std::string(buffer);
		}
		ImGui::PopItemWidth();
		ImGui::SameLine();

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight , lineHeight };

		auto magTexture = AssetManager::Get<Texture2D>("magnifier");

		ImGui::Image((void*)*magTexture, buttonSize, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::PopStyleVar();
		ImGui::EndGroup();
	}

	bool PropertyDetailsBuilder::CheckSearchFilter(const std::string& in, const std::string& filter)
	{
		auto it = std::search(in.begin(), in.end(), filter.begin(), filter.end(),
			[](char a, char b) { return std::tolower(a) == std::tolower(b); });

		return it != in.end();
	}

}