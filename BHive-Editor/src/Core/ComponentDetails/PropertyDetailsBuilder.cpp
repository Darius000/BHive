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

}