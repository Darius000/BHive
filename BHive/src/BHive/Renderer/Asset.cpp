#include "BHivePCH.h"
#include "Asset.h"
#include "Texture.h"

namespace BHive
{

	Asset::Asset(const std::string& name) : m_Name(name), m_Thumbnail(nullptr)
	{

	}

	std::string Asset::GetName() const
	{
		return m_Name;
	}

	Texture2D* Asset::GetThumbnail() const
	{
		return m_Thumbnail;
	}

	uint32 Asset::GetThumnailID() const
	{
		return m_Thumbnail->GetRendererID();
	}

}