#include "BHivePCH.h"
#include "Vector2.h"
#include "Vector3.h"

namespace BHive
{
	Vector2::Vector2()
		:x(0.0f), y(0.0f)
	{

	}

	Vector2::Vector2(float _x, float _y)
		:x(_x), y(_y)
	{

	}

	Vector2::Vector2(const Vector3& _vector3)
		:x(_vector3.x), y(_vector3.y)
	{

	}

	Vector2::Vector2(Vector3& _vector3)
		:x(_vector3.x), y(_vector3.y)
	{

	}

	float Vector2::GetMagnitude() const
	{
		return sqrt((x * x) + (y * y));
	}

	Vector2 Vector2::Normalize()
	{
		return *this /= GetMagnitude();
	}

	const Vector2 Vector2::Zero()
	{
		return Vector2();
	}

	const Vector2 Vector2::One()
	{
		return Vector2(1.0f, 1.0f);
	}

	Vector2 Vector2::Add(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}

	Vector2 Vector2::Subtract(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}

	Vector2 Vector2::Multiply(const Vector2& v, float s)
	{
		return Vector2(v.x * s, v.y * s);
	}

	Vector2 Vector2::Divide(const Vector2& v, float s)
	{
		return Vector2(v.x / s, v.y / s);
	}

	Vector2 Vector2::Negate(Vector2& v)
	{
		return Vector2(v.x * -1.0f, v.y * -1.0f);
	}

	float Vector2::DotProduct(const Vector2& a, const Vector2& b)
	{
		return (a.x * b.x) + (a.y * b.y);
	}

	float Vector2::GetAngle(const Vector2& a, const Vector2& b)
	{
		return DotProduct(a, b) * 360.0f;
	}

	Vector2 Vector2::operator+(const Vector2& _other)
	{
		return Add(*this, _other);
	}

	Vector2 Vector2::operator*=(float _scalar)
	{
		return *this = *this * _scalar;
	}

	float Vector2::operator*(const Vector2& _other)
	{
		return DotProduct(*this, _other);
	}

	float* const Vector2::ptr() 
	{
		return &x;
	}

	float Vector2::operator[](unsigned int index)
	{
		if (index <= 0) return x;
		else return y;
	}

	bool Vector2::operator==(const Vector2& _other)
	{
		return (x == _other.x) && (y == _other.y);
	}

	Vector2 Vector2::operator/=(float _scalar)
	{
		return *this = *this / _scalar;
	}

	Vector2 Vector2::operator-(const Vector2& _other)
	{
		return Subtract(*this, _other);
	}

	Vector2 Vector2::operator-()
	{
		*this = Negate(*this);
		return *this;
	}

	Vector2 Vector2::operator*(float _scalar)
	{
		return Multiply(*this, _scalar);
	}

	Vector2 Vector2::operator/(float _scalar)
	{
		return Divide(*this, _scalar);
	}

	Vector2 Vector2::operator-=(const Vector2& _other)
	{
		return *this = *this - _other;
	}

	Vector2 Vector2::operator+=(const Vector2& _other)
	{
		return *this = *this + _other;
	}

	bool Vector2::operator!=(const Vector2& _other)
	{
		return (x != _other.x) || (y != _other.y);
	}


	FString Vector2::ToString() const
	{
		return FString() + "{" + x + "," + y + "}";
	}
}