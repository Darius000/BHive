#include "BHivePCH.h"
#include "Texture2D.h"
#include "stb_image.h"

namespace BHive
{
	Texture2D::Texture2D()
		:Wrapping(EWrapping::REPEAT), Filter(EFilter::LINEAR), MipMap(EMipMap::LINEAR), BorderColor(1.0f)
	{

	}


	Texture2D::Texture2D(const std::string fileName, const std::string &directory, ETextureType InType, bool gamma, EWrapping wrapping, EMipMap mipmap, EFilter filter, glm::vec3 borderColor)
		:Texture2D()
	{
		LoadTexture(fileName, directory, gamma);

		Type = InType;
		Wrapping = wrapping;
		MipMap = mipmap;
		Filter = filter;
		BorderColor = borderColor;
	}

	Texture2D::~Texture2D()
	{
	}

	void Texture2D::LoadTexture(const std::string fileName, const std::string &directory, bool gamma)
	{
		GLint internalFormat;

		std::string filename = std::string(fileName);
		filename = directory + "/" + filename;

		Name = fileName;

		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filename.c_str(), &width, &height, &numChannels, 0);

		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);

		if (data)
		{
			if (numChannels == 1)
			{
				internalFormat = GL_RED;
			}
			if (numChannels == 3)
			{
				internalFormat = GL_RGB;
			}
			if (numChannels == 4)
			{
				internalFormat = GL_RGBA;
			}

			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			SetTextureParameters();

		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;

		}

		stbi_image_free(data);
	}

	void Texture2D::Use(int activeTexture)
	{
		if (ID)
		{
			glActiveTexture(GL_TEXTURE0 + activeTexture);
			glBindTexture(GL_TEXTURE_2D, ID);
		}
	}

	void Texture2D::SetTextureParameters()
	{
		GLint wrapping;
		GLint filter;
		GLint mipMap;

		switch (Wrapping)
		{
		case EWrapping::REPEAT:
			wrapping = GL_REPEAT;
			break;
		case EWrapping::MIRROREDREPEAT:
			wrapping = GL_MIRRORED_REPEAT;
			break;
		case EWrapping::CLAMP:
			wrapping = GL_CLAMP_TO_EDGE;
			break;
		case EWrapping::CLAMPBORDER:
			wrapping = GL_CLAMP_TO_BORDER;
			break;
		default:
			break;
		}

		switch (Filter)
		{

		case EFilter::LINEAR:
			filter = GL_LINEAR;
			break;
		case EFilter::NEAREST:
			filter = GL_NEAREST;
			break;
		}

		switch (MipMap)
		{
		case EMipMap::LINEAR:
			mipMap = GL_LINEAR;
			break;
		case EMipMap::NEAREST:
			mipMap = GL_NEAREST;
			break;
		case EMipMap::NEAREST_NEAREST:
			mipMap = GL_NEAREST_MIPMAP_NEAREST;
			break;
		case EMipMap::LINEAR_NEAREST:
			mipMap = GL_LINEAR_MIPMAP_NEAREST;
			break;
		case EMipMap::NEAREST_LINEAR:
			mipMap = GL_NEAREST_MIPMAP_LINEAR;
			break;
		case EMipMap::LINEAR_LINEAR:
			mipMap = GL_LINEAR_MIPMAP_LINEAR;
			break;
		default:
			break;
		}

		if (Wrapping != EWrapping::CLAMPBORDER)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
		}
		else
		{
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER, glm::value_ptr(BorderColor));
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mipMap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	}
}