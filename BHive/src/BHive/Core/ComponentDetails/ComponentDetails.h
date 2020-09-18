#pragma once

#include "DetailsCustomization.h"

namespace BHive
{
	class TransformComponentDetails : public DetailsCustomization
	{
		
	public:
		void CreateCustomizedDetails(DetailsBuilder& detailsBuilder) override;

	};

	class TagComponentDetails : public DetailsCustomization
	{
	public:

		void CreateCustomizedDetails(DetailsBuilder& detailsBuilder) override;
	};

	class DirectionalLightComponentDetails : public DetailsCustomization
	{
	public:

		void CreateCustomizedDetails(DetailsBuilder& detailsBuilder) override;
	};

	class PointLightComponentDetails : public DetailsCustomization
	{
	public:

		void CreateCustomizedDetails(DetailsBuilder& detailsBuilder) override;
	};

	class SpotLightComponentDetails : public DetailsCustomization
	{
	public:

		void CreateCustomizedDetails(DetailsBuilder& detailsBuilder) override;
	};

	class CameraComponentDetails : public DetailsCustomization
	{
	public:

		void CreateCustomizedDetails(DetailsBuilder& detailsBuilder) override;
	};

	class RenderComponentDetails : public DetailsCustomization
	{
	public:

		void CreateCustomizedDetails(DetailsBuilder& detailsBuilder) override;
	};
}