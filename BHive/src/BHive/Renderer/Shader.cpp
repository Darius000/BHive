#include "BHivePCH.h"
#include "Shader.h"
#include "BHive/Renderer/Renderer.h"
#include "BHive/Platforms/Opengl/OpenGLShader.h"

namespace BHive
{

	void Shader::SetUniform(const std::string& name, Uniform* uniform)
	{
		if(uniform == nullptr) return;

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
			default:
				break;
		}
	}

	void Shader::SetUniforms()
	{
		Bind();

		for (const auto& uniform : m_Unforms)
		{
			if(uniform.second)
				SetUniform(uniform.first, uniform.second.get());
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
}
