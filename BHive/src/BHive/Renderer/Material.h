#pragma  once

#include "Shader.h"
#include "Assets/Asset.h"
#include "Uniforms/UniformCasts.h"

namespace BHive
{
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

		template<typename T = Uniform>
		void SetParameter(const std::string& name, const T& value);

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
		m_Shader->SetFloat(name, Cast<FloatUniform>(uniform)->Get());
	}

	template<>
	inline void Material::SetUniformImpl<ShaderUniformTypes::Bool>(const std::string& name, Uniform* uniform)
	{
		m_Shader->SetBool(name, Cast<BoolUniform>(uniform)->Get());
	}

	template<>
	inline void Material::SetUniformImpl<ShaderUniformTypes::Int>(const std::string& name, Uniform* uniform)
	{
		m_Shader->SetInt(name, Cast<IntUniform>(uniform)->Get());
	}

	template<>
	inline void Material::SetUniformImpl<ShaderUniformTypes::Vec2>(const std::string& name, Uniform* uniform)
	{
		m_Shader->SetVec2(name, Cast<Vec2Uniform>(uniform)->Get());
	}

	template<>
	inline void Material::SetUniformImpl<ShaderUniformTypes::Vec3>(const std::string& name, Uniform* uniform)
	{
		m_Shader->SetVec3(name, Cast<Vec3Uniform>(uniform)->Get());
	}

	template<>
	inline void Material::SetUniformImpl<ShaderUniformTypes::Sampler>(const std::string& name, Uniform* uniform)
	{
		SamplerUniform* samplerUniform = Cast<SamplerUniform>(uniform);
		auto tex = samplerUniform->Get();
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

	template<>
	inline void Material::SetUniformImpl<ShaderUniformTypes::SamplerCube>(const std::string& name, Uniform* uniform)
	{
		SamplerCubeUniform* samplerUniform = Cast<SamplerCubeUniform>(uniform);
		auto tex = samplerUniform->Get();
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

	template<typename T>
	void Material::SetParameter(const std::string& name, const T& value)
	{
		if(m_Parameters.find(name) == m_Parameters.end()) return;

		auto uniform = m_Parameters[name].get();
		if (auto typeuniform = Cast<TypeUniform<T>>(uniform))
		{
			typeuniform->Set(value);

			return;
		}
		
		BH_CORE_ERROR("Uniform Type must derive from template TypeUniform!");
	}

	template<ShaderUniformTypes Type>
	inline void Material::SetUniformImpl(const std::string& name, Uniform* uniform)
	{

	}
}