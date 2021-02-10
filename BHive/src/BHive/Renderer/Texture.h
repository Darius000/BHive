#pragma once

#include <glad/glad.h>
#include "Assets/Asset.h"
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

	static const char* s_Min_ColorMethods[] = {"Nearest","Linear","NearestMipMapNearest","LinearMipMapNearest","NearestMipMapLinear","LinearMipMapLinear"};
	static const char* s_Mag_ColorMethods[] = {"Nearest", "Linear"};

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
			case MinColorMethod::Nearest:				return GL_NEAREST;
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
		case MagColorMethod::Nearest:				return GL_NEAREST;
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

	class Texture : public IAssetType
	{

		DEFINE_ASSET_BODY(Texture, m_Name)

	public:
		Texture();
		virtual ~Texture() = default;

	public:
		
		virtual uintPtr GetRendererID() const = 0;

		virtual void Bind(uint32 slot = 0) const = 0;

		virtual void UnBind(uint32 slot = 0) const = 0;

		virtual void InValidate() = 0;

		operator uintPtr() const {return GetRendererID(); }

		operator void*() const { return (void*)GetRendererID(); }

		static bool IsExtensionSupported(const std::string& ext);

		void SetParameters(TilingMethod tiling, MinColorMethod minFilter, MagColorMethod magfilter, LinearColor4 borderColor = LinearColor4(0.0f));

	protected:
		
		TilingMethod m_TilingMethod = TilingMethod::Repeat;

		MinColorMethod m_MinFilterColorMethod = MinColorMethod::Linear;

		MagColorMethod m_MagFilterColorMethod = MagColorMethod::Nearest;

		LinearColor4 m_BorderColor = LinearColor4(0.0f); //used if Tiling method is set to clamp to edge

		static std::vector<std::string> extensions; 

		friend class TextureEditorCustomizationDetails;
	};

	class Texture2D : public Texture
	{
		DEFINE_ASSET_BODY(Texture2D, m_Name)

	public:
		Texture2D();

		virtual ~Texture2D() = default;

		uintPtr GetRendererID() const override { return m_RendererID; }

		uint32 GetNumChannels() const { return m_Channels;}

		bool HasAlphaChannel() const { return b_HasAlphaChannel; }

		uint32 GetWidth() const { return m_Width; }

		uint32 GetHeight() const { return m_Height; }

		FPixelData& GetData() { return PixelData; };

	protected:

		WinPath m_Path;

		uint32 m_Width;

		uint32 m_Height;

		uint32 m_Channels = 0;

		FPixelData PixelData;

		uint32 m_RendererID;

		bool b_HasAlphaChannel;

	public:
		static Ref<Texture2D> Create(const WinPath& path);

		static Ref<Texture2D> Create(uint32 width, uint32 height, GLenum internalFormat , GLenum dataFormat, void* data);

	};

	struct CubeTexFaceData
	{
		IVector2 m_Size;
		uint32 m_Channels;
		WinPath m_Path;
		FPixelData m_PixelData;
	};

	class CubeTexture : public Texture
	{
	public:

		DEFINE_ASSET_BODY(CubeTexture, m_Name)

		CubeTexture();

		virtual ~CubeTexture() = default;

		static Ref<CubeTexture> Create(const std::string& name, const std::array<WinPath, 6>& facePaths);

		uintPtr GetRendererID() const override;

		void Bind(uint32 slot = 0) const override;

		void UnBind(uint32 slot = 0) const override;

		void InValidate() override;

	protected:
		uint32 m_RendererID;

		std::vector<CubeTexFaceData> m_FaceData;

	};
}
