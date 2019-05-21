#include "BHivePCH.h"
#include "Vector3.h"
#include "Vector2.h"

namespace BHive
{
	Vector3::Vector3()
	{
	}


	Vector3::Vector3(float _x, float _y, float _z)
		:x(_x), y(_y), z(_z)
	{
		
	}

	Vector3::Vector3(const Vector2& _vector2, float _z)
		:x(_vector2.x), y(_vector2.y), z(_z)
	{

	}

	Vector3::Vector3(Vector2& _vector2, float _z)
		:x( _vector2.x), y(_vector2.y), z(_z)

	{
		
	}

	Vector3::~Vector3()
	{
	}

	float Vector3::GetMagnitude() const
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}

	Vector3 Vector3::Normalize()
	{
		return *this /= GetMagnitude();
	}

	const Vector3 Vector3::Zero()
	{
		Vector3 v = Vector3();
		return v;
	}

	const Vector3 Vector3::One()
	{
		Vector3 v = Vector3(1.0f, 1.0f, 1.0f);
		return v;
	}

	Vector3 Vector3::Add(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	Vector3 Vector3::Subtract(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	Vector3 Vector3::Multiply(const Vector3& v, float s)
	{
		return Vector3(v.x * s, v.y * s, v.z  * s);
	}

	Vector3 Vector3::Divide(const Vector3& v, float s)
	{
		return Vector3(v.x / s, v.y / s, v.z  / s);
	}

	Vector3 Vector3::Negate(Vector3& v)
	{
		return Vector3(v.x * -1.0f, v.y * -1.0f, v.z * -1.0f);
	}

	float Vector3::DotProduct(const Vector3& a, const Vector3& b)
	{
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}

	float Vector3::GetAngle(const Vector3& a, const Vector3& b)
	{
		return DotProduct(a, b) * 360.0f;
	}

	Vector3 Vector3::CrossProduct(const Vector3& a, const Vector3& b)
	{
		float _x = (a.y * b.z) - (a.z * b.y);
		float _y = (a.z * b.x) - (a.x * b.z);
		float _z = (a.x * b.y) - (a.y * b.x);

		return Vector3(_x, _y, _z);
	}

	Vector3 Vector3::operator+(const Vector3& _other)
	{
		return Add(*this, _other);
	}

	Vector3 Vector3::operator-(const Vector3& _other)
	{
		return Subtract(*this, _other);
	}

	Vector3 Vector3::operator-()
	{
		*this = Negate(*this);
		return *this;
	}

	Vector3 Vector3::operator*(float _scalar)
	{
		return Multiply(*this, _scalar);
	}

	Vector3 Vector3::operator/(float _scalar)
	{
		return Divide(*this, _scalar);
	}

	Vector3 Vector3::operator+=(const Vector3& _other)
	{
		return *this = *this + _other;
	}

	Vector3 Vector3::operator-=(const Vector3& _other)
	{
		return *this = *this - _other;
	}

	Vector3 Vector3::operator*=(float _scalar)
	{
		return *this = *this * _scalar;
	}

	Vector3 Vector3::operator/=(float _scalar)
	{
		return *this = *this / _scalar;
	}

	float Vector3::operator*(const Vector3& _other)
	{
		return DotProduct(*this, _other);
	}

	Vector3 Vector3::operator^(const Vector3& _other)
	{
		return CrossProduct(*this, _other);
	}

	float Vector3::operator[](unsigned int index)
	{
		if(index <= 0) return x;
		else if (index == 1) return y;
		else return z;
	}

	bool Vector3::operator==(const Vector3& _other)
	{
		return (x == _other.x) && (y == _other.y) && (z == _other.z);
	}

	bool Vector3::operator!=(const Vector3& _other)
	{
		return (x != _other.x) || (y != _other.y) || (z != _other.z);
	}

	std::string Vector3::ToString() const
	{
		return "{" + NumToString(x) + "," + NumToString(y) + "," + NumToString(z) + "}";
	}
}

