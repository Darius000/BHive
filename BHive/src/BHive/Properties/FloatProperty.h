#pragma once

#include "BaseProperty.h"

namespace BHive
{
	using FloatProperty = BH_Property<float>;

	template<>
	class BH_Property<float> : public BaseProperty<float>
	{
	public:
		BH_Property(){};
		BH_Property(const std::string& propertyName, float* val, float defaultValue = 0.0f,
			float min = 0.0f, float max = 0.0f, float speed = .1f,
			bool button = false, LinearColor4 color = { .5f, .5f, .5f, 1.0f }, bool columnspacing = true,
			Reflection::PropertyTags tags = (Reflection::PropertyTags)0,
			Reflection::PropertyMetaData metaData = (Reflection::PropertyMetaData)0, FunctionCallback callback = nullptr)
			:BaseProperty(propertyName, val, defaultValue, button, color, columnspacing, tags, metaData, callback),
			m_Speed(speed), m_Min(min), m_Max(max)
		{

		}

	protected:
		void OnImGuiDraw() override
		{
			auto flags = (m_Min != 0.0f || m_Max != 0.0f) ? ImGuiSliderFlags_AlwaysClamp : 0;

			if (ImGui::DragFloat(("##" + name).c_str(), value, m_Speed, m_Min, m_Max, "%.3f", flags))
			{
				CallCallbackFunction();
			}
		}

	private:
		float m_Speed;
		float m_Min;
		float m_Max;
	};
}