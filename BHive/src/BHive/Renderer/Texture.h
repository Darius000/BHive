#pragma once
#include <glad/glad.h>


namespace BHive
{	
	enum class TilingMethod : uint8
	{
		ClampToEdge, ClampToBorder, MirroredRepeat, Repeat, MirroredClampToEdge
	};

	static const char* s_TilingMethods = "ClampToEdge\0ClampToBorder\0MirroredRepeat\0Repeat\0MirroredClampToEdge\0" ;

	enum class MagColorMethod : uint8
	{
		Nearest, Linear
	};

	enum class MinColorMethod : uint8 
	{
		Nearest, Linear, NearestMipMapNearest, LinearMipMapNearest, NearestMipMapLinear, LinearMipMapLinear
	};

	static const char* s_Min_ColorMethods = "Linear\0Nearest\0NearestMipMapNearest\0LinearMipMapNearest\0NearestMipMapLinear\0LinearMipMapLinear\0";
	static const char* s_Mag_ColorMethods = "Linear\0Nearest\0";

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

	class Texture 
	{
	public:
		Texture(BName Name);
		virtual ~Texture() = default;

	public:
		BName GetName() const { return m_Name; };

		uint32 GetWidth() const  { return m_Width; }

		uint32 GetHeight() const  {return m_Height; }

		virtual uint32 GetRendererID() const = 0;

		FPixelData GetData() const  { return PixelData; };

		WinPath GetExternalFilePath() const { return m_Path; }

		virtual void Bind(uint32 slot = 0) const = 0;

		virtual void InValidate() = 0;

	protected:
		BName m_Name;

		WinPath m_Path;

		uint32 m_Width;

		uint32 m_Height;

		uint32 m_RendererID;

		FPixelData PixelData;

		TilingMethod m_TilingMethod = TilingMethod::Repeat;

		MinColorMethod m_MinFilterColorMethod = MinColorMethod::Linear;

		MagColorMethod m_MagFilterColorMethod = MagColorMethod::Nearest;

		LinearColor m_BorderColor = LinearColor(0.0f);

		uint32 m_Channels = 0;

		friend class TextureEditorLayer;

		static void Serialize(Ref<Texture> texture, const WinPath& path);
	};

	class Texture2D : public Texture
	{
	public:
		Texture2D(BName Name): Texture(Name){}

		virtual ~Texture2D() = default;

		static Ref<Texture2D> Create(const WinPath& path);

		static Ref<Texture2D> Create(BName TextureName, uint32 width, uint32 height, GLenum internalFormat , GLenum dataFormat, void* data);
	};
}
