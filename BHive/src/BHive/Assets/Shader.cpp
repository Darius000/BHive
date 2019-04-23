#include "BHivePCH.h"
#include "Shader.h"
#include "glad/glad.h"


namespace BHive
{
	Shader::Shader()
	{

	}


	Shader::Shader(const String&  vertexPath, const String&  fragmentPath)
		:Shader()
	{
		vertexFilePath = vertexPath.c_str();

		//get source code form filepath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		//ensure fstream objects can throw exceptions
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;

			//read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			//close file handlers
			vShaderFile.close();
			fShaderFile.close();

			//convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

			std::cout << vertexFilePath << " SHADER::FILE_LOADED_SUCCESFULLY" << std::endl;
		}
		catch (std::ifstream::failure e)
		{
			std::cout << vertexFilePath << " ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		unsigned int vertex = 0, fragment = 0;

		//vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		//fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		//print compile errors
		CheckShaderStatus(vertex);
		CheckShaderStatus(fragment);

		//create and attach shaders
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		//print shader link errors
		CheckLinkStatus(ID);

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void Shader::Use()
	{
		glUseProgram(ID);
	}

	void Shader::SetBool(const String& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}

	void Shader::SetInt(const String& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void Shader::SetFloat(const String& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	void Shader::SetVector2(const String& name, float value0, float value1) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), value0, value1);
	}

	void Shader::SetVector2(const String& name, const glm::vec2 vec) const
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(vec));
	}

	void Shader::SetVector3(const String& name, float value0, float value1, float value2) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), value0, value1, value2);
	}

	void Shader::SetVector3(const String& name, const glm::vec3 vec) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(vec));
	}

	void Shader::SetVector4(const String& name, float value0, float value1, float value2, float value3) const
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), value0, value1, value2, value3);
	}

	void Shader::SetVector4(const String& name, const glm::vec4 vec) const
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(vec));
	}

	void Shader::SetMatrix2(const String& name, const glm::mat2 mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void Shader::SetMatrix3(const String& name, const glm::mat3 mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void Shader::SetMatrix4(const String& name, glm::mat4 mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void Shader::CheckShaderStatus(unsigned int Shader)
	{
		glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
		glGetShaderiv(Shader, GL_SHADER_TYPE, &shaderFileType);

		if (!success)
		{
			glGetShaderInfoLog(Shader, 512, NULL, infoLog);

			const char* shaderType = "";

			if (shaderFileType == GL_VERTEX_SHADER)
			{
				shaderType = "VERTEX";
			}
			else if (shaderFileType == GL_FRAGMENT_SHADER)
			{
				shaderType = "FRAGMENT";
			}

			std::cout << vertexFilePath << " ERROR::SHADER::" << shaderType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}

	void Shader::CheckLinkStatus(unsigned int ShaderProgram)
	{
		glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ShaderProgram, 512, NULL, infoLog);
			std::cout << vertexFilePath << " ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
	}
}
