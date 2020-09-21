#pragma once

#include "PropertyDetailsBuilder.h"

namespace BHive
{ 
	class DetailsCustomization
	{
	public:
		DetailsCustomization() = default;
		DetailsCustomization(const DetailsCustomization&) = default;
		virtual ~DetailsCustomization() = default;

		virtual void CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder){};
	};
}