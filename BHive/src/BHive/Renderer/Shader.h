#pragma once

#include "Uniform.h"
#include "Assets/Asset.h"
#include "BHive/Managers/AssetManagers.h"
//#include "Core/Core.h"

namespace BHive
{
	
	static std::unordered_map<ShaderType, const char*> ShaderTypesToString = {{ShaderType::None,"None"}, {ShaderType::VertexShader, "Vertex"}, { ShaderType::FragmentShader,"Fragment"}};


	using ShaderUniforms = std::unordered_map<std::string, Scope<Uniform>>;

	class BHive_API Shader : public IAssetType
	{
	public:
		
		DEFINE_ASSET_BODY(Shader, "scripticon")

		using ShaderSource = std::unordered_map<ShaderType, std::string>;
		using ShaderIDs = std::unordered_map<ShaderType, uint32>;
		
	public:
		Shader(){}
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual void Compile() = 0;

		void SetUniform(const std::string& name, Uniform* uniform);

		template<ShaderUniformTypes Type>
		inline void SetUniformImpl(const std::string& name, Uniform* uniform);

		virtual void QueryUniforms(uint32 shader) = 0;
		virtual void SetBool(const BString& name, bool value) const = 0;
		virtual void SetInt(const BString& name, int value) const = 0;
		virtual void SetFloat(const BString& name, float value) const = 0;
		virtual void SetFloat2(const BString& name, float value0, float value1) const = 0;
		virtual void SetVec2(const BString& name, const FVector2& vec) const = 0;
		virtual void SetFloat3(const BString& name, float value0, float value1, float value2) const = 0;
		virtual void SetVec3(const BString& name, const FVector3& vec) const = 0;
		virtual void SetFloat4(const BString& name, float value0, float value1, float value2, float value3) const = 0;
		virtual void SetVec4(const BString& name, const FVector4& vec) const = 0;
		virtual void SetMat2(const BString& name, const glm::mat2& mat) const = 0;
		virtual void SetMat3(const BString& name, const glm::mat3& mat) const = 0;
		virtual void SetMat4(const BString& name, const glm::mat4& mat) const = 0;
		virtual uint32& GetID() = 0;
		virtual void SetUniforms();
		ShaderUniforms& GetUniforms(){ return m_Unforms; }

		static Ref<Shader> Create(const WinPath& filePath);
		static Ref<Shader> Create(const BName& name, const BString& vertexSrc, const BString& fragmentSrc);

	protected:
		ShaderSource m_Sources = {{ShaderType::VertexShader, ""}, {ShaderType::FragmentShader, ""}};
		ShaderIDs m_Ids;
		ShaderUniforms m_Unforms;
		
		friend class ShaderEditorCustomizationDetails;
		friend class Material;

		template<typename T>
		friend void Serialize(T* obj, const std::string& filepath);
	};

	template<>
	inline void Shader::SetUniformImpl<ShaderUniformTypes::Float>(const std::string& name, Uniform* uniform)
	{
		SetFloat(name, Cast<FloatUniform>(uniform)->GetValue());
	}

	template<>
	inline void Shader::SetUniformImpl<ShaderUniformTypes::Bool>(const std::string& name, Uniform* uniform)
	{
		SetBool(name, Cast<BoolUniform>(uniform)->GetValue());
	}

	template<>
	inline void Shader::SetUniformImpl<ShaderUniformTypes::Int>(const std::string& name, Uniform* uniform)
	{
		SetInt(name, Cast<IntUniform>(uniform)->GetValue());
	}

	template<>
	inline void Shader::SetUniformImpl<ShaderUniformTypes::Vec2>(const std::string& name, Uniform* uniform)
	{
		SetVec2(name, Cast<Vector2Uniform>(uniform)->GetValue());
	}

	template<>
	inline void Shader::SetUniformImpl<ShaderUniformTypes::Vec3>(const std::string& name, Uniform* uniform)
	{
		SetVec3(name, Cast<Vector3Uniform>(uniform)->GetValue());
	}

	template<>
	inline void Shader::SetUniformImpl<ShaderUniformTypes::Sampler>(const std::string& name, Uniform* uniform)
	{
		SamplerUniform* samplerUniform = Cast<SamplerUniform>(uniform);
		auto tex = samplerUniform->GetValue();
		if (tex)
		{
			tex->Bind(samplerUniform->m_SamplerIndex);
			SetInt(name , samplerUniform->m_SamplerIndex);
			//SetBool(name , true);
		}
		else
		{
			SetInt(name , 0);
			//SetBool(name , false);
		}
	}


	template<ShaderUniformTypes Type>
	inline void Shader::SetUniformImpl(const std::string& name, Uniform* uniform)
	{

	}

}
