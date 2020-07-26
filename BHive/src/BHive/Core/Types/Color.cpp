#include "BHivePCH.h"
#include "Color.h"

namespace BHive
{
	Color::Color()
		: Color(128, 255)
	{

	}

	Color::Color(uint8 color, uint8 A)
		: Color(color, color, color, A)
	{
		
	}

	
	Color::Color(uint8 R, uint8 G, uint8 B, uint8 A )
		: r(R), b(G), g(B), a(A)
	{
		Clamp();
	}

	void Color::Clamp()
	{
		r = MathLibrary::Clamp(r, (uint8)0, (uint8)255);
		g = MathLibrary::Clamp(g, (uint8)0, (uint8)255);
		b = MathLibrary::Clamp(b, (uint8)0, (uint8)255);
		a = MathLibrary::Clamp(a, (uint8)0, (uint8)255);
	}

	BString Color::ToString() const
	{
		return Format("{ %i, %i, %i , %i }", r, g, b, a);
	}


	Color Color::operator=(const Color& other) const
	{
		return Color(other.r, other.g, other.b, other.a);
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
		Clamp();
	}

	void LinearColor::Clamp()
	{
		r = MathLibrary::Clamp(r, 0.0f, 1.0f);
		g = MathLibrary::Clamp(g, 0.0f, 1.0f);
		b = MathLibrary::Clamp(b, 0.0f, 1.0f);
		a = MathLibrary::Clamp(a, 0.0f, 1.0f);
	}

	BString LinearColor::ToString() const
	{
		return Format("{ %f, %f, %f }", r, g, b);
	}


	LinearColor LinearColor::operator=(const LinearColor& other)
	{
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;
		return *this;
	}

	float* const LinearColor::operator*()
	{
		return &r;
	}

	LinearColor::operator FVector4() const
	{
		return FVector4(r, g, b, a);
	}

	void LinearColor::operator+=(const LinearColor& col)
	{
		r += col.r;
		g += col.g;
		b += col.b;
		a += col.a;

		Clamp();
	}

	bool LinearColor::operator==(const LinearColor& col)
	{
		return r == col.r && g == col.g && b == col.b && a == col.a;
	}
}