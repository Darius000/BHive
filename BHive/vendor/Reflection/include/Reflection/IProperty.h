#pragma once

#include <string>
#include "PropertySpecifiers.h"

namespace Reflection
{
	class IProperty
	{
	public:
		IProperty() = default;
		IProperty(const IProperty&) = default;
		virtual ~IProperty() = default;
		virtual std::string GetName() = 0;
		virtual std::string GetTypeName() = 0;
		virtual const PropertyTags& GetTags() const = 0;
		virtual const PropertyMetaData& GetMetaData() const = 0;
		virtual void PrintValue() const = 0;
	};
}
