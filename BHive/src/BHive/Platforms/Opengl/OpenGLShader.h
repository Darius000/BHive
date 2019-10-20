#pragma once

#include "BHive/Renderer/Shader.h"


namespace BHive
{
	class BHive_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const Path&  filePath);
		OpenGLShader(const Name& name, const FString&  vertexSrc, const FString&  fragmentSrc);		
		~OpenGLShader();

		virtual void Bind() const;
		virtual void UnBind() const;

		void SetBool(const Name& name, bool value) const;
		void SetInt(const Name& name, int value) const;
		void SetFloat(const Name& name, float value) const;
		void SetVector2(const Name& name, float value0, float value1) const;
		void SetVector2(const Name& name, const glm::vec2& vec) const;
		void SetVector3(const Name& name, float value0, float value1, float value2) const;
		void SetVector3(const Name& name, const glm::vec3& vec) const;
		void SetVector4(const Name& name, float value0, float value1, float value2, float value3) const;
		void SetVector4(const Name& name, const glm::vec4& vec) const;
		void SetMatrix2(const Name& name, const glm::mat2& mat) const;
		void SetMatrix3(const Name& name, const glm::mat3& mat) const;
		void SetMatrix4(const Name& name, const glm::mat4& mat) const;


		virtual const Name& GetName() const override { return m_Name; };

	protected:
		bool CheckShaderStatus(uint32 Shader);
		bool CheckLinkStatus(uint32 ShaderProgram);

	private:
		FString ReadFile(const Path& filePath);
		std::unordered_map<uint32, FString> PreProccess(const FString& source);
		void Compile(std::unordered_map<uint32, FString>& sources);

	private:
		uint32 id;
		Name m_Name;
	};
}
