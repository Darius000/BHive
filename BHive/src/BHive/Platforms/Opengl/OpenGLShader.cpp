#include "BHivePCH.h"
#include "OpenGLShader.h"
#include "glad/glad.h"


namespace BHive
{
	static GLenum ShaderTypeFromString(const BString& type)
	{
		if (type == "VERTEX") 
			return GL_VERTEX_SHADER;
		if (type == "FRAGMENT" || type == "PIXEL")
			return GL_FRAGMENT_SHADER;

		BH_CORE_ASSERT(false, "Unkown shader type!");

		return 0;
	}

	OpenGLShader::OpenGLShader(const WinPath& filePath)
		:Shader("")
	{
		m_Name = filePath.GetName();

		BString source = ReadFile(filePath);	
		auto shaderSources = PreProccess(source);
		Compile(shaderSources);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const BString&  vertexSrc, const BString&  fragmentSrc)
		:Shader(name)
	{
		std::unordered_map<GLenum, BString> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}

	

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(id);
	}

	void OpenGLShader::SetBool(const BString& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(id, *name), (int)value);
	}

	void OpenGLShader::SetInt(const BString& name, int value) const
	{
		glUniform1i(glGetUniformLocation(id, *name), value);
	}

	void OpenGLShader::SetFloat(const BString& name, float value) const
	{
		glUniform1f(glGetUniformLocation(id, *name), value);
	}

	void OpenGLShader::SetFloat2(const BString& name, float value0, float value1) const
	{
		glUniform2f(glGetUniformLocation(id, *name), value0, value1);
	}

	void OpenGLShader::SetVec2(const BString& name, const FVector2& vec) const
	{
		glUniform2fv(glGetUniformLocation(id, *name), 1, *vec);
	}

	void OpenGLShader::SetFloat3(const BString& name, float value0, float value1, float value2) const
	{
		glUniform3f(glGetUniformLocation(id, *name), value0, value1, value2);
	}

	void OpenGLShader::SetVec3(const BString& name, const FVector3& vec) const
	{
		glUniform3fv(glGetUniformLocation(id, *name), 1, *vec);
	}

	void OpenGLShader::SetFloat4(const BString& name, float value0, float value1, float value2, float value3) const
	{
		glUniform4f(glGetUniformLocation(id, *name), value0, value1, value2, value3);
	}

	void OpenGLShader::SetVec4(const BString& name, const FVector4& vec) const
	{
		glUniform4fv(glGetUniformLocation(id, *name), 1, *vec);
	}

	void OpenGLShader::SetMat2(const BString& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(id, *name), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::SetMat3(const BString& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(id, *name), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::SetMat4(const BString& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(id, *name), 1, GL_FALSE, glm::value_ptr(mat));
	}

	bool OpenGLShader::CheckShaderStatus(uint32 Shader)
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

			BH_CORE_ERROR("File: {0} , {1} ERROR::SHADER::COMPILATION_FAILED\n {2}", GetName(), shaderType, infoLog.data());
		}

		return success;
	}

	bool OpenGLShader::CheckLinkStatus(uint32 ShaderProgram)
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

	BString OpenGLShader::ReadFile(const WinPath& filePath)
	{
		BString result;
	
		std::ifstream shaderFile(*filePath, std::ios::binary | std::ios::in);

		if (shaderFile)
		{
			shaderFile.seekg(0, std::ios::end);
			result.resize(shaderFile.tellg());

			size_t size = result.size();

			shaderFile.seekg(0, std::ios::beg);
			shaderFile.read(&result[0], size);
			shaderFile.close();

			BH_CORE_TRACE("SHADER:: {0} :: FILE_LOADED_SUCCESFULLY!", GetName());
		}
		else
		{
			BH_CORE_ERROR("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ! '{0}'", *filePath);
		}

		return result;
	}

	std::unordered_map<uint32, BString> OpenGLShader::PreProccess(const BString& source)
	{
		std::unordered_map<uint32, BString> shaderSources;

		const ANSICHAR* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(*typeToken, 0);
		
		while (pos != BString::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			BH_CORE_ASSERT(eol != BString::npos, "Syntax Error");
			size_t begin = pos + typeTokenLength + 1;
			BString type = source.substr(begin, eol - begin);
			BH_CORE_ASSERT(ShaderTypeFromString(type), "Invalid Shader Type Specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos,
				pos - (nextLinePos == BString::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(std::unordered_map<uint32, BString>& sources)
	{
		GLuint program = glCreateProgram();
		BH_CORE_ASSERT(sources.size() <= 2, "Only support 2  shaders for now!");

		std::array<uint32, 2> glShaderIDs;

		uint32 index = 0;
		for (auto& kv : sources)
		{
			GLenum shaderType = kv.first;
			const BString& source = kv.second;

			GLuint shader = glCreateShader(shaderType);

			const GLchar* sourceCode = *source;
			glShaderSource(shader, 1, &sourceCode, nullptr);
			glCompileShader(shader);

			if (CheckShaderStatus(shader) == false)
			{
				glDeleteShader(shader);

				//BH_CORE_ASSERT(false, "shader compile error!");
				break;
			}	

			glAttachShader(program, shader);
			glShaderIDs[index++] = shader;
		}	
		
		glLinkProgram(program);

		if (CheckLinkStatus(program) == false)
		{
			for (auto shaderID : glShaderIDs)
			{
				glDeleteShader(shaderID);
			}
#ifdef BH_DEBUG		
			BH_CORE_ASSERT(false, "Shader linking error!");
#endif
			return;
		}

		for (auto shaderID : glShaderIDs)
		{
			glDetachShader(program, shaderID);
		}

		id = program;
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(id);
	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}
}
