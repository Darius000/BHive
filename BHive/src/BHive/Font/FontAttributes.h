#pragma once

#include "Core/Core.h"
#include "Font.h"

namespace BHive
{
	struct FontAttributes
	{
		std::string m_Name;
		Ref<Font> m_Font = nullptr;
	};
}