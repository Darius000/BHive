#include "BHivePCH.h"
#include "Texture.h"
#include "BHive/Renderer/Renderer.h"
#include "BHive/Platforms/Opengl/OpenGLTexture.h"
#include "BHive/Managers/AssetManagers.h"
#include "Core/Viewport/Viewport.h"

namespace BHive
{
	FPixelData::FPixelData()
		: m_Data(nullptr), m_InternalFormat(GL_RGBA8), m_DataFormat(GL_RGBA)
	{
	
	}


	Texture::Texture()
		:m_Path(""), m_Width(0), m_Height(0), m_RendererID(0)
	{

	}

	bool Texture::IsExtensionSupported(const std::string& ext)
	{
		
		return std::find(extensions.begin(), extensions.end(), ext) != extensions.end();
	}


	void Texture::SetParameters(TilingMethod tiling, MinColorMethod minFilter, MagColorMethod magfilter, LinearColor4 borderColor)
	{
		m_TilingMethod = tiling;
		m_MinFilterColorMethod = minFilter;
		m_MagFilterColorMethod = magfilter;
		m_BorderColor = borderColor;
		InValidate();
	}

	void Texture::Serialize(const WinPath& path)
	{
		std::ofstream file;
		file.open(*(std::string(*path) + "\\" + m_Name + ".bh"), std::ios::out | std::ios::trunc);
		uint32 m_Size = m_Channels * m_Width * m_Height;
		file << m_Name << std::endl;
		file << m_Size << " " << m_Width << " " << m_Height << " " << m_Channels << std::endl;
		file << PixelData.m_DataFormat << " " << PixelData.m_InternalFormat << std::endl;
		file.write(reinterpret_cast<const char*>(PixelData.m_Data), m_Size);
		file.close();
	}


	std::vector<std::string> Texture::extensions = { "jpg", "jpeg", "png", "tga" };

	Ref<Texture2D> Texture2D::Create(const WinPath& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: BH_CORE_ASSERT(false, "RendererAPI::None currently not supported") return nullptr;
		case RendererAPI::API::OpenGL: {
			Ref<Texture2D> tex(Make_Ref<OpenGLTexture2D>(path)); 
			return tex;
		}
		case RendererAPI::API::DirectX: break;
		}

		BH_CORE_ASSERT(false, "Unknown API");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(uint32 width, uint32 height, GLenum internalFormat, GLenum dataFormat, void* data)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: BH_CORE_ASSERT(false, "RendererAPI::None currently not supported");
		case RendererAPI::API::OpenGL:{
			Ref<Texture2D> tex(Make_Ref<OpenGLTexture2D>(width, height, internalFormat, dataFormat, data)); 
			return tex;
		}
		case RendererAPI::API::DirectX: break;
		}

		BH_CORE_ASSERT(false, "Unknown API");
		return nullptr;
	}
}
