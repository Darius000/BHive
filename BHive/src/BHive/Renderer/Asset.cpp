#include "BHivePCH.h"
#include "Asset.h"
#include "Texture.h"

namespace BHive
{

	Asset::Asset(const std::string& name) : m_Name(name)
	{

	}

	std::string& Asset::GetName()
	{
		return m_Name;
	}
}