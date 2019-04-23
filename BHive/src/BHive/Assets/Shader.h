#pragma once

#include "Core.h"
#include "BResource.h"


namespace BHive
{
	class BHive_API Shader : public BResource
	{
	public:
		Shader();
		Shader(const String&  vertexPath, const String&  fragmentPath);

		//the programs id
		unsigned int ID;

		//use/activate shader
		void Use();

		//uniform functions
		void SetBool(const String& name, bool value) const;
		void SetInt(const String& name, int value) const;
		void SetFloat(const String& name, float value) const;
		void SetVector2(const String& name, float value0, float value1) const;
		void SetVector2(const String& name, const glm::vec2 vec) const;
		void SetVector3(const String& name, float value0, float value1, float value2) const;
		void SetVector3(const String& name, const glm::vec3 vec) const;
		void SetVector4(const String& name, float value0, float value1, float value2, float value3) const;
		void SetVector4(const String& name, const glm::vec4 vec) const;
		void SetMatrix2(const String& name, const glm::mat2 mat) const;
		void SetMatrix3(const String& name, const glm::mat3 mat) const;
		void SetMatrix4(const String& name, glm::mat4 mat) const;

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
