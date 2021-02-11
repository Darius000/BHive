#include "BHivePCH.h"
#include "RenderSystem.h"
#include "Components/Component.h"
#include "Managers/AssetManagers.h"


namespace BHive
{ 

	void RenderSystem::OnInitialize()
	{
		
	}

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
				for (auto& asset : AssetManager::GetAssetsOfType<Shader>())
				{
					auto shader = CastPointer<Shader>(asset.second);
					shader->Bind();			
					shader->SetVec3(uniform + "direction", transform.m_Transform.GetForward());
					shader->SetVec3(uniform + "color", directionalLight.m_LightColor);
					shader->SetFloat(uniform + "brightness", directionalLight.m_LightBrightness);
				}
			}

			for (auto& asset : AssetManager::GetAssetsOfType<Shader>())
			{
				auto shader = CastPointer<Shader>(asset.second);
				shader->Bind();
				shader->SetInt("numDirLights", numDirLights);
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
				for (auto& asset: AssetManager::GetAssetsOfType<Shader>())
				{
					auto shader = CastPointer<Shader>(asset.second);
					shader->Bind();			
					shader->SetVec3(uniform + "position", transform.m_Transform.GetPosition());
					shader->SetVec3(uniform + "color", pointLight.m_Color);
					shader->SetFloat(uniform + "constant", pointLight.m_Constant);
					shader->SetFloat(uniform + "linear", pointLight.m_Linear);
					shader->SetFloat(uniform + "quadratic", pointLight.m_Quadratic);
					shader->SetFloat(uniform + "brightness", pointLight.m_Brightness);
					
				}
			}

			for (auto& asset : AssetManager::GetAssetsOfType<Shader>())
			{
				auto shader = CastPointer<Shader>(asset.second);
				shader->Bind();
				shader->SetInt("numPointLights", numPointLights);
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
				for (auto& asset : AssetManager::GetAssetsOfType<Shader>())
				{
					auto shader = CastPointer<Shader>(asset.second);
					shader->Bind();				
					shader->SetVec3(uniform + "position", transform.m_Transform.GetPosition());
					shader->SetVec3(uniform + "color", spotLight.m_Color);
					shader->SetVec3(uniform + "direction", transform.m_Transform.GetForward());
					shader->SetFloat(uniform + "cutoff", MathLibrary::Cos(MathLibrary::ToRadians(spotLight.m_Cutoff)));
					shader->SetFloat(uniform + "outerCutoff", MathLibrary::Cos(MathLibrary::ToRadians(spotLight.m_OuterCutoff)));
					shader->SetFloat(uniform + "constant", spotLight.m_Constant);
					shader->SetFloat(uniform + "linear", spotLight.m_Linear);
					shader->SetFloat(uniform + "quadratic", spotLight.m_Quadratic);
					shader->SetFloat(uniform + "brightness", spotLight.m_Brightness);
				}
			}

			for (auto& asset : AssetManager::GetAssetsOfType<Shader>())
			{
				auto shader = CastPointer<Shader>(asset.second);
				shader->Bind();
				shader->SetInt("numSpotLights", numSpotLights);
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

