#pragma once

#include "EnumOperators.h"

namespace Reflection
{	
	enum class ClassTags : int
	{
		Abstract,
		Group,
		Placeable
	};

	enum class ClassMetaData : int
	{
		Component,
		ToolTip
	};

	DEFINE_ENUM_OPERATORS(ClassTags, int)
	DEFINE_ENUM_OPERATORS(ClassMetaData ,int)
}