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

	float Color::GetR() const
	{
		return r / (float)MAX_COLOR;
	}

	float Color::GetG() const
	{
		return g / (float)MAX_COLOR;
	}

	float Color::GetB() const
	{
		return b / (float)MAX_COLOR;
	}

	float Color::GetA() const
	{
		return a / (float)MAX_COLOR;
	}

	FString Color::ToString() const
	{
		return FString() + "{" + r + "," + g + "," + b + "," + a + "}";
	}

	uint8* const Color::operator*()
	{
		return &r;
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

	LinearColor::LinearColor()
		:LinearColor(1.0f, 1.0f)
	{

	}

	LinearColor::LinearColor(float color, float A )
		:LinearColor(color, color, color, A)
	{

	}

	LinearColor::LinearColor(float R, float G, float B, float A )
		:r(R), g(G), b(B), a(A)
	{

	}

	FString LinearColor::ToString() const
	{
		return FString() + "{" + r + "," + g + "," + b + "," + a + "}";
	}

	float* const LinearColor::operator*()
	{
		return &r;
	}

	void LinearColor::operator+=(const LinearColor& col)
	{
		r += col.r;
		g += col.g;
		b += col.b;
		a += col.a;
	}

	bool LinearColor::operator==(const LinearColor& col)
	{
		return r == col.r && g == col.g && b == col.b && a == col.a;
	}
}