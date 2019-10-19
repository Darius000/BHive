#include "BHivePCH.h"
#include "OrthographicCameraController.h"

namespace BHive
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{

	}

	void OrthographicCameraController::SetZoomLevel(float level)
	{
		m_ZoomLevel = level;
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

		m_Camera.GetTransform().SetPosition(m_CameraPosition);

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

			m_Camera.GetTransform().SetRotation(Rotator(0.0f, 0.0f, m_CameraRotation));
		}
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BH_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BH_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset();
		MathLibrary::Clamp(m_ZoomLevel, 0.25f, m_ZoomLevel);
		m_CameraSpeed = m_ZoomLevel * 0.1f;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}
