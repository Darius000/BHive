#include "BHivePCH.h"
#include "Shader.h"
#include "BHive/Renderer/Renderer.h"
#include "BHive/Platforms/Opengl/OpenGLShader.h"

namespace BHive
{
	Ref<Shader> Shader::Create(const FString& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: BH_CORE_ASSERT(false, "RendererAPI::None currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filePath);
		}

		BH_CORE_ASSERT(false, "Unknown API");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const FString& name, const FString& vertexSrc, const FString& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: BH_CORE_ASSERT(false, "RendererAPI::None currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		BH_CORE_ASSERT(false, "Unknown API");
		return nullptr;
	}

	void ShaderLibrary::Add(const FString& name, const Ref<Shader>& shader)
	{
		BH_CORE_ASSERT(!Exists(name), "Shader Already Exists");
		m_Shaders[name] = shader;
	}
	
	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const FString& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const FString& name, const FString& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const FString& name)
	{
		BH_CORE_ASSERT(Exists(name), "Shader Doesn't Exists");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const FString& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}
