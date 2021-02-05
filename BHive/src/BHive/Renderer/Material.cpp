#include "BHivePCH.h"
#include "Material.h"
#include "Managers/AssetManagers.h"

namespace BHive
{

	Material::Material(Ref<Shader> shader) 
		:m_Shader(shader)
	{

	}

	Material::Material()
	{

	}

	void Material::Render()
	{
		if (m_Shader)
		{
			m_Shader->SetUniforms();
		}
	}
}