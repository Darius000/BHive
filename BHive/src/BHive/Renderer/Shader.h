#pragma once

namespace BHive
{
	class BHive_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual const Name& GetName() const = 0;

		static Ref<Shader> Create(const Path& filePath);
		static Ref<Shader> Create(const Name& name, const FString& vertexSrc, const FString& fragmentSrc);
	
	};

	class ShaderLibrary
	{
	public:
		void Add(const Name& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);
		
		Ref<Shader> Load(const Path& filePath);
		Ref<Shader> Load(const Name& name, const Path& filePath);

		Ref<Shader> Get(const Name& name);

		bool Exists(const Name& name) const;

	private:
		std::unordered_map<Name, Ref<Shader>> m_Shaders;
	};
}
