#pragma once

#include "Renderer/Texture.h"

namespace BHive
{
	

	class OpenglCubeTexture : public CubeTexture
	{
	public:
		OpenglCubeTexture(const std::string& name, const std::array<WinPath, 6>& paths);

		void Bind(uint32 slot) const override;
		void UnBind(uint32 slot) const override;


		void InValidate() override;

	private:
		

		TilingMethod m_TilingMethod = TilingMethod::ClampToEdge;

		MinColorMethod m_MinFilterColorMethod = MinColorMethod::Linear;

		MagColorMethod m_MagFilterColorMethod = MagColorMethod::Linear;
	};
}