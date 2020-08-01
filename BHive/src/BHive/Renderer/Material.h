#pragma  once

#include "Shader.h"

namespace BHive
{
	class Material
	{
	public:
		Material():m_Shader(nullptr){};
		virtual ~Material(){};

		void Render();
		virtual void OnShaderBind(Ref<Shader>& shader) = 0;

	protected:
		Ref<Shader> m_Shader;

		friend class Model;
	};

	class DefaultMaterial : public Material
	{
	public:
		DefaultMaterial()
		{
			m_Shader = ShaderLibrary::Get("Default");
		}
		virtual ~DefaultMaterial(){}

		virtual void OnShaderBind(Ref<Shader>& shader) override;

		void SetColor(LinearColor color);

	protected:
		LinearColor m_Color;
	};

	class LambertMaterial : public DefaultMaterial
	{
	public:
		LambertMaterial()
		{
			m_Shader = ShaderLibrary::Get("Lambert");
		}
		virtual ~LambertMaterial(){}

		virtual void OnShaderBind(Ref<Shader>& shader) override;
	};
}