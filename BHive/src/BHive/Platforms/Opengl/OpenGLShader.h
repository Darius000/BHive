#pragma once

#include "BHive/Renderer/Shader.h"


namespace BHive
{
	class BHive_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const FString&  filePath);
		OpenGLShader(const FString& name, const FString&  vertexSrc, const FString&  fragmentSrc);		
		~OpenGLShader();

		virtual void Bind() const;
		virtual void UnBind() const;

		void SetBool(const FString& name, bool value) const;
		void SetInt(const FString& name, int value) const;
		void SetFloat(const FString& name, float value) const;
		void SetVector2(const FString& name, float value0, float value1) const;
		void SetVector2(const FString& name, const glm::vec2& vec) const;
		void SetVector3(const FString& name, float value0, float value1, float value2) const;
		void SetVector3(const FString& name, const glm::vec3& vec) const;
		void SetVector4(const FString& name, float value0, float value1, float value2, float value3) const;
		void SetVector4(const FString& name, const glm::vec4& vec) const;
		void SetMatrix2(const FString& name, const glm::mat2& mat) const;
		void SetMatrix3(const FString& name, const glm::mat3& mat) const;
		void SetMatrix4(const FString& name, const glm::mat4& mat) const;


		virtual const FString& GetName() const override { return m_Name; };

	protected:
		bool CheckShaderStatus(unsigned int Shader);
		bool CheckLinkStatus(unsigned int ShaderProgram);

	private:
		FString ReadFile(const FString& filePath);
		std::unordered_map<uint32, FString> PreProccess(const FString& source);
		void Compile(std::unordered_map<uint32, FString>& sources);

	private:
		uint32 id;
		FString m_Name;
	};
}
