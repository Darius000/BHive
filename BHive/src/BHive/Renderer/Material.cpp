#include "BHivePCH.h"
#include "Material.h"

namespace BHive
{

	void Material::Render()
	{
		if (m_Shader)
		{
			m_Shader->Bind();
			//m_Shader->SetMat4("u_Model", glm::mat4());

			OnShaderBind(m_Shader);
		}
	}

	void DefaultMaterial::OnShaderBind(Ref<Shader>& shader)
	{
		shader->SetVec4("material.color", m_Color);
	}

	void DefaultMaterial::SetColor(LinearColor color)
	{
		m_Color = color;
	}

	void LambertMaterial::OnShaderBind(Ref<Shader>& shader)
	{
		shader->SetVec3("material.color", FVector3(m_Color.r, m_Color.g, m_Color.b));
		shader->SetVec3("directionalLight.direction", FVector3(0.5f, 1.0f, 0.0f));
		shader->SetVec3("directionalLight.color", FVector3(1.0f));
		shader->SetFloat("directionalLight.brightness", 1.0f);
		shader->SetFloat("material.transparency", 1.0f);

	}

}