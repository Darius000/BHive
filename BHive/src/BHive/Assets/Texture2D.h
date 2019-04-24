#pragma once

#include "Core.h"
#include "BResource.h"
#include <glad/glad.h>



namespace BHive
{
	enum class EWrapping : int
	{
		REPEAT = 0,
		MIRROREDREPEAT = 1,
		CLAMP = 2,
		CLAMPBORDER = 3
	};

	enum class EFilter
	{
		LINEAR,
		NEAREST,
	};

	enum class EMipMap
	{
		LINEAR,
		NEAREST,
		NEAREST_NEAREST,
		LINEAR_NEAREST,
		NEAREST_LINEAR,
		LINEAR_LINEAR
	};

	enum class ETextureType
	{
		DIFFUSE,
		SPECULAR,
		EMISSION
	};

	class BHive_API Texture2D : public BResource
	{
	public:
		Texture2D();
		Texture2D(const String& fileName, const String& directory, ETextureType InType, bool gamma = false, EWrapping wrapping = EWrapping::REPEAT, EMipMap mipmap = EMipMap::LINEAR, EFilter filter = EFilter::LINEAR, glm::vec3 borderColor = glm::vec3(1.0f));
		virtual ~Texture2D();

		bool Load(const String& name, const String& path) override;
		void Use(int activeTexture = 0);
		virtual void CreateEditorWindow() override;

		int Wrapping;
		//EWrapping Wrapping;
		EFilter Filter;
		EMipMap MipMap;
		ETextureType Type;

		glm::vec3 BorderColor;

		void SetTextureParameters();

	private:
		unsigned char* data;

		int width, height, numChannels, size;

		friend class MeshComponent;
	};
}
