#pragma once

#include "Core.h"
#include <glad/glad.h>

namespace BHive
{
	class BHive_API Shader
	{
	public:
		Shader();
		Shader(const char* vertexPath, const char* fragmentPath);

		//the programs id
		unsigned int ID;

		//use/activate shader
		void Use();

		//uniform functions
		void SetBool(const std::string &name, bool value) const;
		void SetInt(const std::string &name, int value) const;
		void SetFloat(const std::string &name, float value) const;
		void SetVector2(const std::string &name, float value0, float value1) const;
		void SetVector2(const std::string &name, const glm::vec2 vec) const;
		void SetVector3(const std::string &name, float value0, float value1, float value2) const;
		void SetVector3(const std::string &name, const glm::vec3 vec) const;
		void SetVector4(const std::string &name, float value0, float value1, float value2, float value3) const;
		void SetVector4(const std::string &name, const glm::vec4 vec) const;
		void SetMatrix2(const std::string &name, const glm::mat2 mat) const;
		void SetMatrix3(const std::string &name, const glm::mat3 mat) const;
		void SetMatrix4(const std::string &name, glm::mat4 mat) const;

	protected:
		//check for shader errors
		void CheckShaderStatus(unsigned int Shader);

		//check for linking errors
		void CheckLinkStatus(unsigned int ShaderProgram);

	private:
		int success;
		char infoLog[512];
		int shaderFileType;
		const char* vertexFilePath;
	};
}
