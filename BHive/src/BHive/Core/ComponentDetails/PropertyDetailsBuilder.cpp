#include "BHivePCH.h"
#include "PropertyDetailsBuilder.h"
#include "imgui.h"

namespace BHive
{
	void PropertyDetailsBuilder::SetEntity(Entity& entity)
	{
		m_Entity = entity;
	}

	void PropertyDetailsBuilder::Label(const char* label)
	{
		ImGui::Text(label);
	}

	bool PropertyDetailsBuilder::Button(const char* label, const FVector2&& size)
	{
		if (ImGui::Button(label, ImVec2(size.x, size.y)))
		{
			return true;
		}

		return false;
	}

	void PropertyDetailsBuilder::Image(const uint32& ID, FVector2 size)
	{
		ImGui::Image((void*)ID, ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0));
	}

	void PropertyDetailsBuilder::StringProperty(const char* label, std::string& st)
	{
		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), st.c_str());
		if (ImGui::InputText(label, buffer, sizeof(buffer)))
		{
			st = std::string(buffer);
		}
	}

	void PropertyDetailsBuilder::PathProperty(const char* label, WinPath& p)
	{
		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), p.GetPath());
		if (ImGui::InputText(label, buffer, sizeof(buffer)))
		{
			p = WinPath(buffer);
		}
	}

	bool PropertyDetailsBuilder::Vector2Property(const char* label, FVector2& v)
	{
		return ImGui::DragFloat2(label, *v, 0.1f);
	}

	bool PropertyDetailsBuilder::Vector3Property(const char* label, FVector3& v)
	{
		return ImGui::DragFloat3(label, *v, 0.1f);
	}

	bool PropertyDetailsBuilder::Vector4Property(const char* label, FVector4& v)
	{
		return ImGui::DragFloat4(label, *v, 0.1f);
	}

	bool PropertyDetailsBuilder::Color3Property(const char* label, LinearColor3& v)
	{
		return ImGui::ColorEdit3(label, *v);
	}

	bool PropertyDetailsBuilder::Color4Property(const char* label, LinearColor4& v)
	{
		return ImGui::ColorEdit4(label, *v);
	}

	bool PropertyDetailsBuilder::RotatorProperty(const char* label, Rotator& r)
	{
		return ImGui::DragFloat3(label, *r, 0.1f);
	}

	void PropertyDetailsBuilder::TransformProperty(const char* label, Transform& t)
	{
		ImGui::Text(label);
		if (PropertyDetailsBuilder::Vector3Property("Position", t.GetPosition()) |
			PropertyDetailsBuilder::RotatorProperty("Rotation", t.GetRotation()) |
			PropertyDetailsBuilder::Vector3Property("Scale", t.GetScale()))
		{
			t.RecalulateModelMatrix();
		}
	}

	bool PropertyDetailsBuilder::FloatProperty(const char* label, float& f, float speed, float min, float max)
	{
		return ImGui::DragFloat(label, &f, speed, min, max);
	}

	bool PropertyDetailsBuilder::IntProperty(const char* label, int& f, float speed, int min, int max)
	{
		return ImGui::DragInt(label, &f, speed, min, max);
	}

	bool PropertyDetailsBuilder::BoolProperty(const char* label, bool& b)
	{
		return ImGui::Checkbox(label, &b);
	}

	bool PropertyDetailsBuilder::EnumProperty(const char* label, Projection& e)
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

	void PropertyDetailsBuilder::TextureProperty(const char* label, Ref<Texture2D>& t)
	{
		float ImageSize = 100.0f;
		float RegionWidth = ImGui::GetWindowContentRegionWidth();
		float width = RegionWidth - (ImageSize + RegionWidth * .5f);
		ImGui::Image(t ? (void*)t->GetRendererID() : (void*)-1, ImVec2(ImageSize, ImageSize), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::SameLine();
		ImGui::PushItemWidth(width);
		AssetProperty(label, t);
		ImGui::PopItemWidth();
	}

	void PropertyDetailsBuilder::MeshProperty(const char* label, Ref<Model>& m)
	{
		if (m == nullptr) return;

		int i = 0;
		for (auto& mesh : m->GetMeshes())
		{
			ImGui::PushID(i++);
			ImGui::Text(mesh.second->GetName().c_str());
			Label("Material");
			MaterialProperty(mesh.second->GetMaterial());
			ImGui::PopID();
		}
	}

	void PropertyDetailsBuilder::MaterialProperty(Ref<Material>& m)
	{
		int i = 0;
		for (auto& uniform : m->GetShaderUniforms())
		{
			ImGui::PushID(i++);
			switch (uniform.m_Type)
			{
			default:
				break;
			case ShaderUniformType::Bool:
				BoolProperty(uniform.m_DisplayName, *reinterpret_cast<bool*>(uniform.m_Value));
				break;
			case ShaderUniformType::Int:
				IntProperty(uniform.m_DisplayName, *reinterpret_cast<int*>(uniform.m_Value));
				break;
			case ShaderUniformType::Float:
				FloatProperty(uniform.m_DisplayName, *reinterpret_cast<float*>(uniform.m_Value));
				break;
			case ShaderUniformType::Float2:
			case ShaderUniformType::Vec2:
				Vector2Property(uniform.m_DisplayName, *reinterpret_cast<FVector2*>(uniform.m_Value));
				break;
			case ShaderUniformType::Float3:
			case ShaderUniformType::Vec3:
				Vector3Property(uniform.m_DisplayName, *reinterpret_cast<FVector3*>(uniform.m_Value));
				break;
			case ShaderUniformType::Float4:
			case ShaderUniformType::Vec4:
				Vector4Property(uniform.m_DisplayName, *reinterpret_cast<FVector4*>(uniform.m_Value));
				break;
			case ShaderUniformType::Color3:
				Color3Property(uniform.m_DisplayName, *reinterpret_cast<LinearColor3*>(uniform.m_Value));
				break;
			case ShaderUniformType::Color4:
				Color4Property(uniform.m_DisplayName, *reinterpret_cast<LinearColor4*>(uniform.m_Value));
				break;
			case ShaderUniformType::Sampler:
				TextureProperty(uniform.m_DisplayName, *reinterpret_cast<Ref<Texture2D>*>(uniform.m_Value));
				break;
			}
			ImGui::PopID();
		}
	}
}