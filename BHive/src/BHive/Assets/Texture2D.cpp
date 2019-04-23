#include "BHivePCH.h"
#include "Texture2D.h"
#include <stb_image.h>
#include "imgui.h"
#include "Editors/TextureEditor.h"
#include <filesystem>

namespace BHive
{
	Texture2D::Texture2D()
		:Wrapping(0), Filter(EFilter::LINEAR), MipMap(EMipMap::LINEAR), BorderColor(1.0f)
	{

	}


	Texture2D::Texture2D(const String& fileName, const String& directory, ETextureType InType, bool gamma, EWrapping wrapping, EMipMap mipmap, EFilter filter, glm::vec3 borderColor)
		:Texture2D()
	{

		Type = InType;
		Wrapping = 0;
		MipMap = mipmap;
		Filter = filter;
		BorderColor = borderColor;
	}

	Texture2D::~Texture2D()
	{
	}

	void Texture2D::Use(int activeTexture)
	{
		if (GetData())
		{
			glActiveTexture(GL_TEXTURE0 + activeTexture);
			glBindTexture(GL_TEXTURE_2D, GetData());
		}
	}

	void Texture2D::CreateEditorWindow()
	{
		new TextureEditor(*this, "Edit " + GetDisplayName());
	}

	bool Texture2D::Load(const String& name, const String& path)
	{
		BResource::Load(name, path);
		
		GLint internalFormat = GL_RGB;

		stbi_set_flip_vertically_on_load(true);
		data = stbi_load(path.c_str(), &width, &height, &numChannels, 0);

		glGenTextures(1, &m_Data);
		glBindTexture(GL_TEXTURE_2D, GetData());

		SetTextureParameters();

		if (data != nullptr)
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
		}
		else
		{
			BH_ERROR("Failed to load texture");

			return false;
		}

		
		stbi_image_free(data);

		return true;
	}

	void Texture2D::SetTextureParameters()
	{
		GLint wrapping;
		GLint filter;
		GLint mipMap;

		switch (Wrapping)
		{
		case 0:
			wrapping = GL_REPEAT;
			break;
		case 1:
			wrapping = GL_MIRRORED_REPEAT;
			break;
		case 2:
			wrapping = GL_CLAMP_TO_EDGE;
			break;
		case 3:
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

		if (Wrapping != 3)
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