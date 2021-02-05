#pragma once

#include "Asset.h"
#include "BHive/Font/Font.h"
#include "BHive/Font/FontFamily.h"

namespace BHive
{
	class FontAsset : public IAssetType<Font>
	{
		DEFINE_ASSET_BODY(FontAsset, Font, "Font")
	};

	class FontFamilyAsset : public IAssetType<FontFamily>
	{
		DEFINE_ASSET_BODY(FontFamilyAsset, FontFamily, "FontFamily")
	};
}