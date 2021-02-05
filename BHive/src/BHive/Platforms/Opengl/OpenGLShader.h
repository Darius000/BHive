#pragma once

#include "BHive/Renderer/Shader.h"


namespace BHive
{
	class BHive_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader() = default;
		OpenGLShader(const WinPath&  filePath);
		OpenGLShader(const std::string& name, const BString&  vertexSrc, const BString&  fragmentSrc);
		~OpenGLShader();

		void Bind() const override;
		void UnBind() const override;

		void QueryUniforms(uint32 shader);
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
		uint32& GetID()  override { return id; }

		inline void GetUniformValue(Uniform* uniform, GLenum type);

	protected:
		bool CheckShaderStatus(uint32 Shader);
		bool CheckLinkStatus(uint32 ShaderProgram);

	private:
		BString ReadFile(const WinPath& filePath);
		void PreProccess(const BString& source);
		void Compile() override;

	private:
		uint32 id;
	};

	inline void OpenGLShader::GetUniformValue(Uniform* uniform, GLenum type)
	{
		
		const char* name = uniform->m_Name.c_str();
		int v = 0;
		switch (type)
		{
		case GL_BOOL:
			glGetUniformiv(id, glGetUniformLocation(id, name), &v);
			Cast<BoolUniform>(uniform)->m_Value = (bool)v;
			break;
		case GL_INT:
			glGetUniformiv(id, glGetUniformLocation(id, name), &Cast<IntUniform>(uniform)->m_Value);
			break;
		case GL_FLOAT:
			glGetUniformfv(id, glGetUniformLocation(id, name), &Cast<FloatUniform>(uniform)->m_Value);
			break;
		case GL_FLOAT_VEC2:
			glGetUniformfv(id, glGetUniformLocation(id, name), *Cast<Vector2Uniform>(uniform)->m_Value);
			break;
		case GL_FLOAT_VEC3:
			glGetUniformfv(id, glGetUniformLocation(id, name), *Cast<Vector3Uniform>(uniform)->m_Value);
			break;
		case GL_SAMPLER_2D:
			break;
		default:
			break;
		}
		
	};
}
