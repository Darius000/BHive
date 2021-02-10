#pragma once

#include "Renderer/Texture.h"

namespace BHive
{
	struct CubeTexFaceData
	{
		IVector2 m_Size;
		uint32 m_Channels;
		WinPath m_Path;
		FPixelData m_PixelData;
	};

	class OpenglCubeTexture : public CubeTexture
	{
	public:
		OpenglCubeTexture(const std::array<WinPath, 6>& paths);

		void Bind(uint32 slot) const override;
		void UnBind(uint32 slot) const override;

		uintPtr GetRendererID() const override { return m_ID; };

	private:
		std::vector<CubeTexFaceData> m_FaceData;

		TilingMethod m_TilingMethod = TilingMethod::ClampToEdge;

		MinColorMethod m_MinFilterColorMethod = MinColorMethod::Linear;

		MagColorMethod m_MagFilterColorMethod = MagColorMethod::Linear;

		uint32 m_ID;
	};
}