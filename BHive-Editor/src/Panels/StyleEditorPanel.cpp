#include "StyleEditorPanel.h"


namespace BHive
{
	void StyleEditorPanel::OnImGuiRender()
	{
		if (ImGui::Begin(m_Label, &m_isOpen))
		{
			ImGui::ShowStyleEditor();
			ImGui::End();
		}
	}

	void DemoWindowPanel::OnImGuiRender()
	{
		ImGui::ShowDemoWindow(&m_isOpen);
	}

}