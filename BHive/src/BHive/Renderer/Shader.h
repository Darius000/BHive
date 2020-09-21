#pragma once

#include "Asset.h"

namespace BHive
{
	enum class ShaderUniformType
	{
		Bool, Int, Float, Float2, Float3, Float4, Vec2, Vec3, Color3, Color4, Vec4, Mat2, Mat3, Mat4, Sampler
	};

#define UNIFORM(name, displayName, classname, memberName, type)\
	{name, displayName, &(classname::memberName), type, -1}

#define SAMPLERUNIFORM(name, displayName, classname, memberName, type, index)\
	{name, displayName, &(classname::memberName), type, index}

	struct Uniform
	{
		const char* m_Name;
		const char* m_DisplayName;
		void* m_Value;
		ShaderUniformType m_Type;
		int m_SamplerIndex = -1;
	};

	struct ShaderUniforms
	{
		using Uniforms = std::vector<Uniform>;
		using Iterator = std::vector<Uniform>::iterator;

		Iterator begin() { return m_Uniforms.begin(); }
		Iterator end() { return m_Uniforms.end(); }

		void Add(std::initializer_list<Uniform> uniforms)
		{
			for (auto& uniform : uniforms)
			{
				m_Uniforms.push_back(uniform);
			}	
		}

		Uniforms m_Uniforms;
	};

	class BHive_API Shader : public Asset
	{
	public:
		Shader(const std::string& name): Asset(name){}
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		void SetUniform(const Uniform& uniform);

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

		std::string GetAssetType() const override { return "Shader"; }

		static Ref<Shader> Create(const WinPath& filePath);
		static Ref<Shader> Create(const BName& name, const BString& vertexSrc, const BString& fragmentSrc);
	
	};
}
