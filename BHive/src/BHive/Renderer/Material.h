#pragma  once

#include "Shader.h"
#include "Assets/Asset.h"

namespace BHive
{
	static const char* DefaultMaterialName = "DefaultMaterial";

	class Material : public IAssetType
	{
	protected:
		using MaterialParameters = std::unordered_map<std::string, Scope<Uniform>>;

		DEFINE_ASSET_BODY(Material, "materialicon")
	public:

		Material();
		Material(Ref<Shader> shader);
		virtual ~Material(){};

		void Render();
		
		Ref<Shader> GetShader()
		{
			return m_Shader;
		}

		MaterialParameters& GetParameters(){ return m_Parameters; }

	protected:
		Ref<Shader> m_Shader;

	private:
		void QueryUniformsFromShader();
		void QueryUniformValue(uint32 ShaderID, Uniform* uniform, GLenum type);
		Uniform* QueryUniformType(GLenum type);
		void SetUniform(const std::string& name, Uniform* uniform);

		template<ShaderUniformTypes Type>
		inline void SetUniformImpl(const std::string& name, Uniform* uniform);

	private:
		MaterialParameters m_Parameters;

		friend class FMesh;
		friend class MaterialEditorCustomizationDetails;
	};

	template<>
	inline void Material::SetUniformImpl<ShaderUniformTypes::Float>(const std::string& name, Uniform* uniform)
	{
		m_Shader->SetFloat(name, Cast<FloatUniform>(uniform)->GetValue());
	}

	template<>
	inline void Material::SetUniformImpl<ShaderUniformTypes::Bool>(const std::string& name, Uniform* uniform)
	{
		m_Shader->SetBool(name, Cast<BoolUniform>(uniform)->GetValue());
	}

	template<>
	inline void Material::SetUniformImpl<ShaderUniformTypes::Int>(const std::string& name, Uniform* uniform)
	{
		m_Shader->SetInt(name, Cast<IntUniform>(uniform)->GetValue());
	}

	template<>
	inline void Material::SetUniformImpl<ShaderUniformTypes::Vec2>(const std::string& name, Uniform* uniform)
	{
		m_Shader->SetVec2(name, Cast<Vector2Uniform>(uniform)->GetValue());
	}

	template<>
	inline void Material::SetUniformImpl<ShaderUniformTypes::Vec3>(const std::string& name, Uniform* uniform)
	{
		m_Shader->SetVec3(name, Cast<Vector3Uniform>(uniform)->GetValue());
	}

	template<>
	inline void Material::SetUniformImpl<ShaderUniformTypes::Sampler>(const std::string& name, Uniform* uniform)
	{
		SamplerUniform* samplerUniform = Cast<SamplerUniform>(uniform);
		auto tex = samplerUniform->GetValue();
		if (tex)
		{
			tex->Bind(samplerUniform->m_SamplerIndex);
			m_Shader->SetInt(name, samplerUniform->m_SamplerIndex);
		}
		else
		{
			m_Shader->SetInt(name, 0);
		}
	}

	template<ShaderUniformTypes Type>
	inline void Material::SetUniformImpl(const std::string& name, Uniform* uniform)
	{

	}
}