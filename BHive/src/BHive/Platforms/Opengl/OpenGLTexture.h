#pragma once

#include "BHive/Renderer/Texture.h"


namespace BHive
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(BName TextureName, uint32 width, uint32 height, GLenum internalFormat = GL_RGBA8, GLenum dataFormat = GL_RGBA, void* data = nullptr);

		OpenGLTexture2D(const WinPath& path);
		virtual ~OpenGLTexture2D();

		virtual uint32 GetRendererID() const override { return m_RendererID; }
		virtual void Bind(uint32 slot = 0) const override;
		virtual void UnBind(uint32 slot = 0) const override;

	public:
		void InValidate() override;

	private:

		uint8 m_StbImageCreated = false;
	};
}