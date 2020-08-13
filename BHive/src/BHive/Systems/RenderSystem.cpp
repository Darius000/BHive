#include "BHivePCH.h"
#include "RenderSystem.h"
#include "Components/Component.h"


namespace BHive
{ 
	void RenderSystem::OnUpdate(const Time& time, entt::registry& componentRegistry)
	{
		
		//------------------------Update Camera-----------------------------
		{
			auto group = componentRegistry.view<CameraComponent, TransformComponent>();
			for (auto entity : group)
			{
				auto& [camera, transform] = group.get<CameraComponent, TransformComponent>(entity);

				if (camera.m_PrimaryCamera)
				{
					glm::mat4 m_ProjectionMatrix = camera.m_Camera.GetProjection();

					glm::mat4 matrix = transform.m_Transform.GetMatrix();
					glm::mat4 m_ViewMatrix = glm::inverse(matrix);
					glm::mat4 m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
					ShaderLibrary::UpdateShaderViewProjectionMatrices(m_ViewProjectionMatrix);
				}
			}
		}

		//-----------------------------Update Lights--------------------------
		{
			auto view = componentRegistry.view<DirectionalLightComponent>();
			for (auto entity : view)
			{
				auto& directionalLight = view.get<DirectionalLightComponent>(entity);
				for (auto& shader : ShaderLibrary::GetShaders())
				{
					shader.second->Bind();
					shader.second->SetVec3("directionalLight.direction", directionalLight.m_LightDirection);
					shader.second->SetVec3("directionalLight.color", directionalLight.m_LightColor);
					shader.second->SetFloat("directionalLight.brightness", directionalLight.m_LightBrightness);
				}
			}
		}

		//------------------------------------Draw Meshes---------------------------------------
		{
			auto group = componentRegistry.view<RenderComponent, TransformComponent>();
			for (auto entity : group)
			{
				auto& [render, transform] = group.get<RenderComponent, TransformComponent>(entity);
				if (render.m_Model)
				{
					for (auto& mesh : render.m_Model->GetMeshes())
					{
						Ref<Shader> shader = mesh.second->GetShader();
						shader->Bind();
						shader->SetMat4("u_Model", transform.m_Transform.GetMatrix());
					}

					render.m_Model->Render();
				}
			}
		}
	}

	void RenderSystem::OnViewportResize(uint32 width, uint32 height, entt::registry& componentRegistry)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		auto view = componentRegistry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.m_FixedAspectRatio)
			{
				cameraComponent.m_Camera.OnViewportResize(width, height);
			}
		}
	}

}

