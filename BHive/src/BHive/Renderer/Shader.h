#pragma once

namespace BHive
{
	class BHive_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetBool(const BString& name, bool value) const = 0;
		virtual void SetInt(const BString& name, int value) const = 0;
		virtual void SetFloat(const BString& name, float value) const = 0;
		virtual void SetFloat2(const BString& name, float value0, float value1) const = 0;
		virtual void SetVec2(const BString& name, const glm::vec2& vec) const = 0;
		virtual void SetFloat3(const BString& name, float value0, float value1, float value2) const = 0;
		virtual void SetVec3(const BString& name, const glm::vec3& vec) const = 0;
		virtual void SetFloat4(const BString& name, float value0, float value1, float value2, float value3) const = 0;
		virtual void SetVec4(const BString& name, const glm::vec4& vec) const = 0;
		virtual void SetMat2(const BString& name, const glm::mat2& mat) const = 0;
		virtual void SetMat3(const BString& name, const glm::mat3& mat) const = 0;
		virtual void SetMat4(const BString& name, const glm::mat4& mat) const = 0;

		virtual const BName& GetName() const = 0;

		static Ref<Shader> Create(const Path& filePath);
		static Ref<Shader> Create(const BName& name, const BString& vertexSrc, const BString& fragmentSrc);
	
	};

	class ShaderLibrary
	{
	public:
		static void Add(const BName& name, const Ref<Shader>& shader);
		static void Add(const Ref<Shader>& shader);
		
		static Ref<Shader> Load(const Path& filePath);
		static Ref<Shader> Load(const BName& name, const Path& filePath);

		static Ref<Shader> Get(const BName& name);
		static std::unordered_map<BName, Ref<Shader>> GetShaders() { return m_Shaders; }

		static bool Exists(const BName& name);

	private:
		static std::unordered_map<BName, Ref<Shader>> m_Shaders;
	public:
		static void UpdateShaderViewProjectionMatrices(glm::mat4 VP);
	};
}
