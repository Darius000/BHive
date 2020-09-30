#pragma  once

#include "Shader.h"
#include "Asset.h"

namespace BHive
{
	static const char* DefaultMaterialName = "DefaultMaterial";

	struct MaterialProperties
	{
		
	};

	struct DefaultMaterialProperties : public MaterialProperties
	{
		LinearColor3 m_DiffuseColor = LinearColor3(1.0f);
		LinearColor3 m_AmbientColor = LinearColor3(0.0f);
		FVector2 m_TextureTiling = FVector2(1.0f, 1.0f);
		float m_Opacity = 1.0;
	};

	struct LambertMaterialProperties : public DefaultMaterialProperties
	{
		FVector2 m_TextureTiling = FVector2(1.0f, 1.0f);
	};

	struct PhongMaterialProperties : public MaterialProperties
	{
		LinearColor3 m_Ambient = LinearColor3(0.0f);
		LinearColor3 m_Diffuse = LinearColor3(1.0f);
		LinearColor3 m_Emission = LinearColor3(0.0f);
		LinearColor3 m_Specular = LinearColor3(1.0f);
		float m_Opacity = 1.0f;
		bool m_CutOff = false;
		bool m_UseDiffuseAsAlpha = false;
		float m_Shininess = 20.0f;
		bool m_Doublesided = false;
		bool m_DiscardEdges = false;
		float m_HeightScale = .1f;
		FVector2 m_TextureTiling = FVector2(1.0f, 1.0f);
		Ref<Texture2D> m_DiffuseTexture;
		Ref<Texture2D> m_SpecularTexture;
		Ref<Texture2D> m_NormalTexture;
		Ref<Texture2D> m_EmissionTexture;
		Ref<Texture2D> m_AlphaTexture;
		Ref<Texture2D> m_DisplacementTexture;
	};

	struct ToonMaterialProperties : public MaterialProperties
	{
		Ref<Texture2D> m_DiffuseTexture;
		Ref<Texture2D> m_EmissionTexture;
		LinearColor3 m_Ambient = LinearColor3(0.0f);
		LinearColor3 m_Diffuse = LinearColor3(0.5f);
		LinearColor3 m_Emission = LinearColor3(0.0f);
		LinearColor3 m_Specular = LinearColor3(1.0f);
		float m_Opacity = 1.0f;
		bool m_CutOff = false;
		bool m_UseDiffuseAsAlpha = false;
		float m_Shininess = 20.0f;
		FVector2 m_Tiling = FVector2(1.0f);
	};

	struct GridMaterialProperties : public MaterialProperties
	{
		float m_Scale = 261.0f;
		float m_Resolution = .05f;
		LinearColor4 m_LineColor = LinearColor4(1.0f);
		LinearColor4 m_BackgroundColor = LinearColor4(.1f);
	};

	struct PostProcessingProperties : public MaterialProperties
	{
		Ref<Texture2D> m_SceneTexture;
	};

	class Material : public Asset
	{
	public:
		Material();
		virtual ~Material(){};

		void Render();
		
		virtual ShaderUniforms& GetShaderUniforms() = 0;

		virtual MaterialProperties& GetMaterialProperties() = 0;

		std::string GetAssetType() const override
		{
			return "Material";
		}

		const std::string GetThumbnailName() const override
		{
			return "materialicon";
		}

		Ref<Shader> GetShader()
		{
			return m_Shader;
		}

	protected:
		Ref<Shader> m_Shader;

		friend class FMesh;
		friend class MaterialEditorCustomizationDetails;
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


		MaterialProperties& GetMaterialProperties() override
		{
			return m_Properties;
		}

	public:
		
		DefaultMaterialProperties m_Properties;
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

		MaterialProperties& GetMaterialProperties() override
		{
			return m_Properties;
		}

		ShaderUniforms m_ShaderUniforms;
		LambertMaterialProperties m_Properties;

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

		MaterialProperties& GetMaterialProperties() override
		{
			return m_Properties;
		}
		
		ShaderUniforms m_ShaderUniforms;
		PhongMaterialProperties m_Properties;
	};

	class ToonMaterial : public Material
	{
	public:
		ToonMaterial();

		ShaderUniforms& GetShaderUniforms() override
		{
			return m_ShaderUniforms;
		}

		MaterialProperties& GetMaterialProperties() override
		{
			return m_Properties;
		}

		ShaderUniforms m_ShaderUniforms;
		ToonMaterialProperties m_Properties;
	};

	class GridMaterial : public Material
	{
	public:
		GridMaterial();

		MaterialProperties& GetMaterialProperties() override
		{
			return m_Properties;
		}

		ShaderUniforms& GetShaderUniforms() override
		{
			return m_ShaderUniforms;
		}

		ShaderUniforms m_ShaderUniforms;
		GridMaterialProperties m_Properties;
	};

	class PostProcessingMaterial : public Material
	{
	public:
		PostProcessingMaterial();

		MaterialProperties& GetMaterialProperties() override
		{
			return m_Properties;
		}

		ShaderUniforms& GetShaderUniforms() override
		{
			return m_ShaderUniforms;
		}

		ShaderUniforms m_ShaderUniforms;
		PostProcessingProperties m_Properties;
	};
}