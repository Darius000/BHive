#pragma once
#include <glad/glad.h>

namespace BHive
{
	class Texture 
	{
	public:
		virtual ~Texture() = default;

	public:
		virtual uint32 GetWidth() const = 0;
		virtual uint32 GetHeight() const = 0;
		virtual uint8 GetData() const = 0;

		virtual void SetData(void* data, uint32 size) = 0;

		virtual void Bind(uint32 slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() = default;

		static Ref<Texture2D> Create(const BString& path);
		static Ref<Texture2D> Create(uint32 width, uint32 height, GLenum internalFormat , GLenum dataFormat);
		static Ref<Texture2D> WhiteTexture();
		static Ref<Texture2D> BlackTexture();
	};
}
