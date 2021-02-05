#pragma once

#include "DetailsCustomization.h"
#include "Factory/Factory.h"

namespace BHive
{
	template<typename Component>
	class ComponentDetails : public DetailsCustomization
	{
	public:
		using ComponentClass = Component;

		bool OnDisplayBeginDetails(PropertyDetailsBuilder& detailsBuilder)
		{
			
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 4));

			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImVec2 contentRegionAvail = ImGui::GetContentRegionAvail();

			ImGui::Separator();
			bool opened = ImGui::TreeNodeEx((void*)typeid(ComponentClass).hash_code(), ImGuiTreeNodeFlags_DefaultOpen |
			ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap, Factory<Component>::GetName().c_str());

			ImGui::PopStyleVar();

			ImGui::SameLine(contentRegionAvail.x - lineHeight * 0.5f);
			if (ImGui::Button("+", ImVec2(lineHeight, lineHeight)))
			{
				ImGui::OpenPopup("Component Settings");
			}

			if (ImGui::BeginPopup("Component Settings"))
			{
				if (ImGui::MenuItem("Remove"))
				{
					m_RemoveComponent = true;
				}
				ImGui::EndPopup();
			}

			ImGui::Separator();	

			return opened;
		}

		virtual void OnDisplayPropertyDetails(Entity& entity, Component& component, PropertyDetailsBuilder& detailsBuilder){}

		void OnDisplayEndDetails(PropertyDetailsBuilder& detailsBuilder)
		{
			ImGui::TreePop();
		}

		void CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder) override
		{
			auto& entity = detailsBuilder.GetEntityBeingEdited();
			auto& component = entity.GetComponent<ComponentClass>();

			ImGui::PushID(entity.GetID());
			if (OnDisplayBeginDetails(detailsBuilder))
			{
				OnDisplayPropertyDetails(entity, component, detailsBuilder);
				OnDisplayEndDetails(detailsBuilder);	
			}
			ImGui::PopID();
			
			if (m_RemoveComponent)
			{
				detailsBuilder.GetEntityBeingEdited().RemoveComponent<ComponentClass>();
				m_RemoveComponent = false;
			}
		}

	private:
		bool m_Opened;
		bool m_RemoveComponent;
	};

	class TransformComponentDetails : public ComponentDetails<TransformComponent>
	{
		
	public:
		void OnDisplayPropertyDetails(Entity& entity, ComponentClass& component,PropertyDetailsBuilder& detailsBuilder) override;

	};

	class TagComponentDetails : public ComponentDetails<TagComponent>
	{
	public:

		void OnDisplayPropertyDetails(Entity& entity, ComponentClass& component, PropertyDetailsBuilder& detailsBuilder) override;
	};

	class DirectionalLightComponentDetails : public ComponentDetails<DirectionalLightComponent>
	{
	public:

		void OnDisplayPropertyDetails(Entity& entity, ComponentClass& component, PropertyDetailsBuilder& detailsBuilder) override;
	};

	class PointLightComponentDetails : public ComponentDetails<PointLightComponent>
	{
	public:

		void OnDisplayPropertyDetails(Entity& entity, ComponentClass& component, PropertyDetailsBuilder& detailsBuilder) override;
	};

	class SpotLightComponentDetails : public ComponentDetails<SpotLightComponent>
	{
	public:

		void OnDisplayPropertyDetails(Entity& entity, ComponentClass& component, PropertyDetailsBuilder& detailsBuilder) override;
	};

	class CameraComponentDetails : public ComponentDetails<CameraComponent>
	{
	public:

		void OnDisplayPropertyDetails(Entity& entity, ComponentClass& component, PropertyDetailsBuilder& detailsBuilder) override;
	};

	class RenderComponentDetails : public ComponentDetails<RenderComponent>
	{
	public:

		void OnDisplayPropertyDetails(Entity& entity, ComponentClass& component, PropertyDetailsBuilder& detailsBuilder) override;
	};

	class NativeScriptComponentDetails : public ComponentDetails<NativeScriptComponent>
	{
	public:
		void OnDisplayPropertyDetails(Entity& entity, ComponentClass& component, PropertyDetailsBuilder& detailsBuilder) override;
	};
}