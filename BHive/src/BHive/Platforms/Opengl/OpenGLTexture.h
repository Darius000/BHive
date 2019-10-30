#pragma once

#include "BHive/Renderer/Texture.h"

namespace BHive
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const BString& path);
		virtual ~OpenGLTexture2D();

		virtual uint32 GetWidth() const override { return m_Width; }
		virtual uint32 GetHeight() const override { return m_Height; }

		virtual void Bind(uint32 slot = 0) const override;

	private:
		BString m_Path;
		uint32 m_Width;
		uint32 m_Height;
		uint32 m_Channels;
		uint32 m_RendererID;
	};
}