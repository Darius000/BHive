#include "BHivePCH.h"
#include "Texture.h"
#include <stb_image.h>

namespace BHive
{
	Texture::Texture()
		:m_PixelData(nullptr), m_TextureData(0),
		m_Width(0), m_Height(0), m_NumChannels(0), m_Size(0)
	{
	}

	unsigned int Texture::GetIconData() const
	{
		return m_TextureData;
	}

	void Texture::OnSave(std::ofstream& resourceFile, const String& resourceFilePath)
	{
		BResource::OnSave(resourceFile, resourceFilePath);

		stbi_set_flip_vertically_on_load(true);
		m_PixelData = stbi_load(resourceFilePath.c_str(), &m_Width, &m_Height, &m_NumChannels, 0);
		m_Size = m_NumChannels * m_Width * abs(m_Height);
		resourceFile << m_Size << " " << m_Width << " " << m_Height << " " << m_NumChannels << std::endl;
		resourceFile.write(reinterpret_cast<const char*>(m_PixelData), m_Size);
		LoadResource();
	}

	void Texture::OnLoad(std::ifstream& resourceFile)
	{
		BResource::OnLoad(resourceFile);

		String line;
		resourceFile >> m_Size >> m_Width >> m_Height >> m_NumChannels;
		getline(resourceFile, line);
		m_PixelData = new unsigned char[m_Size];
		resourceFile.read(reinterpret_cast<char*>(m_PixelData), m_Size);
		LoadResource();
	}

	void Texture::LoadResource()
	{
		BH_CORE_ASSERT("Failed to load texture", m_PixelData);

		glGenTextures(1, &m_TextureData);
		glBindTexture(GL_TEXTURE_2D, m_TextureData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		GLint internalFormat = GL_RGB;

		if (m_NumChannels == 1)
		{
			internalFormat = GL_RED;
		}
		if (m_NumChannels == 3)
		{
			internalFormat = GL_RGB;
		}
		if (m_NumChannels == 4)
		{
			internalFormat = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, internalFormat, GL_UNSIGNED_BYTE, m_PixelData);

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(m_PixelData);
	}

	unsigned int Texture::GetTextureData() const
	{
		return m_TextureData;
	}
}
