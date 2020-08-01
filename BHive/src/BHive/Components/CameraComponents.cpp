#include "BHivePCH.h"
#include "CameraComponents.h"


namespace BHive
{
	CameraComponent* CameraSystem::m_ActiveCamera = nullptr;

	CameraComponent::CameraComponent(Projection projection)
		:m_Camera(projection)
	{
		if (CameraSystem::m_ActiveCamera == nullptr)
		{
			SetPrimaryCamera(true);
		}
	}

	void CameraComponent::OnImGuiRender()
	{
		ImGui::Separator();

		const char* projections = "Perspective\0Orthographic\0";
		static int item = 0;

		if (ImGui::Combo("Projection", &item, projections))
		{
			switch (item)
			{
			case 0:
				m_Camera.m_ProjectionType = Projection::Perspective;
				m_Camera.SetPerspective(m_Camera.m_PerspSettings);
				break;
			case 1:
				m_Camera.m_ProjectionType = Projection::Orthographic;
				m_Camera.SetOthographic(m_Camera.m_OrthoSettings);
				break;
			}
		}

		if (m_Camera.m_ProjectionType == Projection::Perspective)
		{
			PerspectiveSettings settings = m_Camera.m_PerspSettings;

			ImGui::Text("Camera Settings");
			if (ImGui::InputFloat("FOV", &settings.FieldofView, .01f, 1.0f, 2) ||
				ImGui::InputFloat2("Aspect Ratio", *settings.AspectRatio, 2) ||
				ImGui::InputFloat("Near", &settings.Near, .01f, 1.0f, 2) ||
				ImGui::InputFloat("Far", &settings.Far, .01f, 1.0f, 2))
			{
				m_Camera.SetPerspective(settings);
			}
		}
		else
		{
			OrthographicSettings  settings = m_Camera.m_OrthoSettings;

			ImGui::Separator();
			if (ImGui::InputFloat("Top", &settings.Top, .01f, 1.0f, 2) ||
				ImGui::InputFloat("Bottom", &settings.Bottom, .01f, 1.0f, 2) ||
				ImGui::InputFloat("Left", &settings.Left, .01f, 1.0f, 2) ||
				ImGui::InputFloat("Right", &settings.Right, .01f, 1.0f, 2) ||
				ImGui::InputFloat("Near", &settings.Near, .01f, 1.0f, 2) ||
				ImGui::InputFloat("Far", &settings.Far, .01f, 1.0f, 2))
			{
				m_Camera.SetOthographic(settings);
			}
		}
	}

}