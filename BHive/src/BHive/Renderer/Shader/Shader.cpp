#include "BHivePCH.h"
#include "Shader.h"
#include "glad/glad.h"


namespace BHive
{
	Shader::Shader(const FString&  vertexSrc, const FString&  fragmentSrc, bool isPath)
		:Shader()
	{
		if (isPath == true)
		{
			//vertexFilePath = vertexSrc;
			//fragmentFilePath = fragmentSrc;

			//ensure fstream objects can throw exceptions
			vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

			try
			{
				vShaderFile.open(*vertexSrc);
				fShaderFile.open(*fragmentSrc);
				std::stringstream vShaderStream, fShaderStream;

				//read file's buffer contents into streams
				vShaderStream << vShaderFile.rdbuf();
				fShaderStream << fShaderFile.rdbuf();

				//close file handlers
				vShaderFile.close();
				fShaderFile.close();

				//convert stream into string
				vertexCode = vShaderStream.str().c_str();
				fragmentCode = fShaderStream.str().c_str();

				//std::cout << vertexFilePath << " SHADER::FILE_LOADED_SUCCESFULLY" << std::endl;

				BH_CORE_ASSERT(true, "SHADER::FILE_LOADED_SUCCESFULLY!");
			}
			catch (std::ifstream::failure e)
			{
				//std::cout << vertexFilePath << " ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;

				BH_CORE_ASSERT(false, "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ!");
			}
		}
		else
		{
			vertexCode = vertexSrc;
			fragmentCode = fragmentSrc;
		}

		const char* vShaderCode = *vertexCode;
		const char* fShaderCode = *fragmentCode;

		unsigned int vertexShader = 0, fragmentShader = 0;

		//vertex shader
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vShaderCode, NULL);
		glCompileShader(vertexShader);

		//fragment shader
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
		glCompileShader(fragmentShader);

		//check for compile errors
		if (CheckShaderStatus(vertexShader) == false)
		{
			glDeleteShader(vertexShader);

			BH_CORE_ASSERT(false, "Vertex compile error!");
			return;
		}

		if (CheckShaderStatus(fragmentShader) == false)
		{
			glDeleteShader(fragmentShader);

			BH_CORE_ASSERT(false, "Fragment compile error!");
			return;
		}

		//create and attach shaders
		id = glCreateProgram();
		glAttachShader(id, vertexShader);
		glAttachShader(id, fragmentShader);
		glLinkProgram(id);

		//check for shader link errors
		if (CheckLinkStatus(id) == false) 
		{
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			BH_CORE_ASSERT(false, "Shader linking error!");
			return;
		}

		//don't need shaders anymore
		glDetachShader(id, vertexShader);
		glDetachShader(id, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(id);
	}

	void Shader::SetBool(const FString& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(id, *name), (int)value);
	}

	void Shader::SetInt(const FString& name, int value) const
	{
		glUniform1i(glGetUniformLocation(id, *name), value);
	}

	void Shader::SetFloat(const FString& name, float value) const
	{
		glUniform1f(glGetUniformLocation(id, *name), value);
	}

	void Shader::SetVector2(const FString& name, float value0, float value1) const
	{
		glUniform2f(glGetUniformLocation(id, *name), value0, value1);
	}

	void Shader::SetVector2(const FString& name, const glm::vec2 vec) const
	{
		glUniform2fv(glGetUniformLocation(id, *name), 1, glm::value_ptr(vec));
	}

	void Shader::SetVector3(const FString& name, float value0, float value1, float value2) const
	{
		glUniform3f(glGetUniformLocation(id, *name), value0, value1, value2);
	}

	void Shader::SetVector3(const FString& name, const glm::vec3 vec) const
	{
		glUniform3fv(glGetUniformLocation(id, *name), 1, glm::value_ptr(vec));
	}

	void Shader::SetVector4(const FString& name, float value0, float value1, float value2, float value3) const
	{
		glUniform4f(glGetUniformLocation(id, *name), value0, value1, value2, value3);
	}

	void Shader::SetVector4(const FString& name, const glm::vec4 vec) const
	{
		glUniform4fv(glGetUniformLocation(id, *name), 1, glm::value_ptr(vec));
	}

	void Shader::SetMatrix2(const FString& name, const glm::mat2 mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(id, *name), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void Shader::SetMatrix3(const FString& name, const glm::mat3 mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(id, *name), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void Shader::SetMatrix4(const FString& name, glm::mat4 mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(id, *name), 1, GL_FALSE, glm::value_ptr(mat));
	}

	bool Shader::CheckShaderStatus(unsigned int Shader)
	{
		int32 success;
		int32 fileType;

		glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
		glGetShaderiv(Shader, GL_SHADER_TYPE, &fileType);

		if (!success)
		{
			int32 maxLength = 0;
			glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<ANSICHAR> infoLog(maxLength);

			glGetShaderInfoLog(Shader, maxLength, &maxLength, infoLog.data());

			const char* shaderType = "";

			if (fileType == GL_VERTEX_SHADER)
			{
				shaderType = "VERTEX";
			}
			else if (fileType == GL_FRAGMENT_SHADER)
			{
				shaderType = "FRAGMENT";
			}

			BH_CORE_ERROR("{0} ERROR::SHADER::COMPILATION_FAILED\n {1}" , shaderType, infoLog.data() );
		}

		return success;
	}

	bool Shader::CheckLinkStatus(unsigned int ShaderProgram)
	{
		int32 success;

		glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			int32 maxLength = 0;
			glGetShaderiv(ShaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<ANSICHAR> infoLog(maxLength);

			glGetProgramInfoLog(ShaderProgram, maxLength, &maxLength, infoLog.data());
			BH_CORE_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED\n {0}", infoLog.data());
		}

		return success;
	}

	void Shader::Bind() const
	{
		glUseProgram(id);
	}

	void Shader::UnBind() const
	{
		glUseProgram(0);
	}
}
