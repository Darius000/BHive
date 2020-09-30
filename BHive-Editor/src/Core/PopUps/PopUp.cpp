#include "PopUp.h"

namespace BHive
{
	PopUp::PopUp(const char* label) :m_Label(label)
	{

	}

	void PopUp::OnImGuiRender()
	{

	}

	void PopUp::OpenPopup()
	{
		m_IsOpen = true;
		ImGui::OpenPopup(m_Label);
	}
}