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

	bool Shader::IsExtensionSupported(const BString ext)
	{
		return std::find(s_SupportedExtension.begin(), s_SupportedExtension.end(), ext) !=
			s_SupportedExtension.end();
	}

	std::vector<std::string> Shader::s_SupportedExtension = { "glsl" };

}
