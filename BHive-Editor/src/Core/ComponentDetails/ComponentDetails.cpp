#include "ComponentDetails.h"

namespace BHive
{
	void TransformComponentDetails::CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder)
	{
		auto& entity = detailsBuilder.GetEntityBeingEdited();
		auto& transform = entity.GetComponent<TransformComponent>().m_Transform;

		detailsBuilder.Label("Transform Component");
		ImGui::Separator();
		detailsBuilder.Property("Transform", transform);
		if (detailsBuilder.Button("Remove##TransformComponent"))
		{
			entity.RemoveComponent<TransformComponent>();
		}
	}

	void TagComponentDetails::CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder)
	{
		auto& entity = detailsBuilder.GetEntityBeingEdited();
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		detailsBuilder.Label("Tag Component");
		ImGui::Separator();
		detailsBuilder.Property("Tag", tag);
	}

	void DirectionalLightComponentDetails::CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder)
	{
		auto& entity = detailsBuilder.GetEntityBeingEdited();

		auto& dirLight = entity.GetComponent<DirectionalLightComponent>();

		detailsBuilder.Label("Directional Light Component");
		ImGui::Separator();
		detailsBuilder.ColorProperty("Color", dirLight.m_LightColor);
		detailsBuilder.Property("Brightness", dirLight.m_LightBrightness, 0.01f);
		if (detailsBuilder.Button("Remove##DirectionalLightComponent"))
		{
			entity.RemoveComponent<DirectionalLightComponent>();
		}
	}

	void PointLightComponentDetails::CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder)
	{
		auto& entity = detailsBuilder.GetEntityBeingEdited();

		auto& pLight = entity.GetComponent<PointLightComponent>();

		detailsBuilder.Label("Point Light Component");
		ImGui::Separator();
		detailsBuilder.ColorProperty("Color", pLight.m_Color);
		detailsBuilder.Property("Constant", pLight.m_Constant);
		detailsBuilder.Property("Linear", pLight.m_Linear);
		detailsBuilder.Property("Quadratic", pLight.m_Quadratic);
		detailsBuilder.Property("Brightness", pLight.m_Brightness, 0.01f);
		if (detailsBuilder.Button("Remove##PointLightComponent"))
		{
			entity.RemoveComponent<PointLightComponent>();
		}
	}

	void SpotLightComponentDetails::CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder)
	{
		auto& entity = detailsBuilder.GetEntityBeingEdited();

		auto& spLight = entity.GetComponent<SpotLightComponent>();

		detailsBuilder.Label("SpotLight Component");
		ImGui::Separator();
		detailsBuilder.ColorProperty("Color", spLight.m_Color);
		detailsBuilder.Property("Cut Off", spLight.m_Cutoff, 0.1f, 0.0f, spLight.m_OuterCutoff);
		detailsBuilder.Property("Outer Cut Off", spLight.m_OuterCutoff, 0.1f, 0.0f);
		detailsBuilder.Property("Constant", spLight.m_Constant, 0.01f, 0.0f, 1.0f);
		detailsBuilder.Property("Linear", spLight.m_Linear, 0.01f, 0.0f, 1.0f);
		detailsBuilder.Property("Quadratic", spLight.m_Quadratic, 0.01f, 0.0f, 1.0f);
		detailsBuilder.Property("Brightness", spLight.m_Brightness, 0.01f);
		if (detailsBuilder.Button("Remove##SpotLightComponent"))
		{
			entity.RemoveComponent<SpotLightComponent>();
		}
	}

	void CameraComponentDetails::CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder)
	{
		auto& entity = detailsBuilder.GetEntityBeingEdited();

		auto& cam = entity.GetComponent<CameraComponent>();
		auto& camera = cam.m_Camera;

		detailsBuilder.Label("Camera Component");
		ImGui::Separator();
		detailsBuilder.Property("Primary", cam.m_PrimaryCamera);
		detailsBuilder.Property("Fixed Aspect Ratio", cam.m_FixedAspectRatio);
		ImGui::BeginGroup();
		ImGui::Text("Projection");

		bool ortho = camera.m_CurrentProjection == Projection::Orthographic;

		if (detailsBuilder.Property<Projection, 2>("Projection", s_Projections ,camera.m_CurrentProjection) |
			detailsBuilder.Property("Far", ortho ? camera.m_OrthographicSettings.Far : camera.m_PerspectiveSettings.Far) |
			detailsBuilder.Property("Near", ortho ? camera.m_OrthographicSettings.Near : camera.m_PerspectiveSettings.Near) |
			detailsBuilder.Property(ortho ? "Size" : "Field of View", ortho ? camera.m_OrthographicSettings.Size : camera.m_PerspectiveSettings.FieldofView))
		{
			camera.RecalculateProjection();
		}
		if (detailsBuilder.Button("Remove##CameraComponent"))
		{
			entity.RemoveComponent<CameraComponent>();
		}

		ImGui::EndGroup();
	}

	void RenderComponentDetails::CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder)
	{
		auto& entity = detailsBuilder.GetEntityBeingEdited();

		auto& mesh = entity.GetComponent<RenderComponent>().m_Model;

		detailsBuilder.Label("Render Component");
		ImGui::Separator();
		detailsBuilder.Property("Mesh", mesh);
		//detailsBuilder.MeshProperty("Sub Meshes", mesh);
		if (detailsBuilder.Button("Remove##RenderComponent"))
		{
			entity.RemoveComponent<RenderComponent>();
		}
	}

	void NativeScriptComponentDetails::CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder)
	{
		auto& entity = detailsBuilder.GetEntityBeingEdited();

		auto& script = entity.GetComponent<NativeScriptComponent>();
		detailsBuilder.Label("C++ Script");
		ImGui::Separator();
		if (detailsBuilder.Button("Remove##ScriptComponent"))
		{
			entity.RemoveComponent<NativeScriptComponent>();
		}
	}
}
