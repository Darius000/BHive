#pragma once

#include "TransformComponent.h"
#include "BHive/Renderer/Buffer.h"
#include "BHive/Renderer/VertexArray.h"
#include "BHive/Platforms/Opengl/OpenGLShader.h"
#include "BHive/Renderer/Texture.h"
#include "BHive/Renderer/Mesh.h"

namespace BHive
{
	struct RenderComponent
	{

		void Draw();
		void OnImguiRender();

		Ref<Texture2D> m_Texture;
		Ref<Model> m_Model;
	}; 
}
