#pragma once

#include "BHive/Renderer/Shader.h"

namespace BHive
{
	class AssetManager
	{
	public:
		virtual ~AssetManager() = default;
		static void AddShader(std::shared_ptr<Shader>& shader);
		static void DeleteShader(const std::shared_ptr<Shader>& shader);
		static void UpdateShaderViewProjectionMatrices(const glm::mat4& viewProjectionMatrix);

		static std::vector<std::shared_ptr<Shader>>::iterator const Begin() { return s_Shaders.begin(); }
		static std::vector<std::shared_ptr<Shader>>::iterator const End() { return s_Shaders.end(); }
		static std::vector<std::shared_ptr<Shader>> const& GetShaders() { return s_Shaders; }

	private:
		static std::vector<std::shared_ptr<Shader>> s_Shaders;
	};
}