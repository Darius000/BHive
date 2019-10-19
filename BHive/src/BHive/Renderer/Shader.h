#pragma once

namespace BHive
{
	class BHive_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual const FString& GetName() const = 0;

		static Ref<Shader> Create(const FString& filePath);
		static Ref<Shader> Create(const FString& name, const FString& vertexSrc, const FString& fragmentSrc);
	
	};

	class ShaderLibrary
	{
	public:
		void Add(const FString& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);
		
		Ref<Shader> Load(const FString& filePath);
		Ref<Shader> Load(const FString& name, const FString& filePath);

		Ref<Shader> Get(const FString& name);

		bool Exists(const FString& name) const;

	private:
		std::unordered_map<FName, Ref<Shader>> m_Shaders;
	};
}
