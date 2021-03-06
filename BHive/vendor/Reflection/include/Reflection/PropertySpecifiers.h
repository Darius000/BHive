#pragma once

#include "EnumOperators.h"

namespace Reflection
{
	enum class PropertyTags : int
	{
		None,
		AdvancedDisplay,
		Callable,
		ReadOnly,
		ReadWrite,
		EditAnywhere,
		EditInline,
		Instanced,
		VisibleAnywhere,
		ToolTip,
		Public,
		Protected,
		Private
	};

	enum class PropertyMetaData : int
	{
		None,
		ClampMin,
		ClampMax,
		DisplayName,
		DisplayPriority,
		EditCondition
	};

	DEFINE_ENUM_OPERATORS(PropertyTags, int)
	DEFINE_ENUM_OPERATORS(PropertyMetaData, int)
}