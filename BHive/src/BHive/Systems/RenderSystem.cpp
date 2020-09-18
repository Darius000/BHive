#include "BHivePCH.h"
#include "RenderSystem.h"
#include "Components/Component.h"
#include "Managers/AssetManagers.h"

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

					for (auto& a : AssetManager::GetAssets<Shader>())
					{
						a.second->Bind();
						a.second->SetMat4("u_ViewProjection", m_ViewProjectionMatrix);
						a.second->SetMat4("u_View", m_ViewMatrix);
						a.second->SetVec3("CameraPosition", transform.m_Transform.GetPosition());
					}
				}
			}
		}

		//-----------------------------Update Lights--------------------------
		{
			auto view = componentRegistry.view<DirectionalLightComponent, TransformComponent>();
			for (auto entity : view)
			{
				auto& [directionalLight, transform] = view.get<DirectionalLightComponent, TransformComponent>(entity);

				for (auto& a : AssetManager::GetAssets<Shader>())
				{
					a.second->Bind();
					a.second->SetVec3("directionalLight.direction", transform.m_Transform.GetForward());
					a.second->SetVec3("directionalLight.color", directionalLight.m_LightColor);
					a.second->SetFloat("directionalLight.brightness", directionalLight.m_LightBrightness);
				}
			}


		}
		{
			auto view = componentRegistry.view<PointLightComponent, TransformComponent>();
			int numPointLights = 0;
			for (auto entity : view)
			{
				auto& [pointLight, transform] = view.get<PointLightComponent, TransformComponent>(entity);
				numPointLights++;
				std::string uniform = "pointLights[" + std::to_string(numPointLights - 1) + "].";
				for (auto& a : AssetManager::GetAssets<Shader>())
				{
					a.second->Bind();
					a.second->SetInt("numPointLights", numPointLights);
					a.second->SetVec3(uniform + "position", transform.m_Transform.GetPosition());
					a.second->SetVec3(uniform + "color", pointLight.m_Color);
					a.second->SetFloat(uniform + "constant", pointLight.m_Constant);
					a.second->SetFloat(uniform + "linear", pointLight.m_Linear);
					a.second->SetFloat(uniform + "quadratic", pointLight.m_Quadratic);
					a.second->SetFloat(uniform + "brightness", pointLight.m_Brightness);
					
				}
			}
		}

		{
			auto view = componentRegistry.view<SpotLightComponent, TransformComponent>();
			for (auto entity : view)
			{
				auto& [spotLight, transform] = view.get<SpotLightComponent, TransformComponent>(entity);

				for (auto& a : AssetManager::GetAssets<Shader>())
				{
					a.second->Bind();
					a.second->SetVec3("spotLight.position", transform.m_Transform.GetPosition());
					a.second->SetVec3("spotLight.color", spotLight.m_Color);
					a.second->SetVec3("spotLight.direction", transform.m_Transform.GetForward());
					a.second->SetFloat("spotLight.cutoff", spotLight.m_Cutoff);
					a.second->SetFloat("spotLight.outerCutoff", spotLight.m_OuterCutoff);
					a.second->SetFloat("spotLight.constant", spotLight.m_Constant);
					a.second->SetFloat("spotLight.linear", spotLight.m_Linear);
					a.second->SetFloat("spotLight.quadratic", spotLight.m_Quadratic);
					a.second->SetFloat("spotLight.brightness", spotLight.m_Brightness);
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
						
						//shader->Bind();
						shader->SetMat4("u_Model", transform.m_Transform.GetMatrix());
						mesh.second->Render();
					}

					//render.m_Model->Render();
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

