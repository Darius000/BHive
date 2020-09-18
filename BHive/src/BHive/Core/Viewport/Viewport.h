#pragma once

#include "Core/Scene/Scene.h"
#include "Renderer/Framebuffer.h"

namespace BHive
{
	class Viewport
	{
	public:
		Viewport(const FrameBufferSpecification& specs, Scene* scene);

		void OnUpdate(const Time& time);

		Ref<FrameBuffer>& GetFrameBuffer() { return m_Framebuffer; }
		Scene* GetScene(){ return m_Scene; }
		uint8 m_Data[800 * 600 * 4];

	private:
		FrameBufferSpecification m_FramebufferSpecs;
		Ref<FrameBuffer> m_Framebuffer;
		Scene* m_Scene = nullptr;
		Entity m_Camera;

		friend class ViewportPanel;
	};
}