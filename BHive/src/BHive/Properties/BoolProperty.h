#pragma once

#include "BaseProperty.h"

namespace BHive
{
	using BoolProperty = BH_Property<bool>;

	template<>
	class BH_Property<bool> : public BaseProperty<bool>
	{
	public:
		BH_Property(const std::string& propertyName, bool* val, bool defaultValue = false,
			bool button = false, LinearColor4 color = { .5f, .5f, .5f, 1.0f }, bool columnspacing = true,
			Reflection::PropertyTags tags = (Reflection::PropertyTags)0,
			Reflection::PropertyMetaData metaData = (Reflection::PropertyMetaData)0, FunctionCallback callback = nullptr)
			:BaseProperty(propertyName, val, defaultValue, button, color, columnspacing, tags, metaData, callback)
		{

		}

	protected:
		void OnImGuiDraw() override
		{
			if (ImGui::Checkbox(("##" + name).c_str(), value))
			{
				CallCallbackFunction();
			}
		}
	};
}