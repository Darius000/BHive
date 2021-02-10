#include "BHivePCH.h"
#include "Material.h"
#include "Managers/AssetManagers.h"

namespace BHive
{

	Material::Material(Ref<Shader> shader) 
		:m_Shader(shader)
	{
		QueryUniformsFromShader();
	}

	Material::Material()
	{

	}

	void Material::Render()
	{
		if (m_Shader)
		{
			m_Shader->Bind();

			for (const auto& uniform : m_Parameters)
			{
				if (uniform.second)
					SetUniform(uniform.first, uniform.second.get());
			}
		}
	}

	void Material::QueryUniformsFromShader()
	{
		if(m_Parameters.empty() == false) m_Parameters.clear();

		if(!m_Shader) return;
		
		uint32 id = m_Shader->GetID();

		GLint numUniforms = 0;
		GLint maxUniformNameLength = 0;
		GLint numBlocks = 0;
		glGetProgramiv(id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformNameLength);
		glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &numUniforms);
		glGetProgramiv(id, GL_ACTIVE_UNIFORM_BLOCKS, &numBlocks);


		for (uint32 i = 0; i < (uint32)numUniforms; i++)
		{
			GLsizei length = 0;
			GLint size = 0;
			GLenum type;
			std::vector<GLchar> name(maxUniformNameLength);
			glGetActiveUniform(id, (GLint)i, (GLsizei)name.size(), &length, &size, &type, &name[0]);
			GLuint location = glGetUniformLocation(id, name.data());
			std::string finalName = name.data();

			size_t pos = finalName.find("material.");
			size_t texPos = finalName.find("textures.");
			size_t dotPos = finalName.find_first_of(".");
			if (pos != std::string::npos || texPos != std::string::npos)
			{
				Uniform* uniform = QueryUniformType(type);

				if (uniform != nullptr)
				{
					uniform->m_Location = (uint32)location;
					uniform->m_Length = (uint64)length;
					uniform->m_Size = (uint32)size;
					uniform->m_Name = name.data();
					uniform->m_DisplayName = finalName.substr(dotPos + 1);
					QueryUniformValue(id, uniform, type);

					//BH_CORE_TRACE("Uniform {0}, {1}, {2}, {3}", length, size, type, name.data());

					m_Parameters.insert({ name.data(), Scope<Uniform>(uniform) });
				}
			}
		}
	}

	void Material::QueryUniformValue(uint32 ShaderID, Uniform* uniform, GLenum type)
	{
		if(ShaderID == -1) return;

		const char* name = uniform->m_Name.c_str();
		int v = 0;
		switch (type)
		{
		case GL_BOOL:
			glGetUniformiv(ShaderID, glGetUniformLocation(ShaderID, name), &v);
			Cast<BoolUniform>(uniform)->m_Value = (bool)v;
			break;
		case GL_INT:
			glGetUniformiv(ShaderID, glGetUniformLocation(ShaderID, name), &Cast<IntUniform>(uniform)->m_Value);
			break;
		case GL_FLOAT:
			glGetUniformfv(ShaderID, glGetUniformLocation(ShaderID, name), &Cast<FloatUniform>(uniform)->m_Value);
			break;
		case GL_FLOAT_VEC2:
			glGetUniformfv(ShaderID, glGetUniformLocation(ShaderID, name), *Cast<Vector2Uniform>(uniform)->m_Value);
			break;
		case GL_FLOAT_VEC3:
			glGetUniformfv(ShaderID, glGetUniformLocation(ShaderID, name), *Cast<Vector3Uniform>(uniform)->m_Value);
			break;
		case GL_SAMPLER_2D:
		case GL_SAMPLER_CUBE:
			break;
		default:
			break;
		}

	};

	Uniform* Material::QueryUniformType(GLenum type)
	{
		switch (type)
		{
		case GL_BOOL:
			return new BoolUniform();
		case GL_INT:
			return new IntUniform();
		case GL_FLOAT:
			return new FloatUniform();
		case GL_FLOAT_VEC3:
			return new Vector3Uniform();
		case GL_FLOAT_VEC2:
			return new Vector2Uniform();
		case GL_SAMPLER_2D:
			return new SamplerUniform();
		case GL_SAMPLER_CUBE:
			return new SamplerCubeUniform();
		default:
			return nullptr;
		}
	}

	void Material::SetUniform(const std::string& name, Uniform* uniform)
	{
		if (uniform == nullptr) return;

		switch (uniform->GetType().UniformType)
		{
		case ShaderUniformTypes::Float:
			SetUniformImpl<ShaderUniformTypes::Float>(name, uniform);
			break;
		case ShaderUniformTypes::Bool:
			SetUniformImpl<ShaderUniformTypes::Bool>(name, uniform);
			break;
		case ShaderUniformTypes::Int:
			SetUniformImpl<ShaderUniformTypes::Int>(name, uniform);
			break;
		case ShaderUniformTypes::Vec2:
			SetUniformImpl<ShaderUniformTypes::Vec2>(name, uniform);
			break;
		case ShaderUniformTypes::Vec3:
			SetUniformImpl<ShaderUniformTypes::Vec3>(name, uniform);
			break;
		case ShaderUniformTypes::Sampler:
			SetUniformImpl<ShaderUniformTypes::Sampler>(name, uniform);
			break;
		case ShaderUniformTypes::SamplerCube:
			SetUniformImpl<ShaderUniformTypes::SamplerCube>(name, uniform);
			break;
		default:
			break;
		}
	}

}