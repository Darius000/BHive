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
		virtual void OnShaderBind(Ref<Shader>& shader) = 0;

		Ref<Texture2D> m_Texture;

	protected:
		Ref<Shader> m_Shader;
		

		friend class FMesh;
	};

	class DefaultMaterial : public Material
	{
	public:
		DefaultMaterial();
		virtual ~DefaultMaterial(){}

		void OnShaderBind(Ref<Shader>& shader) override;

	public:
		FVector3 m_DiffuseColor		= FVector3(1.0f);
		FVector3 m_AmbientColor		= FVector3(0.0f);
		FVector2 m_TextureTiling	= FVector2(1.0f, 1.0f);
		float m_Transparency = 0.0;
	};

	class LambertMaterial : public DefaultMaterial
	{
	public:
		LambertMaterial();
		virtual ~LambertMaterial(){}

		void OnShaderBind(Ref<Shader>& shader) override;

		FVector2 m_TextureTiling = FVector2(1.0f, 1.0f);
	};

	class PhongMaterial : public Material
	{
	public:
		PhongMaterial();

		virtual ~PhongMaterial(){}

		void OnShaderBind(Ref<Shader>& shader) override;

		FVector3 m_Ambient = FVector3(0.0f);
		FVector3 m_Diffuse = FVector3(1.0f);
		FVector3 m_Emission = FVector3(0.0f);
		FVector3 m_Specular = FVector3(1.0f);
		float m_Transparency = 0.0f;
		float m_Shininess = 20.0f;
		FVector2 m_TextureTiling = FVector2(1.0f, 1.0f);
		Ref<Texture2D> m_DiffuseTexture;
		Ref<Texture2D> m_SpecularTexture;
		Ref<Texture2D> m_EmissionTexture;
	};

	class GridMaterial : public Material
	{
	public:
		GridMaterial();


		void OnShaderBind(Ref<Shader>& shader) override;

		float m_Scale = 261.0f;
		float m_Resolution  = .05f;
		FVector4 m_LineColor = FVector4(1.0f);
		FVector4 m_BackgroundColor = FVector4(.1f);
	};
}