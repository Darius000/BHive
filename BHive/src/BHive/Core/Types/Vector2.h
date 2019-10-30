#pragma once

namespace BHive
{
	template<typename T>
	struct Vector2
	{
		struct Vector3;

		Vector2(){};
		Vector2(T _x, T _y = 0.0f) :x(_x), y(_y) {};
		Vector2(const Vector3& _vector3) :x(_vector3.x), y(_vector3.y) {};
		Vector2(Vector3& _vector3) :x(_vector3.x), y(_vector3.y) {};

		union { float x, r; }; 
		union { float y, g; };

		float GetMagnitude() const; 
		Vector2 Normalize(); 

		static const Vector2 Zero(); 
		static const Vector2 One(); 
		static float GetAngle(const Vector2& a, const Vector2& b);

		Vector2 operator+(const Vector2& _other);
		Vector2 operator-(const Vector2& _other);
		Vector2 operator*(T _scalar);
		Vector2 operator/(T _scalar);
		Vector2 operator+=(const Vector2& _other);
		Vector2 operator-=(const Vector2& _other);
		Vector2 operator*=(T _scalar);
		Vector2 operator/=(T _scalar);
		Vector2 operator-(); 
		float operator*(const Vector2& _other);
		T operator[](uint32 index);
		bool operator==(const Vector2& _other);
		bool operator!=(const Vector2& _other);
		T* const operator*();

		const BString& ToString() const { return Format("{ %f, %f}"); }
	};

	template<typename T>
	inline std::ostream& operator<<(std::ostream& os, const Vector2<T>& _vector2)
	{
		return os << _vector2.ToString();
	}

	template<typename T>
	float Vector2<T>::GetMagnitude() const
	{
		return sqrt((x * x) + (y * y));
	}

	template<typename T>
	Vector2<T> Vector2<T>::Normalize()
	{
		return *this /= GetMagnitude();
	}

	template<typename T>
	const Vector2<T> Vector2<T>::Zero()
	{
		return Vector2();
	}

	template<typename T>
	const Vector2<T> Vector2<T>::One()
	{
		return Vector2(1.0f, 1.0f);
	}

	template<typename T>
	float Vector2<T>::GetAngle(const Vector2& a, const Vector2& b)
	{
		return (a * b) * 360.0f;
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator+(const Vector2& _other)
	{
		return Vector2(x + _other.x, y + _other.y);
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator*=(T _scalar)
	{
		return *this = *this * _scalar;
	}

	template<typename T>
	float Vector2<T>::operator*(const Vector2& _other)
	{
		return (x * _other.x) + (y * _other.y);
	}

	template<typename T>
	T* const Vector2<T>::operator*()
	{
		return &x;
	}

	template<typename T>
	T Vector2<T>::operator[](uint32 index)
	{
		if (index <= 0) return x;
		else return y;
	}

	template<typename T>
	bool Vector2<T>::operator==(const Vector2& _other)
	{
		return (x == _other.x) && (y == _other.y);
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator/=(T _scalar)
	{
		return *this = *this / _scalar;
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator-(const Vector2& _other)
	{
		return Vector2(x - _other.x, y - _other.y);
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator-()
	{
		return Vector2(x * -1.0f, y * -1.0f);;
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator*(T _scalar)
	{
		return Vector2(x * _scalar, y * _scalar);
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator/(T _scalar)
	{
		return Vector2(x / _scalar, y / _scalar);
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator-=(const Vector2& _other)
	{
		return *this = *this - _other;
	}

	template<typename T>
	Vector2<T> Vector2<T>::operator+=(const Vector2& _other)
	{
		return *this = *this + _other;
	}

	template<typename T>
	bool Vector2<T>::operator!=(const Vector2& _other)
	{
		return (x != _other.x) || (y != _other.y);
	}

	typedef Vector2<float>	FVector2;
	typedef Vector2<uint32> UVector2;
	typedef Vector2<int32>	IVector2;
	typedef Vector2<bool>	BVector2;
}