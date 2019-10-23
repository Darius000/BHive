#include "BHivePCH.h"
#include "AssetManager.h"
#include "BHive/Platforms/Opengl/OpenGLShader.h"

namespace BHive
{
	void AssetManager::AddShader(std::shared_ptr<Shader>& shader)
	{
		s_Shaders.push_back(shader);
	}

	void AssetManager::DeleteShader(const std::shared_ptr<Shader>& shader)
	{
		std::vector<std::shared_ptr<Shader>>::iterator it = std::find(Begin(), End(), shader);
		s_Shaders.erase(it);
	}

	void AssetManager::UpdateShaderViewProjectionMatrices(const glm::mat4& viewProjectionMatrix)
	{
		for (auto& s : s_Shaders)
		{
			s->Bind();
			s->SetMatrix4("u_ViewProjection", viewProjectionMatrix);
		}
	}

	std::vector<std::shared_ptr<Shader>> AssetManager::s_Shaders;
}