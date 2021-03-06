#pragma once

#include <glm/glm.hpp>


namespace BHive
{
	template<typename T>
	struct Vector2;

	template<typename T>
	struct Vector3
	{

		Vector3() :x((T)0), y((T)0), z((T)0) {};
		Vector3(T _x) :x(_x), y(_x), z(_x) {};
		Vector3(T _x, T _y, T _z) :x(_x), y(_y), z(_z) {};
		Vector3(const Vector2<T>& _vector2, T _z) :x(_vector2.x), y(_vector2.y), z(_z) {};
		Vector3(Vector2<T>& _vector2, T _z = 0.0f) :x(_vector2.x), y(_vector2.y), z(_z) {};
		Vector3(const Vector3& other) :x(other.x), y(other.y), z(other.z) {};

		union { T x, r; };
		union { T y, g; };
		union { T z, b; };

	public:
		T GetMagnitude() const;
		T GetMagnitude2() const;
		Vector3 Normalize();
		Vector3 Cross(const Vector3& other) const ;
		T Dot(const Vector3& other) const;
		T GetDistance(const Vector3& b) const;
	public:
		static const Vector3 Zero();
		static const Vector3 One();
		static float GetAngle(const Vector3& a, const Vector3& b) ;
		static T GetDistance(const Vector3& a, const Vector3& b);
	public:
		Vector3 operator+(const Vector3& _other) const;
		Vector3 operator-(const Vector3& _other) const;
		Vector3 operator*(T _scalar) const;
		Vector3 operator/(T _scalar) const;
		Vector3 operator+=(const Vector3& _other);
		Vector3 operator-=(const Vector3& _other);
		Vector3 operator*=(T _scalar);
		Vector3 operator/=(T _scalar);
		Vector3 operator-();
		T* operator*();
		const T* operator*() const;
		float operator*(const Vector3& _other) const;
		Vector3 operator^(const Vector3& _other) const;
		operator glm::vec3() const { return {x, y, z}; }

		T& operator[](uint32 index);
		bool operator==(const Vector3& _other);

	public:
		template<typename U>
		friend std::ostream& operator<<(std::ostream& os, const Vector3<U>& _vector3);

		template<typename U>
		friend std::istream& operator>>(std::istream& is, Vector3<U>& _vector3);

	public:
		BString ToString() const { return Format("{%f, %f, %f}", x, y, z); }
	};

	template<typename T>
	T Vector3<T>::Dot(const Vector3& other) const
	{
		return (x * other.x) + (y * other.y) + (z * other.z);
	}

	template<typename T>
	Vector3<T> Vector3<T>::Cross(const Vector3& other) const
	{
		float _x = (y * other.z) - (z * other.y);
		float _y = (z * other.x) - (x * other.z);
		float _z = (x * other.y) - (y * other.x);

		return Vector3<T>(_x, _y, _z);
	}

	template<typename T>
	T Vector3<T>::GetDistance(const Vector3& a, const Vector3& b) 
	{
		return a.GetDistance(b);
	}

	template<typename T>
	T Vector3<T>::GetDistance(const Vector3& b) const
	{
		float xd = (x - b.x);
		float yd = (y - b.y);
		float zd = (z - b.z);
		return sqrt( (xd * xd) + (yd * yd) + (zd * zd));
	}

	template<typename T>
	T Vector3<T>::GetMagnitude2() const
	{
		return (x * x) + (y * y) + (z * z);
	}

	template<typename T>
	T Vector3<T>::GetMagnitude() const
	{
		float length = sqrt((x * x) + (y * y) + (z * z));

		return length;
	}

	template<typename T>
	Vector3<T> Vector3<T>::Normalize()
	{
		return *this /= GetMagnitude();
	}

	template<typename T>
	const Vector3<T> Vector3<T>::Zero()
	{
		return Vector3(0.0f, 0.0f, 0.0f);
	}

	template<typename T>
	const Vector3<T> Vector3<T>::One()
	{
		return Vector3(1.0f, 1.0f, 1.0f);
	}

	template<typename T>
	float Vector3<T>::GetAngle(const Vector3& a, const Vector3& b) 
	{
		return (a * b) * 360.0f;
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator+(const Vector3<T>& _other) const
	{
		return Vector3(x + _other.x, y + _other.y, z + _other.z);
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator-(const Vector3<T>& _other) const
	{
		return Vector3(x - _other.x, y - _other.y, z - _other.z);
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator-()
	{
		return Vector3(x * -1.0f, y * -1.0f, z * -1.0f);
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator*(T _scalar) const
	{
		return Vector3(x * _scalar, y * _scalar, z  * _scalar);
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator/(T _scalar) const
	{
		return Vector3(x / _scalar, y / _scalar, z / _scalar);
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator+=(const Vector3<T>& _other)
	{
		return *this = *this + _other;
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator-=(const Vector3<T>& _other)
	{
		return *this = *this - _other;
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator*=(T _scalar)
	{
		return *this = *this * _scalar;
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator/=(T _scalar)
	{
		return *this = *this / _scalar;
	}

	template<typename T>
	float Vector3<T>::operator*(const Vector3<T>& _other) const
	{
		return Dot(_other);
	}

	template<typename T>
	Vector3<T> Vector3<T>::operator^(const Vector3<T>& _other) const
	{
		return Cross(_other);
	}

	template<typename T>
	T& Vector3<T>::operator[](uint32 index)
	{
		if (index <= 0) return x;
		else if (index == 1) return y;
		else return z;
	}

	template<typename T>
	bool Vector3<T>::operator==(const Vector3<T>& _other)
	{
		return (x == _other.x) && (y == _other.y) && (z == _other.z);
	}

	template<typename T>
	T* Vector3<T>::operator*()
	{
		return &x;
	}

	template<typename T>
	const T* Vector3<T>::operator*() const
	{
		return &x;
	}

	template<typename T>
	inline std::ostream& operator<<(std::ostream& os, const Vector3<T>& _vector3)
	{
		return os << _vector3.ToString();
	}

	template<typename T>
	inline std::istream& operator>>(std::istream& is, Vector3<T>& _vector3)
	{
		return is >> _vector3.x >> _vector3.y >> _vector3.z;
	}

	using FVector3 = Vector3<float>;
	using UVector3 = Vector3<uint32>;
	using IVector3 = Vector3<int32>;
	using BVector3 = Vector3<bool>;
}


