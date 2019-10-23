#pragma once

#include "BHive/Renderer/Shader.h"


namespace BHive
{
	class BHive_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const Path&  filePath);
		OpenGLShader(const FName& name, const FString&  vertexSrc, const FString&  fragmentSrc);
		~OpenGLShader();

		virtual void Bind() const;
		virtual void UnBind() const;

		void SetBool(const FString& name, bool value) const override;
		void SetInt(const FString& name, int value) const override;
		void SetFloat(const FString& name, float value) const override;
		void SetVector2(const FString& name, float value0, float value1) const override;
		void SetVector2(const FString& name, const glm::vec2& vec) const override;
		void SetVector3(const FString& name, float value0, float value1, float value2) const override;
		void SetVector3(const FString& name, const glm::vec3& vec) const override;
		void SetVector4(const FString& name, float value0, float value1, float value2, float value3) const override;
		void SetVector4(const FString& name, const glm::vec4& vec) const override;
		void SetMatrix2(const FString& name, const glm::mat2& mat) const override;
		void SetMatrix3(const FString& name, const glm::mat3& mat) const override;
		void SetMatrix4(const FString& name, const glm::mat4& mat) const override;

		virtual const FName& GetName() const override { return m_Name; };

	protected:
		bool CheckShaderStatus(uint32 Shader);
		bool CheckLinkStatus(uint32 ShaderProgram);

	private:
		FString ReadFile(const Path& filePath);
		std::unordered_map<uint32, FString> PreProccess(const FString& source);
		void Compile(std::unordered_map<uint32, FString>& sources);

	private:
		uint32 id;
		FName m_Name;
	};
}
