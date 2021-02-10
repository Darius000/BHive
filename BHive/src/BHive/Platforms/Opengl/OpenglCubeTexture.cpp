#include "BHivePCH.h"
#include "OpenglCubeTexture.h"

#include "stb_image.h"
#include <glad/glad.h>

namespace BHive
{

	OpenglCubeTexture::OpenglCubeTexture(const std::array<WinPath, 6>& paths)
	{
		//Create texture
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);

		m_FaceData.resize(paths.size());

		

		//Load texture data
		for (uint32 i = 0; i < paths.size(); i++)
		{
			CubeTexFaceData& FaceData = m_FaceData[i];
			IVector2 size = {};
			int channels; 

			stbi_set_flip_vertically_on_load(false);

			FaceData.m_Path = paths[i];
			FaceData.m_PixelData.m_Data = stbi_load(paths[i].c_str(), &size.x, &size.y, &channels, 0);

			FaceData.m_Size = size;
			FaceData.m_Channels = channels;

			if (channels == 4)
			{
				FaceData.m_PixelData.m_InternalFormat = GL_RGBA8;
				FaceData.m_PixelData.m_DataFormat = GL_RGBA;
			}
			else if (channels == 3)
			{
				FaceData.m_PixelData.m_InternalFormat = GL_RGB8;
				FaceData.m_PixelData.m_DataFormat = GL_RGB;
			}
			else if (channels == 1)
			{
				FaceData.m_PixelData.m_InternalFormat = GL_R8;
				FaceData.m_PixelData.m_DataFormat = GL_RED;
			}

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, FaceData.m_PixelData.m_InternalFormat,
			FaceData.m_Size.x, FaceData.m_Size.y, 0, FaceData.m_PixelData.m_DataFormat, GL_UNSIGNED_BYTE , FaceData.m_PixelData.m_Data);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, ColorMethodToGLEnum(m_MagFilterColorMethod));
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, ColorMethodToGLEnum(m_MinFilterColorMethod));
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, TilingMethodToGLEnum(m_TilingMethod));
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, TilingMethodToGLEnum(m_TilingMethod));
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, TilingMethodToGLEnum(m_TilingMethod));
	}

	void OpenglCubeTexture::Bind(uint32 slot) const
	{
		glBindTextureUnit(slot, m_ID);
	}

	void OpenglCubeTexture::UnBind(uint32 slot) const
	{
		glBindTextureUnit(slot, 0);
	}

}