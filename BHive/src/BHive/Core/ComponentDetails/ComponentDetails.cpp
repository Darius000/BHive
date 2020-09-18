#include "BHivePCH.h"
#include "ComponentDetails.h"

namespace BHive
{
	void TransformComponentDetails::CreateCustomizedDetails(DetailsBuilder& detailsBuilder)
	{
		auto& entity = detailsBuilder.GetEntityBeingEdited();
		auto& transform = entity.GetComponent<TransformComponent>().m_Transform;

		detailsBuilder.Label("Transform Component");
		ImGui::Separator();
		detailsBuilder.TransformProperty("Transform", transform);
	}

	void TagComponentDetails::CreateCustomizedDetails(DetailsBuilder& detailsBuilder)
	{
		auto& entity = detailsBuilder.GetEntityBeingEdited();
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		detailsBuilder.Label("Tag Component");
		ImGui::Separator();
		detailsBuilder.StringProperty("Tag", tag);
	}

	void DirectionalLightComponentDetails::CreateCustomizedDetails(DetailsBuilder& detailsBuilder)
	{
		auto& entity = detailsBuilder.GetEntityBeingEdited();

		auto& dirLight = entity.GetComponent<DirectionalLightComponent>();

		detailsBuilder.Label("Directional Light Component");
		ImGui::Separator();
		detailsBuilder.Color3Property("Color", dirLight.m_LightColor);
		detailsBuilder.FloatProperty("Brightness", dirLight.m_LightBrightness);
	}

	void PointLightComponentDetails::CreateCustomizedDetails(DetailsBuilder& detailsBuilder)
	{
		auto& entity = detailsBuilder.GetEntityBeingEdited();

		auto& pLight = entity.GetComponent<PointLightComponent>();

		detailsBuilder.Label("Directional Light Component");
		ImGui::Separator();
		detailsBuilder.Color3Property("Color", pLight.m_Color);
		detailsBuilder.FloatProperty("Constant", pLight.m_Constant);
		detailsBuilder.FloatProperty("Linear", pLight.m_Linear);
		detailsBuilder.FloatProperty("Quadratic", pLight.m_Quadratic);
		detailsBuilder.FloatProperty("Brightness", pLight.m_Brightness);
	}

	void SpotLightComponentDetails::CreateCustomizedDetails(DetailsBuilder& detailsBuilder)
	{
		auto& entity = detailsBuilder.GetEntityBeingEdited();

		auto& spLight = entity.GetComponent<SpotLightComponent>();

		detailsBuilder.Label("SpotLight Component");
		ImGui::Separator();
		detailsBuilder.Color3Property("Color", spLight.m_Color);
		detailsBuilder.FloatProperty("Cut Off", spLight.m_Cutoff);
		detailsBuilder.FloatProperty("Outer Cut Off", spLight.m_OuterCutoff);
		detailsBuilder.FloatProperty("Constant", spLight.m_Constant);
		detailsBuilder.FloatProperty("Linear", spLight.m_Linear);
		detailsBuilder.FloatProperty("Quadratic", spLight.m_Quadratic);
		detailsBuilder.FloatProperty("Brightness", spLight.m_Brightness);
	}

	void CameraComponentDetails::CreateCustomizedDetails(DetailsBuilder& detailsBuilder)
	{
		auto& entity = detailsBuilder.GetEntityBeingEdited();

		auto& cam = entity.GetComponent<CameraComponent>();
		auto& camera = cam.m_Camera;

		detailsBuilder.Label("Camera Component");
		ImGui::Separator();
		detailsBuilder.BoolProperty("Primary", cam.m_PrimaryCamera);
		detailsBuilder.BoolProperty("Fixed Aspect Ratio", cam.m_FixedAspectRatio);
		ImGui::BeginGroup();
		ImGui::Text("Projection");

		bool ortho = camera.m_CurrentProjection == Projection::Orthographic;

		if (detailsBuilder.EnumProperty("Projection", camera.m_CurrentProjection) |
			detailsBuilder.FloatProperty("Far", ortho ? camera.m_OrthographicSettings.Far : camera.m_PerspectiveSettings.Far) |
			detailsBuilder.FloatProperty("Near", ortho ? camera.m_OrthographicSettings.Near : camera.m_PerspectiveSettings.Near) |
			detailsBuilder.FloatProperty(ortho ? "Size" : "Field of View", ortho ? camera.m_OrthographicSettings.Size : camera.m_PerspectiveSettings.FieldofView))
		{
			camera.RecalculateProjection();
		}

		ImGui::EndGroup();
	}

	void RenderComponentDetails::CreateCustomizedDetails(DetailsBuilder& detailsBuilder)
	{
		auto& entity = detailsBuilder.GetEntityBeingEdited();

		auto& mesh = entity.GetComponent<RenderComponent>().m_Model;

		detailsBuilder.Label("Render Component");
		ImGui::Separator();
		detailsBuilder.AssetProperty("Mesh", mesh);
		detailsBuilder.MeshProperty("Sub Meshes", mesh);
	}

}
