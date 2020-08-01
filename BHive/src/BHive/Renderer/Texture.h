#pragma once
#include <glad/glad.h>


namespace BHive
{
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

	protected:
		virtual void SetupTextureParameters() = 0;

		BName m_Name;

		WinPath m_Path;

		uint32 m_Width;

		uint32 m_Height;

		uint32 m_RendererID;

		FPixelData PixelData;
	};

	class Texture2D : public Texture
	{
	public:
		Texture2D(BName Name): Texture(Name){}

		virtual ~Texture2D() = default;

		static Ref<Texture2D> Create(BName TextureName, const WinPath& path);

		static Ref<Texture2D> Create(BName TextureName, uint32 width, uint32 height, GLenum internalFormat , GLenum dataFormat, void* data);
	};
}
