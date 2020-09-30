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
		
		
	private:
		FrameBufferSpecification m_FramebufferSpecs;
		
		Ref<FrameBuffer> m_Framebuffer;
		Ref<FrameBuffer> m_SceneFramebuffer;
	
		Ref<PostProcessingMaterial> ppm;
		Ref<Model> quad;
		Scene* m_Scene = nullptr;
		Entity m_Camera;
		float m_Exposure = 1.0f;
		bool m_HDR = false;

		friend class ViewportPanel;
	};
}