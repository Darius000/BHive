#include "BHivePCH.h"
#include "Shader.h"
#include "BHive/Renderer/Renderer.h"
#include "BHive/Platforms/Opengl/OpenGLShader.h"

namespace BHive
{

	void Shader::SetUniform(const Uniform& uniform)
	{
		const char* name = uniform.m_Name;
		ShaderUniformType type = uniform.m_Type;
		void* value = uniform.m_Value;

		switch (type)
		{
		case ShaderUniformType::Bool:
			SetBool(name, *reinterpret_cast<bool*>(value));
			break;
		case ShaderUniformType::Int:
			SetInt(name, *reinterpret_cast<int*>(value));
			break;
		case ShaderUniformType::Float:
			SetFloat(name, *reinterpret_cast<float*>(value));
			break;
		case ShaderUniformType::Float2:
			{
				FVector2 v2 = *reinterpret_cast<FVector2*>(value);
				SetFloat2(name, v2.x, v2.y);
			}
			break;
		case ShaderUniformType::Float3:				
			{
				FVector3 v3 = *reinterpret_cast<FVector3*>(value);
				SetFloat3(name, v3.x, v3.y, v3.z);
			}
			break;
		case ShaderUniformType::Float4:
			{
				FVector4 v4 = *reinterpret_cast<FVector4*>(value);
				SetFloat4(name, v4.x, v4.y, v4.z, v4.w);
			}
			break;
		
		case ShaderUniformType::Color3:
			{
				LinearColor3 c3 = *reinterpret_cast<LinearColor3*>(value);
				SetFloat3(name, c3.r, c3.g, c3.b);
			}
			break;
		case ShaderUniformType::Color4:
			{
				LinearColor4 c4 = *reinterpret_cast<LinearColor4*>(value);
				SetFloat4(name, c4.r, c4.g, c4.b, c4.a);
			}
			break;
		case ShaderUniformType::Vec2:
			SetVec2(name, *reinterpret_cast<FVector2*>(value));
			break;
		case ShaderUniformType::Vec3:
			SetVec3(name, *reinterpret_cast<FVector3*>(value));
			break;
		case ShaderUniformType::Vec4:
			SetVec4(name, *reinterpret_cast<FVector4*>(value));
			break;
		case ShaderUniformType::Mat2:
			SetMat2(name, *reinterpret_cast<glm::mat2*>(value));
			break;
		case ShaderUniformType::Mat3:
			SetMat3(name, *reinterpret_cast<glm::mat3*>(value));
			break;
		case ShaderUniformType::Mat4:
			SetMat4(name, *reinterpret_cast<glm::mat4*>(value));
			break;
		case ShaderUniformType::Sampler:
		{
			Ref<Texture2D> tex = *reinterpret_cast<Ref<Texture2D>*>(value);
			if(tex)
			{ 
				tex->Bind(uniform.m_SamplerIndex);
				SetInt(name + std::string(".texture"), uniform.m_SamplerIndex );
				SetBool(name + std::string(".set"), true);
			}
			else
			{
				SetInt(name + std::string(".texture"), 0);
				SetBool(name + std::string(".set"), false);
			}
		}	
		break;
		default:
			break;
		}
	}

	Ref<Shader> Shader::Create(const WinPath& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: BH_CORE_ASSERT(false, "RendererAPI::None currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filePath);
		case RendererAPI::API::DirectX: break;
		}

		BH_CORE_ASSERT(false, "Unknown API");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const BName& name, const BString& vertexSrc, const BString& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: BH_CORE_ASSERT(false, "RendererAPI::None currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		case RendererAPI::API::DirectX: break;
		}

		BH_CORE_ASSERT(false, "Unknown API");
		return nullptr;
	}

	void Shader::AddAttribute(UniformAttribute* attribute)
	{
		m_UniformAttribues.push_back(Scope<UniformAttribute>(attribute));
	}


	void Shader::RemoveAttribute(const std::string name)
	{
		auto it = std::find_if(m_UniformAttribues.begin(), m_UniformAttribues.end(), [name](Scope<UniformAttribute>& attr)
		{
			if (attr->m_Name == name)
			{
				return true;
			}

			return false;
		});

		m_UniformAttribues.erase(it);
	}

	void Shader::RemoveAttribute(unsigned int index)
	{
		auto it = std::find(m_UniformAttribues.begin(), m_UniformAttribues.end(), m_UniformAttribues[index]);
		m_UniformAttribues.erase(it);
	}

}
