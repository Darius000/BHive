#include "BHivePCH.h"
#include "Shader.h"
#include "BHive/Renderer/Renderer.h"
#include "BHive/Platforms/Opengl/OpenGLShader.h"

namespace BHive
{
	Ref<Shader> Shader::Create(const WinPath& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: BH_CORE_ASSERT(false, "RendererAPI::None currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filePath);
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
		}

		BH_CORE_ASSERT(false, "Unknown API");
		return nullptr;
	}

	void ShaderLibrary::Add(const BName& name, const Ref<Shader>& shader)
	{
		BH_CORE_ASSERT(!Exists(name), "Shader Already Exists");
		m_Shaders[name] = shader;
	}
	
	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const WinPath& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const BName& name, const WinPath& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const BName& name)
	{
		BH_CORE_ASSERT(Exists(name), "Shader Doesn't Exists");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const BName& name)
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

	void ShaderLibrary::UpdateShaderViewProjectionMatrices(glm::mat4 VP)
	{
		for (auto& s : m_Shaders)
		{
			s.second->Bind();
			s.second->SetMat4("u_ViewProjection", VP);
		}
	}

	std::unordered_map<BName, Ref<Shader>> ShaderLibrary::m_Shaders;
}
