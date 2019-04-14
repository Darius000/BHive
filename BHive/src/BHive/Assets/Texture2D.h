#pragma once

#include "BHive/Core.h"
#include <glad/glad.h>


namespace BHive
{
	enum class EWrapping
	{
		REPEAT,
		MIRROREDREPEAT,
		CLAMP,
		CLAMPBORDER
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

	class BHive_API Texture2D
	{
	public:
		Texture2D();
		Texture2D(const std::string fileName, const std::string &directory, ETextureType InType, bool gamma = false, EWrapping wrapping = EWrapping::REPEAT, EMipMap mipmap = EMipMap::LINEAR, EFilter filter = EFilter::LINEAR, glm::vec3 borderColor = glm::vec3(1.0f));
		virtual ~Texture2D();

		void LoadTexture(const std::string fileName, const std::string &directory, bool gamma = false);

		void Use(int activeTexture = 0);

		EWrapping Wrapping;
		EFilter Filter;
		EMipMap MipMap;
		ETextureType Type;

		glm::vec3 BorderColor;

	private:
		unsigned int ID;

		std::string Name;

		int width, height, numChannels;

		void SetTextureParameters();

		friend class MeshComponent;
	};
}
