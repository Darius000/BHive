#include "BHivePCH.h"
#include "PopUp.h"

namespace BHive
{
	PopUp::PopUp(const std::string& label, const uint64& id) 
		:m_Label(label), m_ID(id)
	{
		
	}

	void PopUp::OnRender()
	{	
		ImGui::PushID((int)m_ID);
		if(!m_IsRendering) 
		{	
			ImGui::OpenPopup(m_Label.c_str());
			m_IsRendering = true;
		}

		if (ImGui::BeginPopup(m_Label.c_str()))
		{
			static float x = 0.0f;
			ImGui::SliderFloat("Test SLider", &x, 0.0f, 0.0f, "%2.f");
			ImGui::EndPopup();
		}
		ImGui::PopID();
	}
}