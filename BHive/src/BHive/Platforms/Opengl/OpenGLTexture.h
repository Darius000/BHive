#pragma once

#include "BHive/Renderer/Texture.h"


namespace BHive
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32 width, uint32 height, GLenum internalFormat = GL_RGBA8, GLenum dataFormat = GL_RGBA);
		OpenGLTexture2D(const WinPath& path);
		virtual ~OpenGLTexture2D();

		virtual uint32 GetWidth() const override { return m_Width; }
		virtual uint32 GetHeight() const override { return m_Height; }
		virtual uint8* GetData() const override { return m_Data; }
		virtual BName GetName() const override { return m_Name; }

		virtual void Bind(uint32 slot = 0) const override;

		virtual void SetData(void* data, uint32 size) override;

	private:
		BName m_Name;
		WinPath m_Path;
		uint32 m_Width;
		uint32 m_Height;
		uint8* m_Data;
		uint32 m_RendererID;
		GLenum m_InternalFormat;
		GLenum m_DataFormat;
	};
}