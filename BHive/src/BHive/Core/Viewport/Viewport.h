#pragma once

#include "Core/Scene/Scene.h"
#include "Renderer/Framebuffer.h"


namespace BHive
{
	enum class GBufferType : size_t
	{
		Position, SceneColor, Albedo, Specular, Normal, Emission, Ambient, TexCoord
	};

	static const char* GBufferTypeNames[9] = { "Position", "SceneColor", "Albedo", "Specular", "Normal","Emission", "Ambient" , "TexCoord"};

	struct GBufferAttribute
	{
		using InternalFormat = GLint;
		using Format = GLenum;
		using Type = GLenum;
		using TextureID = uint32;

		InternalFormat m_InternalFormat;
		Format m_Format;
		Type m_Type;
		TextureID m_Texture = 0;
	};

	using GBufferAttributes = std::unordered_map<GBufferType, GBufferAttribute>;

	class Viewport
	{
	public:
		
		Viewport(const FrameBufferSpecification& specs, Scene* scene);
		virtual ~Viewport();

		void OnUpdate(const Time& time);
		Scene* GetScene(){ return m_Scene; }
		
		
		void Resize(uint32 width, uint32 height);
	private:
		FrameBufferSpecification m_FramebufferSpecs;
		Ref<FrameBuffer> m_SceneFrameBuffer;
		Ref<FrameBuffer> m_QuadFrameBuffer;
		Ref<FrameBuffer> m_PingPongFrameBuffer[2];
		
		Ref<Material> ppm;
		Ref<Material> blurppm;
		Ref<Model> quad;
		Ref<Model> blurquad;
		Scene* m_Scene = nullptr;
		//Entity m_Camera;
		float m_Exposure = 0.8f;
		bool m_HDR = true;
		bool m_Bloom = true;

		friend class ViewportPanel;
	
		uint32 m_DepthAttachment = 0;
		uint32 m_DepthID = 0;
	
		GBufferAttributes m_GBufferAttributes;
	};
}