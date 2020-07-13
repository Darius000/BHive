#include "BHivePCH.h"
#include "CameraController.h"
#include "Core/Application.h"

namespace BHive
{
	CameraController::CameraController()
	{
		
	}

	void CameraController::SetZoomLevel(float level)
	{
		m_ZoomLevel = level;
	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_ONE_PARAM(CameraController::OnMouseScrolled));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_ONE_PARAM(CameraController::OnMouseMoved));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_ONE_PARAM(CameraController::OnMouseButtonPressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_ONE_PARAM(CameraController::OnMouseButtonReleased));
	}



	OrthographicCameraController::OrthographicCameraController(Ref<OrthographicCameraComponent>& camera, bool rotation )
		:CameraController(), m_Rotation(rotation), m_Camera(camera)
	{
		
	}


	const BHive::Ref<BHive::OrthographicCameraComponent>& OrthographicCameraController::GetCamera() const
	{
		return m_Camera;
	}

	void OrthographicCameraController::OnUpdate(const Time& time)
	{
		
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		return false;
	}

	bool OrthographicCameraController::OnMouseMoved(MouseMovedEvent& e)
	{
		return false;
	}

	bool OrthographicCameraController::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		return false;
	}


	bool OrthographicCameraController::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		return false;
	}


	PerspectiveCameraController::PerspectiveCameraController(Ref<PerspectiveCameraComponent> camera)
		:CameraController(), m_Camera(camera)
	{	
		m_CameraPosition = m_Camera->GetTransform().GetPosition();
	}

	void PerspectiveCameraController::OnUpdate(const Time& time)
	{
		m_DeltaTime = time.GetDeltaTime();
	}

	bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel = e.GetYOffset() * m_ZoomSpeed;
		BH_TRACE("Zoom Level: {0}", m_ZoomLevel * m_ZoomSpeed);

		m_CameraPosition.z += m_ZoomLevel;
		m_Camera->GetTransform().SetPosition(m_CameraPosition);
		return false;
	}

	bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent& e)
	{
		FVector2 MousePos = FVector2(e.GetX(), e.GetY());
		FVector2 DeltaMousePos = MousePos - m_OldMousePos;
		m_OldMousePos = MousePos;
		DeltaMousePos.Normalize();

		if (m_bMiddleMouseButtonPressed)
		{
			m_CameraPosition.x -= m_CameraSpeed * DeltaMousePos.x * m_DeltaTime; 
			m_CameraPosition.y += m_CameraSpeed * DeltaMousePos.y * m_DeltaTime;
			m_Camera->GetTransform().SetPosition(m_CameraPosition);
			BH_CORE_TRACE("mouse delta : {0}", DeltaMousePos.ToString());
		}

		if (m_bLeftMouseButtonPressed)
		{
			//ADD ROTATION HERE

			/*float WindowHeight	= (float)Application::Get().GetWindow().GetHeight();
			float WindowWidth	= (float)Application::Get().GetWindow().GetWidth();
			Vector2 MouseToCenterPos = Vector2(WindowHeight / 2.0f - MousePos.x, WindowWidth / 2.0f - MousePos.y);
			m_Angles +=  MouseToCenterPos * m_RotationSpeed * m_DeltaTime;
			Vector3 Direction = Vector3(cos(m_Angles.y) * sin(m_Angles.x),
			sin(m_Angles.y),
			cos(m_Angles.y) * cos(m_Angles.x));

			m_Camera->GetTransform().SetPosition(m_CameraPosition + Direction);*/
		}

		return false;
	}


	bool PerspectiveCameraController::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == BH_MOUSE_BUTTON_MIDDLE)
		{
			m_bMiddleMouseButtonPressed = true;

			BH_CORE_TRACE("{0}", m_bMiddleMouseButtonPressed);
		}
		else if(e.GetMouseButton() == BH_MOUSE_BUTTON_LEFT)
		{
			m_bLeftMouseButtonPressed = true;
		}

		return false;
	}


	bool PerspectiveCameraController::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		if (e.GetMouseButton() == BH_MOUSE_BUTTON_MIDDLE)
		{
			m_bMiddleMouseButtonPressed = false;

			BH_CORE_TRACE("{0}", m_bMiddleMouseButtonPressed);
		}
		else if (e.GetMouseButton() == BH_MOUSE_BUTTON_LEFT)
		{
			m_bLeftMouseButtonPressed = false;
		}

		return false;
	}
}
