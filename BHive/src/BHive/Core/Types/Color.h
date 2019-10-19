#pragma once

namespace BHive
{
	
	class Color
	{
		#define MAX_COLOR 255

	public:
		Color();
		Color(uint8 InColor, uint8 InA = MAX_COLOR);
		Color(uint8 InR, uint8 InG, uint8 InB, uint8 InA = MAX_COLOR);
		float GetR() const;
		float GetG() const;
		float GetB() const;
		float GetA() const;
		FString ToString() const;

	public:
		bool operator==(const Color& col);
		void operator+=(const Color& col);
		uint8* const operator*();

	public:
		uint8 r;
		uint8 g;
		uint8 b;
		uint8 a;
	};

	inline std::ostream& operator<<(std::ostream& os, const Color& color)
	{
		return os << color.ToString();
	}


	class LinearColor
	{
		#define MAX_LINEARCOLOR 1.0f

	public:
		LinearColor();
		LinearColor(float color, float A = MAX_COLOR);
		LinearColor(float R, float G, float B, float A = MAX_COLOR);

		FString ToString() const;

	public:
		bool operator==(const LinearColor& col);
		void operator+=(const LinearColor& col);
		float* const operator*();

	public:
		float r;	
		float g;
		float b;
		float a;
	};

	inline std::ostream& operator<<(std::ostream& os, const LinearColor& color)
	{
		return os << color.ToString();
	}
}
