#pragma once

#include "TransformComponent.h"
#include "BHive/Renderer/Buffer.h"
#include "BHive/Renderer/VertexArray.h"
#include "BHive/Platforms/Opengl/OpenGLShader.h"
#include "BHive/Renderer/Texture.h"
#include "BHive/Renderer/Mesh.h"

namespace BHive
{
	class BHive_API RenderComponent : public TransformComponent
	{
		BCLASS(RenderComponent, ComponentCategory, TransformComponent)

	public:
		RenderComponent();
		RenderComponent(const RenderComponent& other);
		virtual ~RenderComponent() {};

		virtual void ComponentInit() override;
		virtual void ComponentStart() override;
		virtual void ComponentUpdate(const Time& time) override;

	protected:
		virtual void OnTransformUpdated(const Transform& transform) override;

	public:
		void SetShader(Ref<Shader> shader);
		Ref<Shader> GetShader() const { return m_Shader; }
		void SetTexture(Ref<Texture2D> texture);

		void SetMesh(Ref<FMesh> Mesh);
		Ref<FMesh> GetMesh() { return m_Mesh; }

	private:
		void CreateBuffers();
		void Draw();

	protected:
		//std::vector<float> m_Vertices;
		//std::vector<uint32> m_Indices;

	private:
		Ref<Shader> m_Shader;
		//Ref<VertexArray> m_VertexArray;
		Ref<Texture2D> m_Texture;

	protected:
		Ref<FMesh> m_Mesh;
	};
}
