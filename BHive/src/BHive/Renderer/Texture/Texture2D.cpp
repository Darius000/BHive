#include "BHivePCH.h"
#include "Texture2D.h"
#include "imgui.h"
#include "BHive/Editors/TextureEditor.h"

namespace BHive
{
	Texture2D::Texture2D()
		:Wrapping(0), Filter(EFilter::LINEAR), MipMap(EMipMap::LINEAR), 
		BorderColor(1.0f)
	{

	}


	Texture2D::Texture2D(const FString& fileName, const FString& directory, ETextureType InType, bool gamma, EWrapping wrapping, EMipMap mipmap, EFilter filter, glm::vec3 borderColor)
		:Texture2D()
	{

		Wrapping = 0;
		MipMap = mipmap;
		Filter = filter;
		BorderColor = borderColor;
	}

	void Texture2D::Use(int activeTexture)
	{
		if (m_TextureData)
		{
			glActiveTexture(GL_TEXTURE0 + activeTexture);
			glBindTexture(GL_TEXTURE_2D, m_TextureData);
		}
	}

	/*void Texture2D::CreateEditorWindow()
	{
		new TextureEditor(*this, FString() + "Edit " + GetDisplayName());
	}*/

	void Texture2D::SetWrapping(GLint wrapping)
	{

	}

	void Texture2D::SetFilter(EFilter filter)
	{

	}

	void Texture2D::SetMipMap(EMipMap mipmap)
	{

	}


	/*bool Texture2D::Load(const String& name, const String& path)
	{
		BResource::Load(name, path);
		
		String resourceName = "Data\\" + name + ".bh";
		
		bool saveExists = std::filesystem::exists(resourceName.c_str());

		if (!saveExists)
		{
			stbi_set_flip_vertically_on_load(true);
			m_PixelData = stbi_load(path.c_str(), &m_Width, &m_Height, &m_NumChannels, 0);
			m_Size = m_NumChannels * m_Width * abs(m_Height);
		}

		if (saveExists)
		{
			String line;
			//Load data
			std::ifstream file;
			file.open(resourceName, std::ifstream::in | std::ifstream::binary);

			file >> m_Size >> m_Width >> m_Height >> m_NumChannels;
			//Skip to next line in file
			getline(file, line);
			m_PixelData = new unsigned char[m_Size];
			file.read(reinterpret_cast<char*>(m_PixelData), m_Size);
			//data = reinterpret_cast<unsigned char*>(temp);
			file.close();
		}

		if (m_PixelData != nullptr && !saveExists)
		{			
			//Save data
			std::ofstream file;
			file.open(resourceName, std::ofstream::out | std::ofstream::binary);

			file << m_Size << " " << m_Width << " " << m_Height << " " << m_NumChannels << std::endl;
			file.write(reinterpret_cast<const char*>(m_PixelData), m_Size );
			file.close();
		}

		glGenTextures(1, &m_TextureData);
		glBindTexture(GL_TEXTURE_2D, m_TextureData);

		SetTextureParameters();

		GLint internalFormat = GL_RGB;

		if (m_PixelData != nullptr)
		{
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
		}
		else
		{
			BH_ERROR("Failed to load texture");

			return false;
		}

		stbi_image_free(m_PixelData);

		return true;
	}*/

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