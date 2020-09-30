#include "BHivePCH.h"
#include "RenderSystem.h"
#include "Components/Component.h"
#include "Managers/AssetManagers.h"

namespace BHive
{ 
	void RenderSystem::OnUpdate(const Time& time, entt::registry& componentRegistry)
	{
		FVector3 CameraPosition = FVector3();
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

					CameraPosition = transform.m_Transform.GetPosition();
				}
			}
		}

		//-----------------------------Update Lights--------------------------
		{
			auto view = componentRegistry.view<DirectionalLightComponent, TransformComponent>();
			int numDirLights = 0;
			for (auto entity : view)
			{
				auto& [directionalLight, transform] = view.get<DirectionalLightComponent, TransformComponent>(entity);				
				std::string uniform = "directionalLights[" + std::to_string(numDirLights) + "].";
				numDirLights++;
				for (auto& a : AssetManager::GetAssets<Shader>())
				{
					a.second->Bind();
					a.second->SetInt("numDirLights", numDirLights);
					a.second->SetVec3(uniform + "direction", transform.m_Transform.GetForward());
					a.second->SetVec3(uniform + "color", directionalLight.m_LightColor);
					a.second->SetFloat(uniform + "brightness", directionalLight.m_LightBrightness);
				}
			}


		}
		{
			auto view = componentRegistry.view<PointLightComponent, TransformComponent>();
			int numPointLights = 0;
			for (auto entity : view)
			{
				auto& [pointLight, transform] = view.get<PointLightComponent, TransformComponent>(entity);
				std::string uniform = "pointLights[" + std::to_string(numPointLights) + "].";
				numPointLights++;
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
			int numSpotLights = 0;
			for (auto entity : view)
			{
				auto& [spotLight, transform] = view.get<SpotLightComponent, TransformComponent>(entity);			
				std::string uniform = "spotLights[" + std::to_string(numSpotLights) + "].";
				numSpotLights++;
				for (auto& a : AssetManager::GetAssets<Shader>())
				{
					a.second->Bind();
					a.second->SetInt("numSpotLights", numSpotLights);
					a.second->SetVec3(uniform + "position", transform.m_Transform.GetPosition());
					a.second->SetVec3(uniform + "color", spotLight.m_Color);
					a.second->SetVec3(uniform + "direction", transform.m_Transform.GetForward());
					a.second->SetFloat(uniform + "cutoff", MathLibrary::Cos(MathLibrary::ToRadians(spotLight.m_Cutoff)));
					a.second->SetFloat(uniform + "outerCutoff", MathLibrary::Cos(MathLibrary::ToRadians(spotLight.m_OuterCutoff)));
					a.second->SetFloat(uniform + "constant", spotLight.m_Constant);
					a.second->SetFloat(uniform + "linear", spotLight.m_Linear);
					a.second->SetFloat(uniform + "quadratic", spotLight.m_Quadratic);
					a.second->SetFloat(uniform + "brightness", spotLight.m_Brightness);
				}
			}
		}


		//------------------------------------Draw Meshes---------------------------------------
		{
			//Sort models based on distance from camera
			
			struct Comp
			{
				RenderComponent rc;
				TransformComponent tc;
			};

			auto group = componentRegistry.view<RenderComponent, TransformComponent>();
			std::multimap<float, Comp> sorted;

			for (auto entity : group)
			{
				auto& [render, transform] = group.get<RenderComponent, TransformComponent>(entity);
				float distance = (CameraPosition - transform.m_Transform.GetPosition()).GetMagnitude2();
				sorted.insert({distance, {render, transform}});
				
			}

			//Draw models
			for (auto it = sorted.rbegin(); it != sorted.rend(); it++)
			{
				auto render = it->second.rc;
				auto transform = it->second.tc;

				if (render.m_Model)
				{
					for (auto& mesh : render.m_Model->GetMeshes())
					{
						auto shader = mesh.second->GetMaterial()->GetShader();

						shader->Bind();
						shader->SetMat4("u_Model", transform.m_Transform.GetMatrix());
						mesh.second->Render();
					}
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

