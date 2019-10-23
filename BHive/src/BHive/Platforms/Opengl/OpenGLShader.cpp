#include "BHivePCH.h"
#include "OpenGLShader.h"
#include "glad/glad.h"


namespace BHive
{
	static GLenum ShaderTypeFromString(const FString& type)
	{
		if (type == "VERTEX") 
			return GL_VERTEX_SHADER;
		if (type == "FRAGMENT" || type == "PIXEL")
			return GL_FRAGMENT_SHADER;

		BH_CORE_ASSERT(false, "Unkown shader type!");

		return 0;
	}

	OpenGLShader::OpenGLShader(const Path& filePath)
	{
		FString source = ReadFile(filePath);	
		auto shaderSources = PreProccess(source);
		Compile(shaderSources);

		auto lastLash = filePath.Find_Last_Of("/");
		lastLash = lastLash == filePath.Size() ? 0 : lastLash + 1;
		auto lastDot = filePath.Find(".", 0);
		auto count = lastDot == filePath.Size() ? filePath.Size() - lastLash : lastDot - lastLash;

		FString fileName;
		filePath.GetSubString(lastLash, count, fileName);
		m_Name.FromString(fileName);
	}

	OpenGLShader::OpenGLShader(const FName& name, const FString&  vertexSrc, const FString&  fragmentSrc)
	{
		std::unordered_map<GLenum, FString> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}

	

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(id);
	}

	void OpenGLShader::SetBool(const FString& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(id, *name), (int)value);
	}

	void OpenGLShader::SetInt(const FString& name, int value) const
	{
		glUniform1i(glGetUniformLocation(id, *name), value);
	}

	void OpenGLShader::SetFloat(const FString& name, float value) const
	{
		glUniform1f(glGetUniformLocation(id, *name), value);
	}

	void OpenGLShader::SetVector2(const FString& name, float value0, float value1) const
	{
		glUniform2f(glGetUniformLocation(id, *name), value0, value1);
	}

	void OpenGLShader::SetVector2(const FString& name, const glm::vec2& vec) const
	{
		glUniform2fv(glGetUniformLocation(id, *name), 1, glm::value_ptr(vec));
	}

	void OpenGLShader::SetVector3(const FString& name, float value0, float value1, float value2) const
	{
		glUniform3f(glGetUniformLocation(id, *name), value0, value1, value2);
	}

	void OpenGLShader::SetVector3(const FString& name, const glm::vec3& vec) const
	{
		glUniform3fv(glGetUniformLocation(id, *name), 1, glm::value_ptr(vec));
	}

	void OpenGLShader::SetVector4(const FString& name, float value0, float value1, float value2, float value3) const
	{
		glUniform4f(glGetUniformLocation(id, *name), value0, value1, value2, value3);
	}

	void OpenGLShader::SetVector4(const FString& name, const glm::vec4& vec) const
	{
		glUniform4fv(glGetUniformLocation(id, *name), 1, glm::value_ptr(vec));
	}

	void OpenGLShader::SetMatrix2(const FString& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(id, *name), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::SetMatrix3(const FString& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(id, *name), 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::SetMatrix4(const FString& name, const glm::mat4& mat) const
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

			BH_CORE_ERROR("{0} ERROR::SHADER::COMPILATION_FAILED\n {1}", shaderType, infoLog.data());
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

	FString OpenGLShader::ReadFile(const Path& filePath)
	{
		FString result;
	
		std::ifstream shaderFile(*filePath, std::ios::binary | std::ios::in);

		if (shaderFile)
		{
			shaderFile.seekg(0, std::ios::end);
			result.Resize((uint32)shaderFile.tellg());

			int32 size = (int32)result.Size();

			shaderFile.seekg(0, std::ios::beg);
			shaderFile.read(&result[0], size);
			shaderFile.close();

			BH_CORE_ASSERT(true, "SHADER::FILE_LOADED_SUCCESFULLY!");
		}
		else
		{
			BH_CORE_ERROR("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ! '{0}'", *filePath);
		}

		return result;
	}

	std::unordered_map<uint32, FString> OpenGLShader::PreProccess(const FString& source)
	{
		std::unordered_map<uint32, FString> shaderSources;

		FString typeToken = "#type";
		uint32 typeTokenLength = typeToken.Size();

		FString vCode, fCode, type;

		uint32 i = source.Find(*typeToken, 0);
		uint32 j = source.Find("\n", i + typeTokenLength);
		//FString vertex = source.SubString(i + typeTokenLength, j);
		source.GetSubString(i + typeTokenLength + 1, j - 2, type);

		uint32 r = source.Find(*typeToken, j);
		source.GetSubString(j, r - 1, vCode);
		shaderSources[ShaderTypeFromString(type)] = vCode;

		uint32 s = source.Find("\n", r + typeTokenLength);
		//FString fragment = source.SubString(r + typeTokenLength, s);
		uint32 e = source.Find("\n", s);
		source.GetSubString(e, source.Size(), fCode);
		source.GetSubString(r + typeTokenLength + 1, s - 2, type);
		
		shaderSources[ShaderTypeFromString(type)] = fCode;

		/*while (pos != FString::npos)
		{
			size_t eol = source.Find_First_Of("\r\n", pos);
			BH_CORE_ASSERT(eol != FString::npos, "Syntax Error");
			size_t begin = pos + typeTokenLength + 1;
			FString type = source.SubString(begin, eol - begin);
			BH_CORE_ASSERT(ShaderTypeFromString(type), "Invalid Shader Type Specified");

			size_t nextLinePos = source.Find_First_Not_Of("\r\n", eol);
			pos = source.Find(typeToken);
			shaderSources[ShaderTypeFromString(type)] = source.SubString(nextLinePos,
				pos - (nextLinePos == FString::npos ? source.Size() - 1 : nextLinePos));
		}*/

		return shaderSources;
	}

	void OpenGLShader::Compile(std::unordered_map<uint32, FString>& sources)
	{
		GLuint program = glCreateProgram();
		BH_CORE_ASSERT(sources.size() <= 2, "Only support 2  shaders for now!");

		std::array<uint32, 2> glShaderIDs;

		uint32 index = 0;
		for (auto& kv : sources)
		{
			GLenum shaderType = kv.first;
			const FString& source = kv.second;

			GLuint shader = glCreateShader(shaderType);

			const GLchar* sourceCode = *source;
			glShaderSource(shader, 1, &sourceCode, NULL);
			glCompileShader(shader);

			if (CheckShaderStatus(shader) == false)
			{
				glDeleteShader(shader);

				BH_CORE_ASSERT(false, "shader compile error!");
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
			
			BH_CORE_ASSERT(false, "Shader linking error!");
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
