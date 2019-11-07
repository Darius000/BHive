#include "BHivePCH.h"
#include "CameraController.h"

namespace BHive
{
	CameraController::CameraController(float aspectRatio)
		:m_AspectRatio(aspectRatio)
	{
		
	}

	void CameraController::SetZoomLevel(float level)
	{
		m_ZoomLevel = level;
	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BH_BIND_EVENT_FN(CameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BH_BIND_EVENT_FN(CameraController::OnWindowResized));
	}



	OrthographicCameraController::OrthographicCameraController(Ref<OrthographicCameraComponent>& camera, float aspectRatio, bool rotation )
		:CameraController(aspectRatio), m_Rotation(rotation), m_Camera(camera)
	{
		
	}

	void OrthographicCameraController::OnUpdate(const Time& time)
	{
		if (Input::IsKeyPressed(BH_KEY_A))
		{
			m_CameraPosition.x -= m_CameraSpeed * time;
		}
		else if (Input::IsKeyPressed(BH_KEY_D))
		{
			m_CameraPosition.x += m_CameraSpeed * time;
		}

		if (Input::IsKeyPressed(BH_KEY_W))
		{
			m_CameraPosition.y += m_CameraSpeed * time;
		}
		else if (Input::IsKeyPressed(BH_KEY_S))
		{
			m_CameraPosition.y -= m_CameraSpeed * time;
		}

		m_Camera->GetTransform().SetPosition(m_CameraPosition);

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(BH_KEY_Q))
			{
				m_CameraRotation += m_RotationSpeed * time;
			}
			else if (Input::IsKeyPressed(BH_KEY_E))
			{
				m_CameraRotation -= m_RotationSpeed * time;
			}

			m_Camera->GetTransform().SetRotation(Rotator(0.0f, 0.0f, m_CameraRotation));
		}
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset();
		MathLibrary::Clamp(m_ZoomLevel, 0.25f, m_ZoomLevel);
		m_CameraSpeed = m_ZoomLevel * 0.1f;
		m_Camera->SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera->SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	PerspectiveCameraController::PerspectiveCameraController(Ref<PerspectiveCameraComponent>& camera, float aspect)
		:CameraController(aspect), m_Camera(camera)
	{	
		m_Camera->SetProjection(glm::radians(45.0f), m_AspectRatio, .1f, 1000.0f);
		m_Camera->GetTransform().SetPosition(m_CameraPosition);
		//m_Camera->LookAt(FVector3(0.0f));
	}

	void PerspectiveCameraController::OnUpdate(const Time& time)
	{
		if (Input::IsKeyPressed(BH_KEY_A))
		{
			m_CameraPosition.x -= m_CameraSpeed * time;
		}
		else if (Input::IsKeyPressed(BH_KEY_D))
		{
			m_CameraPosition.x += m_CameraSpeed * time;
		}

		if (Input::IsKeyPressed(BH_KEY_W))
		{
			m_CameraPosition.y += m_CameraSpeed * time;
		}
		else if (Input::IsKeyPressed(BH_KEY_S))
		{
			m_CameraPosition.y -= m_CameraSpeed * time;
		}

		if (Input::IsKeyPressed(BH_KEY_Q))
		{
			m_CameraRotation.y += m_RotationSpeed * time;
		}
		else if (Input::IsKeyPressed(BH_KEY_E))
		{
			m_CameraRotation.y -= m_RotationSpeed * time;
		}

		/*if (Input::IsKeyPressed(BH_KEY_F))
		{
			m_Camera->LookAt(FVector3(0.0f));
		}*/

		m_Camera->GetTransform().SetRotation(m_CameraRotation);
		m_Camera->GetTransform().SetPosition(m_CameraPosition);
		//m_Camera->LookAt(FVector3(0.0f));
	}

	bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel = e.GetYOffset() * m_ZoomSpeed;
		BH_TRACE("Zoom Level: {0}", m_ZoomLevel * m_ZoomSpeed);
		//MathLibrary::Clamp(m_ZoomLevel, 0.25f, m_ZoomLevel);
		m_CameraSpeed = m_ZoomLevel * 0.1f;
		m_Camera->SetProjection(glm::radians(45.0f), m_AspectRatio, .1f, 1000.0f);
		m_CameraPosition.z += m_ZoomLevel;
		m_Camera->GetTransform().SetPosition(m_CameraPosition);
		//m_Camera->LookAt(FVector3(0.0f));
		return false;
	}

	bool PerspectiveCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera->SetProjection(glm::radians(45.0f), m_AspectRatio, .1f, 1000.0f);
		//m_Camera->LookAt(FVector3(0.0f));
		return false;
	}

}
