#pragma once

#include "BHive.h"

namespace BHive
{
	struct InputTextCallback_UserData
	{
		std::string* str;
	};

	static int InputTextCallback(ImGuiInputTextCallbackData* data)
	{
		InputTextCallback_UserData* userdata = (InputTextCallback_UserData*)data->UserData;
		if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
		{
			std::string* str = userdata->str;
			IM_ASSERT(data->Buf == str->c_str());
			str->resize(data->BufTextLen);
			data->Buf = (char*)str->c_str();
		}

		return 0;
	}

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

		template<typename T>
		bool Property(const char* label , T& p, float speed = 1.0f, float min = 0.0f, float max = 0.0f)
		{
			return false;
		}

		template<typename T>
		bool Property(const char* label, T* p, float speed = 1.0f, float min = 0.0f, float max = 0.0f)
		{
			return false;
		}

		template<>
		bool Property(const char* label, std::string* p, float speed, float min, float max)
		{
			ImVec2 Size = ImVec2(1000, 300);

			ImGuiInputTextFlags flags = ImGuiInputTextFlags_CallbackResize | ImGuiInputTextFlags_AllowTabInput;
			InputTextCallback_UserData callback_user_data;
			callback_user_data.str = p;
			return ImGui::InputTextMultiline(label, (char*)p->c_str(), p->capacity(), Size, flags, InputTextCallback, &callback_user_data);
		};

		template<>
		bool Property(const char* label, std::string& p,  float speed, float min, float max)
		{
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), p.c_str());
			if (ImGui::InputText(label, buffer, sizeof(buffer)))
			{
				p = std::string(buffer);
				return true;
			}

			return false;
		};

		template<>
		bool Property(const char* label, WinPath& p, float speed, float min, float max)
		{
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), p.GetPath());
			if (ImGui::InputText(label, buffer, sizeof(buffer)))
			{
				p = WinPath(buffer);
				return true;
			}

			return false;
		}

		template<>
		bool Property(const char* label, FVector2& p, float speed, float min, float max)
		{
			return ImGui::DragFloat2(label, *p, speed, min, max);
		}

		template<>
		bool Property(const char* label, FVector3& p, float speed, float min, float max)
		{
			return ImGui::DragFloat3(label, *p, speed, min, max);
		}

		template<>
		bool Property(const char* label, Rotator& p, float speed, float min, float max)
		{
			return ImGui::DragFloat3(label, *p, speed, min, max);
		}

		template<>
		bool Property(const char* label, FVector4& p, float speed, float min, float max)
		{
			return ImGui::DragFloat4(label, *p, speed, min, max);
		}

		template<typename T>
		bool ColorProperty(const char* label, T& p, ImGuiColorEditFlags flags = 0)
		{
			return ImGui::ColorEdit3(label, *p, flags);
		}

		template<>
		bool ColorProperty(const char* label, LinearColor3& p, ImGuiColorEditFlags flags)
		{
			return ImGui::ColorEdit3(label, *p, flags);
		}

		template<>
		bool ColorProperty(const char* label, LinearColor4& p, ImGuiColorEditFlags flags)
		{
			return ImGui::ColorEdit4(label, *p);
		}

		template<>
		bool Property(const char* label, Transform& p, float speed, float min, float max)
		{
			ImGui::Text(label);
			if (PropertyDetailsBuilder::Property("Position", p.GetPosition()) |
				PropertyDetailsBuilder::Property("Rotation", p.GetRotation()) |
				PropertyDetailsBuilder::Property("Scale", p.GetScale()))
			{
				p.RecalulateModelMatrix();
				return true;
			}

			return false;
		}

		template<>
		bool Property(const char* label, float& p, float speed, float min, float max)
		{
			return ImGui::DragFloat(label, &p, speed, min, max);
		}

		template<>
		bool Property(const char* label, int& p, float speed, float min, float max)
		{
			return ImGui::DragInt(label, &p, speed, (int)min, (int)max);
		}

		template<>
		bool Property(const char* label, bool& p, float speed, float min, float max)
		{
			return ImGui::Checkbox(label, &p);
		}

		template<typename Enum, size_t numItems>
		bool Property(const char* label, const char* items[], Enum& value)
		{
			bool selected = false;
			//static int item = 0;
			if (ImGui::BeginCombo(label, items[(int)value]))
			{
				for (int i = 0; i < numItems; i++)
				{
					if (ImGui::Selectable(items[i], (int)value == i))
					{
						value = (Enum&)i;
						selected = true;
					}
				}

				ImGui::EndCombo();
			}

			return selected;
		}

		template<typename T>
		void AssetProperty_Impl(const char* label, Ref<T>& a)
		{
			//ImGui::BeginTooltip();
			//ImGui::SetTooltip(a ? a->GetName().c_str() : "");
			if (ImGui::BeginCombo(label, a.get() ? a->GetName().c_str() : ""))
			{
				int i = 0;

				DefaultAssetProperty<T>(a);

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
			//ImGui::EndTooltip();
		}

		template<typename T>
		void Property(const char* label, Ref<T>& a)
		{
			AssetProperty_Impl(label, a);
		}

		template<>
		void Property(const char* label, Ref<Texture2D>& t) 
		{
			float ImageSize = 100.0f;
			float RegionWidth = ImGui::GetWindowContentRegionWidth();
			float width = RegionWidth - (ImageSize + RegionWidth * .5f);
			ImGui::Image(t ? (void*)t->GetRendererID() : (void*)-1, ImVec2(ImageSize, ImageSize), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::SameLine();
			ImGui::PushItemWidth(width);
			AssetProperty_Impl(label, t);
			ImGui::PopItemWidth();
		}

		Entity m_Entity;

	private:
		template<typename T>
		void DefaultAssetProperty(Ref<T>& a);
	};

	template<typename T>
	inline void PropertyDetailsBuilder::DefaultAssetProperty(Ref<T>& a)
	{
		if (ImGui::Selectable("None"))
		{
			a = AssetManager::Get<T>("Default");
		}
	}

	template<>
	inline void PropertyDetailsBuilder::DefaultAssetProperty(Ref<Model>& a)
	{
		if (ImGui::Selectable("None"))
		{
			a = nullptr;
		}
	}

	template<>
	inline void PropertyDetailsBuilder::DefaultAssetProperty(Ref<Texture2D>& a)
	{
		if (ImGui::Selectable("None"))
		{
			a = nullptr;
		}
	}
}