#pragma  once

#include "Shader.h"
#include "Managers/AssetManagers.h"

namespace BHive
{

	

	class Material
	{
	public:
		Material();
		virtual ~Material(){};

		void Render();
		
		virtual ShaderUniforms& GetShaderUniforms() = 0;
	protected:
		Ref<Shader> m_Shader;
		

		friend class FMesh;
	};

	class DefaultMaterial : public Material
	{
	public:
		DefaultMaterial();
		virtual ~DefaultMaterial(){}

		ShaderUniforms& GetShaderUniforms() override
		{
			return m_ShaderUniforms;
		}

	public:
		LinearColor3 m_DiffuseColor		= LinearColor3(1.0f);
		LinearColor3 m_AmbientColor		= LinearColor3(0.0f);
		FVector2 m_TextureTiling		= FVector2(1.0f, 1.0f);
		float m_Opacity = 1.0;

		ShaderUniforms m_ShaderUniforms;
	};

	class LambertMaterial : public DefaultMaterial
	{
	public:
		LambertMaterial();
		virtual ~LambertMaterial(){}

		ShaderUniforms& GetShaderUniforms() override
		{
			return m_ShaderUniforms;
		}

		FVector2 m_TextureTiling = FVector2(1.0f, 1.0f);
		ShaderUniforms m_ShaderUniforms;
	};

	class PhongMaterial : public Material
	{
	public:
		PhongMaterial();

		virtual ~PhongMaterial(){}

		ShaderUniforms& GetShaderUniforms() override
		{
			return m_ShaderUniforms;
		}

		LinearColor3 m_Ambient =	LinearColor3(0.0f);
		LinearColor3 m_Diffuse =	LinearColor3(1.0f);
		LinearColor3 m_Emission =	LinearColor3(0.0f);
		LinearColor3 m_Specular =	LinearColor3(1.0f);
		float m_Opacity = 1.0f;
		bool m_CutOff = false;
		bool m_UseDiffuseAsAlpha = false;
		float m_Shininess = 20.0f;
		FVector2 m_TextureTiling = FVector2(1.0f, 1.0f);
		Ref<Texture2D> m_DiffuseTexture;
		Ref<Texture2D> m_SpecularTexture;
		Ref<Texture2D> m_EmissionTexture;
		Ref<Texture2D> m_AlphaTexture;
		ShaderUniforms m_ShaderUniforms;
	};

	class GridMaterial : public Material
	{
	public:
		GridMaterial();

		float m_Scale = 261.0f;
		float m_Resolution  = .05f;
		LinearColor4 m_LineColor		= LinearColor4(1.0f);
		LinearColor4 m_BackgroundColor	= LinearColor4(.1f);
		ShaderUniforms m_ShaderUniforms;
	};
}