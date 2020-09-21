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

	const uint8* Color::operator*() const
	{
		return &r;
	}

	uint8* Color::operator*()
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

	LinearColor3::LinearColor3()
		:LinearColor3(1.0f)
	{

	}

	LinearColor3::LinearColor3(float color)
		: LinearColor3(color, color, color)
	{

	}

	LinearColor3::LinearColor3(float R, float G, float B)
		: r(R), g(G), b(B)
	{
		Clamp();
	}

	void LinearColor3::Clamp()
	{
		r = MathLibrary::Clamp(r, 0.0f, 1.0f);
		g = MathLibrary::Clamp(g, 0.0f, 1.0f);
		b = MathLibrary::Clamp(b, 0.0f, 1.0f);
	}

	BString LinearColor3::ToString() const
	{
		return Format("{ %f, %f, %f }", r, g, b);
	}


	LinearColor3 LinearColor3::operator=(const LinearColor3& other)
	{
		r = other.r;
		g = other.g;
		b = other.b;
		return *this;
	}

	const float* LinearColor3::operator*() const
	{
		return &r;
	}

	float* LinearColor3::operator*()
	{
		return &r;
	}

	LinearColor3::operator FVector3() const
	{
		return FVector3(r, g, b);
	}

	void LinearColor3::operator+=(const LinearColor3& col)
	{
		r += col.r;
		g += col.g;
		b += col.b;

		Clamp();
	}

	bool LinearColor3::operator==(const LinearColor3& col)
	{
		return r == col.r && g == col.g && b == col.b;
	}

	LinearColor4::LinearColor4()
		:LinearColor4(1.0f, 1.0f)
	{

	}

	LinearColor4::LinearColor4(float color, float A )
		:LinearColor4(color, color, color, A)
	{

	}

	LinearColor4::LinearColor4(float R, float G, float B, float A )
		:r(R), g(G), b(B), a(A)
	{
		Clamp();
	}

	void LinearColor4::Clamp()
	{
		r = MathLibrary::Clamp(r, 0.0f, 1.0f);
		g = MathLibrary::Clamp(g, 0.0f, 1.0f);
		b = MathLibrary::Clamp(b, 0.0f, 1.0f);
		a = MathLibrary::Clamp(a, 0.0f, 1.0f);
	}

	BString LinearColor4::ToString() const
	{
		return Format("{ %f, %f, %f }", r, g, b);
	}


	LinearColor4 LinearColor4::operator=(const LinearColor4& other)
	{
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;
		return *this;
	}

	const float* LinearColor4::operator*() const
	{
		return &r;
	}

	float* LinearColor4::operator*()
	{
		return &r;
	}

	LinearColor4::operator FVector4() const
	{
		return FVector4(r, g, b, a);
	}

	void LinearColor4::operator+=(const LinearColor4& col)
	{
		r += col.r;
		g += col.g;
		b += col.b;
		a += col.a;

		Clamp();
	}

	bool LinearColor4::operator==(const LinearColor4& col)
	{
		return r == col.r && g == col.g && b == col.b && a == col.a;
	}

	
}