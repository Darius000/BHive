#include "BHivePCH.h"
#include "DetailsCustomization.h"
#include "imgui.h"

namespace BHive
{

	void DetailsBuilder::SetEntity(Entity& entity)
	{
		m_Entity = entity;
	}

	void DetailsBuilder::Label(const char* label)
	{
		ImGui::Text(label);
	}

	void DetailsBuilder::StringProperty(const char* label, std::string& st)
	{
		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), st.c_str());
		if (ImGui::InputText(label, buffer, sizeof(buffer)))
		{
			st = std::string(buffer);
		}
	}

	bool DetailsBuilder::Vector3Property(const char* label, FVector3& v)
	{
		return ImGui::DragFloat3(label, *v, 0.1f);
	}

	bool DetailsBuilder::Color3Property(const char* label, FVector3& v)
	{
		return ImGui::ColorEdit3(label, *v);
	}

	bool DetailsBuilder::RotatorProperty(const char* label, Rotator& r)
	{
		return ImGui::DragFloat3(label, *r, 0.1f);
	}

	void DetailsBuilder::TransformProperty(const char* label, Transform& t)
	{
		ImGui::Text(label);
		if (DetailsBuilder::Vector3Property("Position", t.GetPosition()) |
			DetailsBuilder::RotatorProperty("Rotation", t.GetRotation()) |
			DetailsBuilder::Vector3Property("Scale", t.GetScale()))
		{
			t.RecalulateModelMatrix();
		}
	}

	bool DetailsBuilder::FloatProperty(const char* label, float& f)
	{
		return ImGui::DragFloat(label, &f, .1f);
	}

	bool DetailsBuilder::BoolProperty(const char* label, bool& b)
	{
		return ImGui::Checkbox(label, &b);
	}

	bool DetailsBuilder::EnumProperty(const char* label, Projection& e)
	{
		bool selected = false;
		static std::map<int, const char*> names = { {0, "Perspective"},
		{1, "Orthographic"} };
		if (ImGui::BeginCombo(label, names[(int)e]))
		{
			for (int i = 0; i < names.size(); i++)
			{
				if (ImGui::Selectable(names[i], (int)e == i))
				{
					e = (Projection)i;

					selected = true;
				}
			}
			
			ImGui::EndCombo();
		}

		return selected;
	}

	void DetailsBuilder::MeshProperty(const char* label, Ref<Model>& m)
	{
		int i = 0;
		for (auto& mesh : m->GetMeshes())
		{
			ImGui::PushID(i++);
			ImGui::Text(mesh.second->GetName().c_str());
			AssetProperty("Texture", mesh.second->GetMaterial()->m_Texture);
			ImGui::PopID();
		}	
	}

	void ClassPropertyRegistry::RegisterClassDetails(const char* classname, Ref<DetailsCustomization> detailsCustomization)
	{
		s_DetailsRegistry.insert({classname, detailsCustomization});
	}

	Ref<DetailsCustomization> ClassPropertyRegistry::GetDetailsCustomizationInstance(const char* className)
	{
		return s_DetailsRegistry[className];
	}

	std::unordered_map<const char*, Ref<DetailsCustomization>> ClassPropertyRegistry::s_DetailsRegistry;

}
