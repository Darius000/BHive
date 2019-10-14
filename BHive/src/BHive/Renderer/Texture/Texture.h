#pragma once

#include "Core.h"
//#include "Bhive/Assets/BResource.h"
#include <glad/glad.h>

namespace BHive
{
	class Texture //: public BResource
	{
	public:
		Texture();

		//virtual unsigned int GetIconData() const override;

	protected:
		//virtual void OnSave(std::ofstream& resourceFile, const FString& resourceFilePath) override;
		//virtual void OnLoad(std::ifstream& resourceFile) override;
		//virtual void LoadResource() override;
		unsigned int GetTextureData() const;

	protected:
		unsigned char* m_PixelData;
		unsigned int m_TextureData;
		int m_Width, m_Height, m_NumChannels, m_Size;
	};
}
