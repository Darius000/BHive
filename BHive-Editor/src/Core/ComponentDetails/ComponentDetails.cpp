#include "ComponentDetails.h"
#include "Properties/BoolProperty.h"

namespace BHive
{
	void TransformComponentDetails::OnDisplayPropertyDetails(Entity& entity, ComponentClass& component, PropertyDetailsBuilder& detailsBuilder)
	{
		detailsBuilder.TransformProperty("Transform", component.m_Transform);
	}

	void TagComponentDetails::OnDisplayPropertyDetails(Entity& entity, ComponentClass& component, PropertyDetailsBuilder& detailsBuilder)
	{
		auto id = std::to_string(entity.GetID());
		detailsBuilder.EntityName( id, component.Tag);
	}

	void DirectionalLightComponentDetails::OnDisplayPropertyDetails(Entity& entity, ComponentClass& component, PropertyDetailsBuilder& detailsBuilder)
	{
		//detailsBuilder.Color3Property("Color", component.m_LightColor, true);
		detailsBuilder.FloatProperty("Brightness", component.m_LightBrightness, 0.01f);

		m_ColorProp.OnImGuiRender();

		component.m_LightColor = m_Color;
	}

	LinearColor3 DirectionalLightComponentDetails::m_Color = {1.0f};

	LColor3Property DirectionalLightComponentDetails::m_ColorProp = 
		LColor3Property("Color", &m_Color, { 1.0f });

	void PointLightComponentDetails::OnDisplayPropertyDetails(Entity& entity, ComponentClass& component, PropertyDetailsBuilder& detailsBuilder)
	{
		detailsBuilder.Color3Property("Color",	component.m_Color, true);
		detailsBuilder.FloatProperty("Constant",		component.m_Constant);
		detailsBuilder.FloatProperty("Linear",		component.m_Linear);
		detailsBuilder.FloatProperty("Quadratic",	component.m_Quadratic);
		detailsBuilder.FloatProperty("Brightness",	component.m_Brightness, 0.01f);
	}

	void SpotLightComponentDetails::OnDisplayPropertyDetails(Entity& entity, ComponentClass& component, PropertyDetailsBuilder& detailsBuilder)
	{
		detailsBuilder.Color3Property("Color",		component.m_Color, true);
		detailsBuilder.FloatProperty("Cut Off",			component.m_Cutoff, 0.1f, 0.0f, component.m_OuterCutoff);
		detailsBuilder.FloatProperty("Outer Cut Off",	component.m_OuterCutoff, 0.1f, 0.0f);
		detailsBuilder.FloatProperty("Constant",			component.m_Constant, 0.01f, 0.0f, 1.0f);
		detailsBuilder.FloatProperty("Linear",			component.m_Linear, 0.01f, 0.0f, 1.0f);
		detailsBuilder.FloatProperty("Quadratic",		component.m_Quadratic, 0.01f, 0.0f, 1.0f);
		detailsBuilder.FloatProperty("Brightness",		component.m_Brightness, 0.01f);

	}

	void CameraComponentDetails::OnDisplayPropertyDetails(Entity& entity, ComponentClass& component, PropertyDetailsBuilder& detailsBuilder)
	{
		auto& camera = component.m_Camera;

		//detailsBuilder.BoolProperty("Primary", component.m_PrimaryCamera, true);
		//detailsBuilder.BoolProperty("Fixed Aspect Ratio", component.m_FixedAspectRatio, false);

		static BoolProperty PrimaryCamera = BoolProperty("Primary", &component.m_PrimaryCamera, true);
		static BoolProperty FixedAspectRatio = BoolProperty("Fixed Aspect Ratio", &component.m_FixedAspectRatio, false);

		PrimaryCamera.OnImGuiRender();
		FixedAspectRatio.OnImGuiRender();
	

		bool ortho = camera.m_CurrentProjection == Projection::Orthographic;
		bool changed = false;

		changed |= detailsBuilder.EnumProperty<Projection, 2>("Projection", s_Projections, camera.m_CurrentProjection);
		changed |= detailsBuilder.FloatProperty("Far", ortho ? camera.m_OrthographicSettings.Far : camera.m_PerspectiveSettings.Far);
		changed |= detailsBuilder.FloatProperty("Near", ortho ? camera.m_OrthographicSettings.Near : camera.m_PerspectiveSettings.Near);
		changed |= detailsBuilder.FloatProperty(ortho ? "Size" : "Field of View", ortho ? camera.m_OrthographicSettings.Size : camera.m_PerspectiveSettings.FieldofView);

		if (changed)
		{
			camera.RecalculateProjection();
		}
	}

	void RenderComponentDetails::OnDisplayPropertyDetails(Entity& entity, ComponentClass& component, PropertyDetailsBuilder& detailsBuilder)
	{
		detailsBuilder.AssetProperty("Mesh", component.m_Model);

		if (ImGui::TreeNode("Materials"))
		{
			for (auto& mesh : component.m_Model->GetMeshes())
			{
				detailsBuilder.AssetProperty(mesh.second->GetName(), mesh.second->m_Material);
			}

			ImGui::TreePop();
		}
	}

	void NativeScriptComponentDetails::OnDisplayPropertyDetails(Entity& entity, ComponentClass& component, PropertyDetailsBuilder& detailsBuilder)
	{

	}
}
