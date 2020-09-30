#include "PropertyDetailsBuilder.h"
#include "imgui.h"

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

	void PropertyDetailsBuilder::Image(const uint32& ID, FVector2 size)
	{
		ImGui::Image((void*)ID, ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0));
	}
}