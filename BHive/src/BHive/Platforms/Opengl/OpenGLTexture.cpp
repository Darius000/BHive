#include "BHivePCH.h"
#include "OpenGLTexture.h"

#include "stb_image.h"



namespace BHive
{
	OpenGLTexture2D::OpenGLTexture2D(const WinPath& path)
		:m_Path(path), m_DataFormat(0), m_InternalFormat(0)
	{
		m_Name = path.GetName();

		stbi_set_flip_vertically_on_load(1);

		int width, height, channels;
		m_Data = stbi_load(*path, &width, &height, &channels, 0);

		BH_CORE_ASSERT(m_Data, "failed to load image!");
		m_Width = width;
		m_Height = height;
		uint32 Channels = channels;

		if (channels == 4)
		{
			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			m_InternalFormat = GL_RGB8;
			m_DataFormat = GL_RGB;
		}

		BH_CORE_ASSERT(m_InternalFormat & m_DataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat , m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, m_Data);
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32 width, uint32 height,  GLenum internalFormat, GLenum dataFormat)
		:m_Width(width), m_Height(height), m_Path(""), m_InternalFormat(internalFormat), m_DataFormat(dataFormat), m_Data(nullptr)
	{
		m_Name = "Texture" + m_RendererID;

		BH_CORE_ASSERT(m_InternalFormat & m_DataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		stbi_image_free(m_Data);

		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32 slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32 size)
	{
		m_Data = (uint8*)(data);
		uint32 bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		BH_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, m_Data);
	}
}
