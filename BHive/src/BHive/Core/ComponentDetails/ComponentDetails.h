#pragma once

#include "DetailsCustomization.h"

namespace BHive
{
	class TransformComponentDetails : public DetailsCustomization
	{
		
	public:
		void CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder) override;

	};

	class TagComponentDetails : public DetailsCustomization
	{
	public:

		void CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder) override;
	};

	class DirectionalLightComponentDetails : public DetailsCustomization
	{
	public:

		void CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder) override;
	};

	class PointLightComponentDetails : public DetailsCustomization
	{
	public:

		void CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder) override;
	};

	class SpotLightComponentDetails : public DetailsCustomization
	{
	public:

		void CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder) override;
	};

	class CameraComponentDetails : public DetailsCustomization
	{
	public:

		void CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder) override;
	};

	class RenderComponentDetails : public DetailsCustomization
	{
	public:

		void CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder) override;
	};

	class NativeScriptComponentDetails : public DetailsCustomization
	{
	public:
		void CreateCustomizedDetails(PropertyDetailsBuilder& detailsBuilder) override;
	};
}