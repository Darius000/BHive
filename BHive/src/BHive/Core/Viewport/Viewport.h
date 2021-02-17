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

	struct ViewportGridSettings
	{
		float m_Scale = 126.0f;
		FVector4 m_Color = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
	};

	class Viewport
	{
	public:
		
		Viewport(const FrameBufferSpecification& specs, Scene* scene);
		virtual ~Viewport();

		void OnUpdate(const Time& time);
		Scene* GetScene(){ return m_Scene; }
		
		void DrawGrid();
		
		void Resize(uint32 width, uint32 height);
	private:
		FrameBufferSpecification m_FramebufferSpecs;
		Ref<FrameBuffer> m_SceneFrameBuffer;
		Ref<FrameBuffer> m_QuadFrameBuffer;
		Ref<FrameBuffer> m_PingPongFrameBuffer[2];
		Ref<FrameBuffer> m_MultiSampledFrameBuffer;
		
		Ref<Shader> m_FinalResult;
		Ref<Shader> m_BloomPostProcessing;
		Ref<Shader> m_MultiSampleShader;
		Ref<Model> m_Quad;

		/*Begin Viewport Grid*/
		Ref<Model> m_Grid;

		Ref<Material> m_GridMaterial;

		ViewportGridSettings m_GridSettings;
		/*End Viewport Grid*/

		Scene* m_Scene = nullptr;
		//Entity m_Camera;
		float m_Exposure = 0.8f;
		bool m_HDR = true;
		bool m_Bloom = true;

		uint32 m_NumSamples = 16;

		friend class ViewportPanel;
	
		uint32 m_DepthAttachment = 0;
		uint32 m_DepthID = 0;
	
		GBufferAttributes m_GBufferAttributes;
	};
}