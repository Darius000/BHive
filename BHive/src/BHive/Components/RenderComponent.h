#pragma once

#include "TransformComponent.h"
#include "Assets/Shader.h"

namespace BHive
{
	class BHive_API RenderComponent : public TransformComponent
	{
		BCLASS(RenderComponent, ComponentCategory, TransformComponent);

	public:
		RenderComponent();
		virtual ~RenderComponent();

		virtual void ComponentStart() override;
		virtual void ComponentUpdate(float deltaTime) override;
		virtual void Construct();
		virtual void Render();
		void SetShader(Shader* shader);

		unsigned int vao, vbo, ebo;

		std::vector<float> positions;
		std::vector<unsigned int> indices;
		std::string vertexShader, fragmentShader;

		Shader* shader;
	};
}
