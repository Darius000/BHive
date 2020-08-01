#pragma once

namespace BHive
{
	template<typename T>
	struct Vector4
	{
		struct Vector2;
		struct Vector3;

		Vector4() :x((T)0), y((T)0), z((T)0), w((T)1) {};
		Vector4(T _x) :x(_x), y(_x), z(_x), w((T)1.0f) {};
		Vector4(T _x, T _y, T _z, T _w) :x(_x), y(_y), z(_z), w(_w) {};
		Vector4(const Vector2& _vectorA, const Vector2& _vectorB) :x(_vectorA.x), y(_vectorA.y), z(_vectorB._z), w(_vectorB.w) {};
		Vector4(const Vector3& _vector, T _w = 1.0f) :x(_vector.x), y(_vector.y), z(_vector.z), w(_w) {};
		Vector4(const Vector4& other) :x(other.x), y(other.y), z(other.z), w(other.w) {};

		union { T x, r; };
		union { T y, g; };
		union { T z, b; };
		union { T w, a; };

	public:
		T GetMagnitude() const;
		Vector4 Normalize();

	public:
		static const Vector4 Zero();
		static const Vector4 One();
		static float GetAngle(const Vector4& a, const Vector4& b);

	public:
		Vector4 operator+(const Vector4& _other);
		Vector4 operator-(const Vector4& _other);
		Vector4 operator*(T _scalar);
		Vector4 operator/(T _scalar);
		Vector4 operator+=(const Vector4& _other);
		Vector4 operator-=(const Vector4& _other);
		Vector4 operator*=(T _scalar);
		Vector4 operator/=(T _scalar);
		Vector4 operator-();
		T* operator*();
		const T* operator*() const;
		float operator*(const Vector4& _other);

		T operator[](uint32 index);
		bool operator==(const Vector4& _other);

	public:
		BString ToString() const { return Format("{%f, %f, %f, %f}", x, y, z, w); }
	};

	template<typename T>
	inline std::ostream& operator<<(std::ostream& os, const Vector4<T>& _vector)
	{
		return os << _vector.ToString();
	}

	template<typename T>
	T Vector4<T>::GetMagnitude() const
	{
		return sqrt((x * x) + (y * y) + (z * z) + (w * w));
	}

	template<typename T>
	Vector4<T> Vector4<T>::Normalize()
	{
		return *this /= GetMagnitude();
	}

	template<typename T>
	const Vector4<T> Vector4<T>::Zero()
	{
		return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	template<typename T>
	const Vector4<T> Vector4<T>::One()
	{
		return Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	template<typename T>
	float Vector4<T>::GetAngle(const Vector4& a, const Vector4& b)
	{
		return (a * b) * 360.0f;
	}

	template<typename T>
	Vector4<T> Vector4<T>::operator+(const Vector4<T>& _other)
	{
		return Vector4(x + _other.x, y + _other.y, z + _other.z, w + _other.w);
	}

	template<typename T>
	Vector4<T> Vector4<T>::operator-(const Vector4<T>& _other)
	{
		return Vector4(x - _other.x, y - _other.y, z - _other.z, w - _other.w);
	}

	template<typename T>
	Vector4<T> Vector4<T>::operator-()
	{
		return Vector4(x * -1.0f, y * -1.0f, z * -1.0f, w * -1.0f);
	}

	template<typename T>
	Vector4<T> Vector4<T>::operator*(T _scalar)
	{
		return Vector4(x * _scalar, y * _scalar, z * _scalar, w * _scalar);
	}

	template<typename T>
	Vector4<T> Vector4<T>::operator/(T _scalar)
	{
		return Vector4(x / _scalar, y / _scalar, z / _scalar, w / _scalar);
	}

	template<typename T>
	Vector4<T> Vector4<T>::operator+=(const Vector4<T>& _other)
	{
		return *this = *this + _other;
	}

	template<typename T>
	Vector4<T> Vector4<T>::operator-=(const Vector4<T>& _other)
	{
		return *this = *this - _other;
	}

	template<typename T>
	Vector4<T> Vector4<T>::operator*=(T _scalar)
	{
		return *this = *this * _scalar;
	}

	template<typename T>
	Vector4<T> Vector4<T>::operator/=(T _scalar)
	{
		return *this = *this / _scalar;
	}

	template<typename T>
	float Vector4<T>::operator*(const Vector4<T>& _other)
	{
		return (x * _other.x) + (y * _other.y) + (z * _other.z) + (w * _other.w);
	}


	template<typename T>
	T Vector4<T>::operator[](uint32 index)
	{
		if (index <= 0) return x;
		else if (index == 1) return y;
		else if (index == 2) return z;
		else return w;
	}

	template<typename T>
	bool Vector4<T>::operator==(const Vector4<T>& _other)
	{
		return (x == _other.x) && (y == _other.y) && (z == _other.z) && (w == _other.w);
	}

	template<typename T>
	T* Vector4<T>::operator*()
	{
		return &x;
	}

	template<typename T>
	const T* Vector4<T>::operator*() const
	{
		return &x;
	}

	using FVector4 = Vector4<float>;
	using UVector4 = Vector4<uint32>;
	using IVector4 = Vector4<int32>;
	using BVector4 = Vector4<bool>;
}



