#pragma once

#include "BHive.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "BHive/Core/Utils/PlatformUtils.h"
#include "BHive/Font/Font.h"
//#include "BHive/Managers/AssetManagers.h"

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
		void Image(const Texture* texture, FVector2 size);
		void BeginProperty(const std::string& label);
		void EndProperty();
		std::string GetID(const std::string& label);

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

		bool ColorProperty8(const std::string& label, Color& p, int speed = 1)
		{
			bool changed = false;
			
			ImGui::Text(label.c_str());

			ImGui::PushID(label.c_str());

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 5.0f));
			ImGui::PushMultiItemsWidths(4, ImGui::CalcItemWidth());

			changed |= UInt8Property("R", p.r, speed, {1.0f, 0.0f, 0.0f, 1.0f});
			ImGui::SameLine();
			ImGui::PopItemWidth();

			changed |= UInt8Property("G", p.g, speed, { 0.0f, 1.0f, 0.0f, 1.0f });
			ImGui::SameLine();
			ImGui::PopItemWidth();

			changed |= UInt8Property("B", p.b, speed, { 0.0f, 0.0f, 1.0f, 1.0f });
			ImGui::SameLine();
			ImGui::PopItemWidth();

			changed |= UInt8Property("A", p.a, speed, { .5f, .5f, .5f, 1.0f });
			ImGui::PopItemWidth();

			ImGui::PopStyleVar();

			ImGui::PopID();

			return changed;
		}

		bool FloatProperty(const std::string& label, float& p, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0.0f, bool button = false, bool columnSpacing = true, ImVec4 color = { 1.0f, 0.0f, 0.0f, 1.0f })
		{
			bool changed = false;
			
			if(columnSpacing) ImGui::Columns(2, label.c_str(), false);

			if(button)
			{ 
				ImGui::PushStyleColor(ImGuiCol_Button, color);

				float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
				ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

				if (ImGui::Button(label.c_str(), buttonSize))
				{
					p = resetValue;
					changed = true;
				};
			}
			else
			{
				ImGui::Text(label.c_str());
			}

			columnSpacing ?  ImGui::NextColumn() : ImGui::SameLine();

			auto flags = (min != 0.0f || max != 0.0f)? ImGuiSliderFlags_AlwaysClamp : 0;

			if (ImGui::DragFloat(("##" + label).c_str(), &p, speed, min , max, "%.3f", flags))
			{
				changed = true;
			}

			if (ImGui::BeginPopupContextItem(label.c_str()))
			{
				if (ImGui::MenuItem("Reset Default"))
				{
					p = resetValue;
					changed = true;
				}

				ImGui::EndPopup();
			}

			if(button) ImGui::PopStyleColor();

			if(columnSpacing) ImGui::Columns();

			return changed;
		}

		bool UInt8Property(const std::string& label, uint8& p, int speed = 1, ImVec4 color = {1.0f, 0.0f, 0.0f, 1.0f})
		{
			bool changed = false;
			auto val = (int)(p);
			ImGui::PushStyleColor(ImGuiCol_Button, color);

			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

			if (ImGui::Button(label.c_str(), buttonSize))
			{
				val = 255;
			};

			ImGui::SameLine();

			if(ImGui::DragInt(("##" + label).c_str(), &val, (float)speed, 0, 255, "%d", ImGuiSliderFlags_AlwaysClamp ))
			{
				p = (uint8)(val);
				changed = true;
			}

			ImGui::PopStyleColor();

			return changed;
		}

		bool MultiStringProperty(const char* label, std::string& p, FVector2 size)
		{
			ImVec2 Size = ImVec2(size.x, size.y);

			ImGuiInputTextFlags flags = ImGuiInputTextFlags_CallbackResize | ImGuiInputTextFlags_AllowTabInput;
			InputTextCallback_UserData callback_user_data;
			callback_user_data.str = &p;
			ImGui::Text(label);
			bool edited = ImGui::InputTextMultiline((std::string("##") + label).c_str(), 
				(char*)p.c_str(), p.capacity(), Size, flags, InputTextCallback, &callback_user_data);
			return edited;
		};

		void EntityName(const std::string& label, std::string& p)
		{
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), p.c_str());
			auto inputTextlabel = "##" + label;
			ImGui::SetNextItemWidth(ImGui::GetContentRegionAvailWidth());
			if (ImGui::InputText(inputTextlabel.c_str(), buffer, sizeof(buffer)))
			{
				p = std::string(buffer);
			}
		};

		bool StringProperty(const std::string& label, std::string& p)
		{
			BeginProperty(label);

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), p.c_str());
			auto inputTextlabel = "##" + label;
			if (ImGui::InputText(inputTextlabel.c_str(), buffer, sizeof(buffer)))
			{
				p = std::string(buffer);
				return true;
			}

			EndProperty();

			return false;
		};

		template<>
		bool Property(const char* label, WinPath& p, float speed, float min, float max)
		{
			std::string file = "";
			//Add font drop down list
			ImGui::Text(p.GetName());
			ImGui::SameLine();
			auto texture = AssetManager::Get<Texture2D>("folder");
			if (ImGui::ImageButton((void*)texture.get(), ImVec2(20.0f, 20.0f), ImVec2(0, 1), ImVec2(1, 0)))
			{
				file = FileDialog::OpenFile("All\0*.*\0").c_str();
			}

			if (!file.empty())
			{
				p = WinPath(file.c_str());
				return true;
			}

			return false;
		}

		
		bool Vector2Property(const std::string& label, FVector2& p, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0.0f)
		{
			std::array<ImVec4, 2> colors = { ImVec4(1.0f, 0.0f, 0.0f, 1.0f), ImVec4(0.0f, 1.0f, 0.0f, 1.0f)};
			
			bool changed = false;

			ImGui::Columns(2, label.c_str(), false);

			ImGui::Text(label.c_str());

			ImGui::NextColumn();

			ImGui::PushID(label.c_str());

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 5.0f));
			ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());

			changed |= FloatProperty("X", p.x, speed, min , max,resetValue, true, false, colors[0]);
			ImGui::SameLine();
			ImGui::PopItemWidth();

			changed |= FloatProperty("Y", p.y, speed, min, max, resetValue , true, false, colors[1]);
			ImGui::PopItemWidth();

			ImGui::PopStyleVar();

			ImGui::PopID();

			ImGui::Columns();

			return changed;
		}

		bool Vector3Property(const std::string& label,  FVector3& p, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0.0f)
		{
			std::array<ImVec4, 3> colors = { ImVec4(1.0f, 0.0f, 0.0f, 1.0f), ImVec4(0.0f, 1.0f, 0.0f, 1.0f) , ImVec4(0.0f, 0.0f, 1.0f, 1.0f) };
			
			bool changed = false;

			ImGui::Columns(2, label.c_str(), false);

			ImGui::Text(label.c_str());

			ImGui::NextColumn();

			ImGui::PushID(label.c_str());

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 5.0f));
			ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());

			changed |= FloatProperty("X", p.x, speed, min, max, resetValue, true, false, colors[0]);
			ImGui::SameLine();
			ImGui::PopItemWidth();

			changed |= FloatProperty("Y", p.y, speed, min, max, resetValue, true, false, colors[1]);
			ImGui::SameLine();
			ImGui::PopItemWidth();

			changed |= FloatProperty("Z", p.z, speed, min, max, resetValue, true, false, colors[2]);
			ImGui::PopItemWidth();

			ImGui::PopStyleVar();

			ImGui::PopID();

			ImGui::Columns();

			return changed;
		}

		bool RotatorProperty(const std::string& label, Rotator& p, float speed = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0.0f)
		{
			std::array<ImVec4, 3> colors = { ImVec4(1.0f, 0.0f, 0.0f, 1.0f), ImVec4(0.0f, 1.0f, 0.0f, 1.0f) , ImVec4(0.0f, 0.0f, 1.0f, 1.0f) };

			bool changed = false;

			ImGui::Columns(2, label.c_str(), false);

			ImGui::Text(label.c_str());

			ImGui::NextColumn();

			ImGui::PushID(label.c_str());

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 5.0f));
			ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());

			changed |= FloatProperty("X", p.x, speed, min, max, resetValue, true, false, colors[0]);
			ImGui::SameLine();
			ImGui::PopItemWidth();

			changed |= FloatProperty("Y", p.y, speed, min, max, resetValue, true, false, colors[1]);
			ImGui::SameLine();
			ImGui::PopItemWidth();

			changed |= FloatProperty("Z", p.z, speed, min, max, resetValue, true, false, colors[2]);
			ImGui::PopItemWidth();

			ImGui::PopStyleVar();

			ImGui::PopID();

			ImGui::Columns();

			return changed;
		}

		bool Vector4Property(const std::string& label, FVector4& p, float speed  = 1.0f, float min = 0.0f, float max = 0.0f, float resetValue = 0.0f)
		{
			std::array<ImVec4, 4> colors = { ImVec4(1.0f, 0.0f, 0.0f, 1.0f), ImVec4(0.0f, 1.0f, 0.0f, 1.0f) , ImVec4(0.0f, 0.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 1.0f) };
			
			bool changed = false;

			ImGui::Columns(2, label.c_str(), false);

			ImGui::Text(label.c_str());

			ImGui::NextColumn();

			ImGui::PushID(label.c_str());

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 5.0f));
			ImGui::PushMultiItemsWidths(4, ImGui::CalcItemWidth());

			changed |= FloatProperty("X", p.x, speed, min, max, resetValue, true, false, colors[0]);
			ImGui::SameLine();
			ImGui::PopItemWidth();

			changed |= FloatProperty("Y", p.y, speed, min, max, resetValue, true, false, colors[1]);
			ImGui::SameLine();
			ImGui::PopItemWidth();

			changed |= FloatProperty("Z", p.z, speed, min, max, resetValue, true, false, colors[2]);
			ImGui::SameLine();
			ImGui::PopItemWidth();

			changed |= FloatProperty("W", p.w, speed, min, max, resetValue, true, false, colors[3]);
			ImGui::PopItemWidth();

			ImGui::PopStyleVar();

			ImGui::PopID();

			ImGui::Columns();

			return changed;
		}
														   
		bool Color3Property(const std::string& label, LinearColor3& p, bool hdr = false, ImGuiColorEditFlags flags = 0)
		{
			flags += ImGuiColorEditFlags_Float;
			if (hdr) flags += ImGuiColorEditFlags_HDR ;

			ImGui::Columns(2, label.c_str(), false);

			ImGui::Text(label.c_str());

			ImGui::NextColumn();

			ImGui::PushID(label.c_str());

			bool changed = false;
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImVec2 buttonSize = {ImGui::CalcItemWidth(), lineHeight };

			ImVec4 color = {p.r, p.g, p.b, 1.0f};
			if(ImGui::ColorButton(GetID(label).c_str(), color, 0, buttonSize))
			{
				// open a picker
				ImGui::OpenPopup("ColorPicker");	
			}

			if (ImGui::BeginPopup("ColorPicker"))
			{			
				if(ImGui::ColorPicker3(label.c_str(), *p , flags)) 
					changed = true;

				ImGui::EndPopup();
			}

			ImGui::PopID();

			ImGui::Columns();

			return changed;
		}

		bool Color4Property(const std::string& label, LinearColor4& p, bool hdr = false, ImGuiColorEditFlags flags = 0)
		{
			flags += ImGuiColorEditFlags_Float;
			if (hdr) flags += ImGuiColorEditFlags_HDR;

			ImGui::Columns(2, label.c_str(), false);

			ImGui::Text(label.c_str());

			ImGui::NextColumn();

			ImGui::PushID(label.c_str());

			bool changed = false;
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImVec2 buttonSize = { ImGui::CalcItemWidth(), lineHeight };

			ImVec4 color = { p.r, p.g, p.b, p.a };
			if (ImGui::ColorButton(GetID(label).c_str(), color, 0, buttonSize))
			{
				// open a picker
				ImGui::OpenPopup("ColorPicker");
			}

			if (ImGui::BeginPopup("ColorPicker"))
			{
				if (ImGui::ColorPicker4(label.c_str(), *p, flags))
					changed = true;

				ImGui::EndPopup();
			}

			ImGui::PopID();

			ImGui::Columns();

			return changed;
		}

		bool TransformProperty(const char* label, Transform& p, float speed = 1.0f, float min = 0.0f, float max = 0.0f)
		{
			ImGui::Text(label);
			ImGui::Separator();
			bool changed = false;

			if (Vector3Property("Position", p.GetPosition(), speed, min, max))
			{
				p.RecalulateModelMatrix();
				changed = true;
			}

			if (RotatorProperty("Rotation", p.GetRotation(), speed, min, max))
			{
				p.RecalulateModelMatrix();
				changed = true;
			}
				
			if(Vector3Property("Scale",  p.GetScale(), speed, min, max, 1.0f))
			{
				p.RecalulateModelMatrix();
				changed = true;
			}

			return changed;
		}

		template<>
		bool Property(const char* label, int& p, float speed, float min, float max)
		{
			return ImGui::DragInt(label, &p, speed, (int)min, (int)max);
		}

		bool BoolProperty(const std::string& label, bool& p, bool resetValue = false)
		{
			bool changed = false;

			ImGui::Columns(2, label.c_str(), false);
	
			ImGui::Text(label.c_str());
		
			ImGui::NextColumn();

			if (ImGui::Checkbox(("##" + label).c_str(), &p))
			{
				changed = true;
			}

			if (ImGui::BeginPopupContextItem(label.c_str()))
			{
				if (ImGui::MenuItem("Reset Default"))
				{
					p = resetValue;
					changed = true;
				}

				ImGui::EndPopup();
			}

			ImGui::Columns();

			return changed;
		}

		template<typename Enum, size_t numItems>
		bool EnumProperty(const std::string& label, const char* items[], Enum& value)
		{
			bool changed = false;

			ImGui::Columns(2, label.c_str(), false);

			ImGui::Text(label.c_str());

			ImGui::NextColumn();

			int index = (int)value;
			if (ImGui::BeginCombo(label.c_str(), items[index]))
			{
				for (int i = 0; i < numItems; i++)
				{
					if (ImGui::Selectable(items[i], index == i))
					{
						value = (Enum&)i;
						changed = true;
					}
				}

				ImGui::EndCombo();
			}
			
			ImGui::Columns();

			return changed;
		}

		template<typename T>
		void AssetProperty(const std::string& label, Ref<T>& a)
		{
			BeginProperty(label);

			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImVec2 comboSize = ImVec2(ImGui::GetContentRegionAvailWidth(), lineHeight);

			//ImGui::SetNextWindowSizeConstraints(ImVec2(0,0), comboSize);

			if (ImGui::BeginCombo("", a.get() ? a->GetName().c_str() : ""))
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
			
			EndProperty();
		}

		template<typename T>
		void Property(const char* label, Ref<T>& a)
		{
			AssetProperty_Impl(label, a);
		}

		/*template<>
		void AssetProperty_Impl(const std::string& label, Ref<Material>& a)
		{
			ImGui::PushID(GetID(label).c_str());
			if (ImGui::BeginCombo(GetID(label).c_str(), a.get() ? a->GetName().c_str() : ""))
			{
				int i = 0;

				DefaultAssetProperty<Material>(a);

				for (auto& asset : AssetManager::GetAssets<Material>())
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

			ImGui::PopID();
		}*/

		template<>
		void Property(const char* label, Ref<Font>& a)
		{
			if (ImGui::BeginCombo(GetID(label).c_str(), a.get() ? a->GetName().c_str() : ""))
			{
				int i = 0;

				DefaultAssetProperty<Font>(a);

				for (auto& asset : AssetManager::GetAssets<Font>())
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
		}

		/*template<>
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
		}*/

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

	template<typename T>
	inline ImVec4 operator*(const ImVec4& v, T s)
	{
		return ImVec4(v.x * s, v.y * s, v.z * s, v.w * s);
	}
}