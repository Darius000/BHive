#pragma once

#include "BaseProperty.h"

namespace BHive
{
	using FVector2Property = BH_Property<Vector2<float>>;
	using UVector2Property = BH_Property<Vector2<uint32>>;
	using IVector2Property = BH_Property<Vector2<int32>>;
	using BVector2Property = BH_Property<Vector2<bool>>;


	template<typename U>
	class BH_Property<Vector2<U>> : public BaseProperty<Vector2<U>>
	{

		using FunctionCallback = void(*)(Vector2<U>);
	public:
		
		BH_Property(const std::string& propertyName, Vector2<U>* val, Vector2<U> defaultValue = Vector2<U>(),
			U min = (U)0, U max = (U)0, U speed = (U)1,
			LinearColor4 color = { .5f, .5f, .5f, 1.0f },
			Reflection::PropertyTags tags = (Reflection::PropertyTags)0,
			Reflection::PropertyMetaData metaData = (Reflection::PropertyMetaData)0, FunctionCallback callback = nullptr)
			:BaseProperty(propertyName, val, defaultValue, false, color, true, tags, metaData, callback),
			m_Speed(speed), m_Min(min), m_Max(max)
		{
			X = BH_Property<U>("X", &value->x, m_DefaultValue.x, m_Min, m_Max, m_Speed, true, { 1.0f, 0.0f, 0.0f, 1.0f }, false);
			Y = BH_Property<U>("Y", &value->y, m_DefaultValue.y, m_Min, m_Max, m_Speed, true, { 0.0f, 1.0f, 0.0f, 1.0f }, false);
		};

	protected:
		void OnImGuiDraw() override
		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 5.0f));
			ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());

			X.OnImGuiRender();

			ImGui::SameLine();
			ImGui::PopItemWidth();

			Y.OnImGuiRender();

			ImGui::PopItemWidth();

			ImGui::PopStyleVar();
		};

	private:
		U m_Speed;
		U m_Min;
		U m_Max;
		BH_Property<U> X;
		BH_Property<U> Y;
	};
};