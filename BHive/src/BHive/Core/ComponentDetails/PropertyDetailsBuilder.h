#pragma once

namespace BHive
{
	class PropertyDetailsBuilder
	{
	public:
		PropertyDetailsBuilder() = default;
		PropertyDetailsBuilder(const PropertyDetailsBuilder&) = default;

		Entity GetEntityBeingEdited() { return m_Entity; }

		void SetEntity(Entity& entity);

		void Label(const char* label);
		bool Button(const  char* label, const FVector2&& size = FVector2(0.0f));
		void Image(const uint32& ID, FVector2 size);

		template<typename Enum, size_t numItems>
		inline bool Combo(const char* label,  const char* items[], Enum& value)
		{
			bool selected = false;
			//static int item = 0;
			if (ImGui::BeginCombo(label, items[(int)value]))
			{
				for (int i = 0; i < numItems; i++)
				{
					if(ImGui::Selectable(items[i], (int)value == i))
					{
						value = (Enum&)i;
						selected = true;
					}
				}

				ImGui::EndCombo();
			}

			return selected;
		}

		//Creates a String Property Editor
		void StringProperty(const char* label, std::string& st);
		void PathProperty(const char* label, WinPath& p);

		//Creates a Vector3 Property Editor
		bool Vector2Property(const char* label, FVector2& v);
		bool Vector3Property(const char* label, FVector3& v);
		bool Vector4Property(const char* label, FVector4& v);

		bool Color3Property(const char* label, LinearColor3& v);
		bool Color4Property(const char* label, LinearColor4& v);

		//Creates a Rotator Property Editor
		bool RotatorProperty(const char* label, Rotator& r);

		//Creates a Transform Property Editor
		void TransformProperty(const char* label, Transform& t);

		//Creates a float property Editor
		bool FloatProperty(const char* label, float& f, float speed = .01f, float min = 0.0f, float max = 0.0f);

		bool IntProperty(const char* label, int& f, float speed = 1.0f, int min = 0, int max = 0);

		//Creates a bool property Editor
		bool  BoolProperty(const char* label, bool& b);

		//template<typename Enum>
		bool EnumProperty(const char* label, Projection& e);

		template<typename T>
		void AssetProperty(const char* label, Ref<T>& a);

		void TextureProperty(const char* label, Ref<Texture2D>& t);

		void MeshProperty(const char* label, Ref<Model>& m);

		void MaterialProperty(Ref<Material>& m);

		Entity m_Entity;
	};

	template<typename T>
	void PropertyDetailsBuilder::AssetProperty(const char* label, Ref<T>& a)
	{
		if (ImGui::BeginCombo(label, a.get() ? a->GetName().c_str() : ""))
		{
			int i = 0;
			if (ImGui::Selectable("None"))
			{
				a = nullptr;
			}

			for (auto& asset : AssetManager::GetAssets<T>())
			{
				ImGui::PushID(i++);
				std::string name = asset.second->GetName();
				if (ImGui::Selectable(name.c_str(), name == (a.get() ? a->GetName() : std::string(""))))
				{
					a = asset.second;
				}
				ImGui::PopID();
			}
			ImGui::EndCombo();
		}
	};
}