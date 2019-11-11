#pragma once

#include "BHive/Renderer/Shader.h"


namespace BHive
{
	class BHive_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const WinPath&  filePath);
		OpenGLShader(const BName& name, const BString&  vertexSrc, const BString&  fragmentSrc);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		void SetBool(const BString& name, bool value) const override;
		void SetInt(const BString& name, int value) const override;
		void SetFloat(const BString& name, float value) const override;
		void SetFloat2(const BString& name, float value0, float value1) const override;
		void SetVec2(const BString& name, const FVector2& vec) const override;
		void SetFloat3(const BString& name, float value0, float value1, float value2) const override;
		void SetVec3(const BString& name, const FVector3& vec) const override;
		void SetFloat4(const BString& name, float value0, float value1, float value2, float value3) const override;
		void SetVec4(const BString& name, const FVector4& vec) const override;
		void SetMat2(const BString& name, const glm::mat2& mat) const override;
		void SetMat3(const BString& name, const glm::mat3& mat) const override;
		void SetMat4(const BString& name, const glm::mat4& mat) const override;

		virtual const BName& GetName() const override { return m_Name; };

	protected:
		bool CheckShaderStatus(uint32 Shader);
		bool CheckLinkStatus(uint32 ShaderProgram);

	private:
		BString ReadFile(const WinPath& filePath);
		std::unordered_map<uint32, BString> PreProccess(const BString& source);
		void Compile(std::unordered_map<uint32, BString>& sources);

	private:
		uint32 id;
		BName m_Name;
	};
}
