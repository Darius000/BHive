#ifndef SHADER_H
#define SHADER_H

#include "Core.h"
//#include "BHive/Assets/BResource.h"


namespace BHive
{
	class BHive_API Shader
	{
	public:
		Shader() = default;
		Shader(const FString&  vertexSrc, const FString&  fragmentSrc, bool isPath = false);
		~Shader();

		void Bind() const;
		void UnBind() const;

		void SetBool(const FString& name, bool value) const;
		void SetInt(const FString& name, int value) const;
		void SetFloat(const FString& name, float value) const;
		void SetVector2(const FString& name, float value0, float value1) const;
		void SetVector2(const FString& name, const glm::vec2 vec) const;
		void SetVector3(const FString& name, float value0, float value1, float value2) const;
		void SetVector3(const FString& name, const glm::vec3 vec) const;
		void SetVector4(const FString& name, float value0, float value1, float value2, float value3) const;
		void SetVector4(const FString& name, const glm::vec4 vec) const;
		void SetMatrix2(const FString& name, const glm::mat2 mat) const;
		void SetMatrix3(const FString& name, const glm::mat3 mat) const;
		void SetMatrix4(const FString& name, glm::mat4 mat) const;

	protected:
		bool CheckShaderStatus(unsigned int Shader);
		bool CheckLinkStatus(unsigned int ShaderProgram);

	private:	
		uint32 id;
		//FString vertexFilePath;
		//FString fragmentFilePath;
		FString vertexCode;
		FString fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		//friend class ShaderResource;
	};
}

#endif