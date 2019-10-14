#include "BHivePCH.h"
#include "Color.h"

namespace BHive
{
	Color::Color()
		: Color(0, 255)
	{

	}

	Color::Color(uint8 InColor, uint8 InA)
		:r(InColor), b(InColor), g(InColor), a(InA)
	{
		
	}

	
	Color::Color(uint8 InR, uint8 InG, uint8 InB, uint8 InA /*= 1*/)
		: r(InR), b(InG), g(InB), a(InA)
	{

	}

	float Color::GetR()
	{
		return r / (float)MAX_COLOR;
	}

	float Color::GetG()
	{
		return g / (float)MAX_COLOR;
	}

	float Color::GetB()
	{
		return b / (float)MAX_COLOR;
	}

	float Color::GetA()
	{
		return a / (float)MAX_COLOR;
	}

	FString Color::ToString() const
	{
		return FString() + "{" + r + "," + g + "," + b + "," + a + "}";
	}

	void Color::operator+=(const Color& col)
	{
		r += col.r;
		g += col.g;
		b += col.b;
		a += col.a;
	}

	bool Color::operator==(const Color& col)
	{
		return r == col.r && g == col.g && b == col.b && a == col.a;
	}

	bool Color::operator!=(const Color& col)
	{
		return r != col.r && g != col.g && b != col.b && a != col.a;
	}

}