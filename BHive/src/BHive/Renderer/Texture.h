#pragma once
#include <glad/glad.h>
#include "BHive/Managers/AssetManagers.h"

namespace BHive
{	
	class Viewport;

	enum class TilingMethod : uint8
	{
		ClampToEdge, ClampToBorder, MirroredRepeat, Repeat, MirroredClampToEdge
	};

	static const char* s_TilingMethods[] = {"ClampToEdge", "ClampToBorder", "MirroredRepeat", "Repeat", "MirroredClampToEdge"} ;

	enum class MagColorMethod : uint8
	{
		Nearest, Linear
	};

	enum class MinColorMethod : uint8 
	{
		Nearest, Linear, NearestMipMapNearest, LinearMipMapNearest, NearestMipMapLinear, LinearMipMapLinear
	};

	static const char* s_Min_ColorMethods[] = {"Linear","Nearest","NearestMipMapNearest","LinearMipMapNearest","NearestMipMapLinear","LinearMipMapLinear"};
	static const char* s_Mag_ColorMethods[] = {"Linear", "Nearest"};

	static GLenum TilingMethodToGLEnum(TilingMethod method)
	{
		switch (method)
		{
		case TilingMethod::ClampToEdge: return GL_CLAMP_TO_EDGE;
		case TilingMethod::ClampToBorder:	return GL_CLAMP_TO_BORDER;
		case TilingMethod::MirroredRepeat:	return GL_MIRRORED_REPEAT;
		case TilingMethod::Repeat:	return GL_REPEAT;
		case TilingMethod::MirroredClampToEdge: return GL_MIRROR_CLAMP_TO_EDGE;
		}

		return 0;
	}

	static GLenum ColorMethodToGLEnum(MinColorMethod method)
	{
		switch (method)
		{
			case MinColorMethod::Linear:				return GL_LINEAR;
			case MinColorMethod::Nearest:				return GL_LINEAR;
			case MinColorMethod::NearestMipMapNearest: return GL_NEAREST_MIPMAP_NEAREST;
			case MinColorMethod::LinearMipMapNearest:	return GL_LINEAR_MIPMAP_NEAREST;
			case MinColorMethod::NearestMipMapLinear:	return GL_NEAREST_MIPMAP_LINEAR;
			case MinColorMethod::LinearMipMapLinear:	return GL_LINEAR_MIPMAP_LINEAR;
		}

		return 0;
	}

	static GLenum ColorMethodToGLEnum(MagColorMethod method)
	{
		switch (method)
		{
		case MagColorMethod::Linear:				return GL_LINEAR;
		case MagColorMethod::Nearest:				return GL_LINEAR;
		}

		return 0;
	}

	struct FPixelData
	{
		FPixelData();

		void* m_Data;

		GLenum m_InternalFormat;

		GLenum m_DataFormat;
	};

	class Texture : public Asset
	{
	public:
		Texture(const std::string& Name);
		virtual ~Texture() = default;

	public:
		
		std::string GetAssetType() const override { return "Texture";}

		uint32 GetWidth() const  { return m_Width; }

		uint32 GetHeight() const  {return m_Height; }

		virtual uint32 GetRendererID() const = 0;

		FPixelData GetData() const  { return PixelData; };

		WinPath GetExternalFilePath() const { return m_Path; }

		virtual void Bind(uint32 slot = 0) const = 0;

		virtual void UnBind(uint32 slot = 0) const = 0;

		virtual void InValidate() = 0;

		operator uint32() const {return GetRendererID(); }

		operator void*() const { return (void*)&m_RendererID; }

		static bool IsExtensionSupported(const std::string& ext);

	protected:
		WinPath m_Path;

		std::string m_SavedPath;

		uint32 m_Width;

		uint32 m_Height;

		uint32 m_RendererID;

		FPixelData PixelData;

		TilingMethod m_TilingMethod = TilingMethod::Repeat;

		MinColorMethod m_MinFilterColorMethod = MinColorMethod::Linear;

		MagColorMethod m_MagFilterColorMethod = MagColorMethod::Nearest;

		LinearColor4 m_BorderColor = LinearColor4(0.0f);

		uint32 m_Channels = 0;

		void Serialize(const WinPath& path);

		static std::vector<std::string> extensions; 

		friend class TextureEditorCustomizationDetails;
	};

	class Texture2D : public Texture
	{
	public:
		Texture2D(BName Name): Texture(Name){}

		virtual ~Texture2D() = default;

		std::string GetAssetType() const override { return "Texture2D"; }

		static Ref<Texture2D> Create(const WinPath& path);

		static Ref<Texture2D> Create(BName TextureName, uint32 width, uint32 height, GLenum internalFormat , GLenum dataFormat, void* data);

		const std::string GetThumbnailName() const override
		{
			return m_Name;
		}
	};
}
