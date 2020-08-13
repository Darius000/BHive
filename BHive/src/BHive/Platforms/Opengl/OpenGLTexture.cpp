#include "BHivePCH.h"
#include "OpenGLTexture.h"

#include "stb_image.h"



namespace BHive
{
	OpenGLTexture2D::OpenGLTexture2D(const WinPath& path)
		:Texture2D(path.GetName())
	{
		stbi_set_flip_vertically_on_load(true);

		int width, height, channels;
		PixelData.m_Data = stbi_load(*path, &width, &height, &channels, 0);

		BH_CORE_ASSERT(PixelData.m_Data, "failed to load image!");
		m_Name  = path.GetName();
		m_Path = path;
		m_Width = width;
		m_Height = height;
		m_Channels = channels;

		if (m_Channels == 4)
		{
			PixelData.m_InternalFormat = GL_RGBA8;
			PixelData.m_DataFormat = GL_RGBA;
		}
		else if (m_Channels == 3)
		{
			PixelData.m_InternalFormat = GL_RGB8;
			PixelData.m_DataFormat = GL_RGB;
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
	
		InValidate();

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, PixelData.m_DataFormat, GL_UNSIGNED_BYTE, PixelData.m_Data);
		glGenerateMipmap(m_RendererID);

		m_StbImageCreated = true;
	}

	OpenGLTexture2D::OpenGLTexture2D(BName TextureName, uint32 width, uint32 height,  GLenum internalFormat, GLenum dataFormat, void* data)
		:Texture2D(TextureName)
	{
		m_Width = width;
		m_Height = height;
		m_Path = "";
		PixelData.m_DataFormat = dataFormat;
		PixelData.m_InternalFormat = internalFormat;
		PixelData.m_Data = static_cast<uint8*>(data);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

		InValidate();

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, PixelData.m_DataFormat, GL_UNSIGNED_BYTE, PixelData.m_Data);
		glGenerateMipmap(m_RendererID);

		m_StbImageCreated = false;
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);

		if(m_StbImageCreated) 
		{
			stbi_image_free(PixelData.m_Data);
		}
	}

	void OpenGLTexture2D::Bind(uint32 slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}


	void OpenGLTexture2D::InValidate()
	{
		
		BH_CORE_ASSERT(PixelData.m_InternalFormat & PixelData.m_DataFormat, "Format not supported!");

		glTextureStorage2D(m_RendererID, 1, PixelData.m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, ColorMethodToGLEnum(m_MinFilterColorMethod));
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, ColorMethodToGLEnum(m_MagFilterColorMethod));

		if (m_TilingMethod == TilingMethod::ClampToBorder)
		{
			glTextureParameterfv(m_RendererID, GL_TEXTURE_BORDER_COLOR, *m_BorderColor);
		}

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, TilingMethodToGLEnum(m_TilingMethod));
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, TilingMethodToGLEnum(m_TilingMethod));		
	}
}
