#pragma once

namespace BHive
{
	#define MAX_COLOR 255

	class Color
	{
	public:
		Color();
		Color(uint8 InColor, uint8 InA = MAX_COLOR);
		Color(uint8 InR, uint8 InG, uint8 InB, uint8 InA = MAX_COLOR);
		float GetR();
		float GetG();
		float GetB();
		float GetA();
		FString ToString() const;

	public:
		bool operator!=(const Color& col);
		bool operator==(const Color& col);
		void operator+=(const Color& col);

	public:
		uint8 r;
		uint8 b;
		uint8 g;
		uint8 a;
	};

	inline std::ostream& operator<<(std::ostream& os, const Color color)
	{
		return os << color.ToString();
	}
}
