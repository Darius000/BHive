#pragma once

#include "BHive.h"

namespace BHive
{ 
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(const Time& time) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;

	private:
		Ref<BHive::PerspectiveCameraController> m_OrthoCameraController;
		Plane* m_Plane;
		Ref<Texture2D> m_Texture;
		Ref<Texture2D> m_Texture2;
		Ref<FrameBuffer> m_Framebuffer;
		Triangle* triangle;
		FVector2 m_ViewportSize= {0, 0};
		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;
	};
}