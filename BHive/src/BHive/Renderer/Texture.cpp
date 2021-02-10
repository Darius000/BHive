#include "BHivePCH.h"
#include "Texture.h"
#include "BHive/Renderer/Renderer.h"
#include "BHive/Platforms/Opengl/OpenGLTexture.h"
#include "BHive/Platforms/Opengl/OpenglCubeTexture.h"
#include "BHive/Managers/AssetManagers.h"
#include "Core/Viewport/Viewport.h"

namespace BHive
{
	FPixelData::FPixelData()
		: m_Data(nullptr), m_InternalFormat(GL_RGBA8), m_DataFormat(GL_RGBA)
	{
	
	}


	Texture::Texture()
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

	std::vector<std::string> Texture::extensions = { "jpg", "jpeg", "png", "tga" };


	Texture2D::Texture2D()
	: m_Width(0), m_Height(0)
	{

	}

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


	CubeTexture::CubeTexture()
		:m_RendererID(0)
	{

	}

	Ref<CubeTexture> CubeTexture::Create(const std::string& name, const std::array<WinPath, 6>& facePaths)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: BH_CORE_ASSERT(false, "RendererAPI::None currently not supported");
		case RendererAPI::API::OpenGL: {
			Ref<CubeTexture> tex(Make_Ref<OpenglCubeTexture>(name, facePaths));
			return tex;
		}
		case RendererAPI::API::DirectX: break;
		}

		BH_CORE_ASSERT(false, "Unknown API");
		return nullptr;
	}

	uintPtr CubeTexture::GetRendererID() const
	{
		return m_RendererID;
	}


	void CubeTexture::Bind(uint32 slot) const
	{
		
	}


	void CubeTexture::UnBind(uint32 slot) const
	{
		
	}


	void CubeTexture::InValidate()
	{
		
	}

}
