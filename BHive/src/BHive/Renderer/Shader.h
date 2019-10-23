#pragma once

namespace BHive
{
	class BHive_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetBool(const FString& name, bool value) const = 0;
		virtual void SetInt(const FString& name, int value) const = 0;
		virtual void SetFloat(const FString& name, float value) const = 0;
		virtual void SetVector2(const FString& name, float value0, float value1) const = 0;
		virtual void SetVector2(const FString& name, const glm::vec2& vec) const = 0;
		virtual void SetVector3(const FString& name, float value0, float value1, float value2) const = 0;
		virtual void SetVector3(const FString& name, const glm::vec3& vec) const = 0;
		virtual void SetVector4(const FString& name, float value0, float value1, float value2, float value3) const = 0;
		virtual void SetVector4(const FString& name, const glm::vec4& vec) const = 0;
		virtual void SetMatrix2(const FString& name, const glm::mat2& mat) const = 0;
		virtual void SetMatrix3(const FString& name, const glm::mat3& mat) const = 0;
		virtual void SetMatrix4(const FString& name, const glm::mat4& mat) const = 0;

		virtual const FName& GetName() const = 0;

		static Ref<Shader> Create(const Path& filePath);
		static Ref<Shader> Create(const FName& name, const FString& vertexSrc, const FString& fragmentSrc);
	
	};

	class ShaderLibrary
	{
	public:
		void Add(const FName& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);
		
		Ref<Shader> Load(const Path& filePath);
		Ref<Shader> Load(const FName& name, const Path& filePath);

		Ref<Shader> Get(const FName& name);

		bool Exists(const FName& name) const;

	private:
		std::unordered_map<FName, Ref<Shader>> m_Shaders;
	};
}
