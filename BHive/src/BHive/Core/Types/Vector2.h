#pragma once



namespace BHive
{
	template<typename T>
	struct Vector2
	{
		struct Vector3;

		Vector2():x((T)0), y((T)0){};
		Vector2(T _x, T _y) :x(_x), y(_y) {};
		Vector2(const Vector3& _vector3) :x(_vector3.x), y(_vector3.y) {};
		Vector2(Vector3& _vector3) :x(_vector3.x), y(_vector3.y) {};
		Vector2(const Vector2& other):x(other.x), y(other.y){};

		union { T x, r; }; 
		union { T y, g; };

		float GetMagnitude() const; 
		Vector2 Normalize(); 

		static const Vector2 Zero(); 
		static const Vector2 One(); 
		static float GetAngle(const Vector2& a, const Vector2& b);
		static Vector2 Normalize(Vector2& v);

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
		const T* operator*() const;
		T* operator*();

		friend std::ostream& operator<<(std::ostream& os, const Vector2& _vector2);
		BString ToString() const { return Format("{ %f, %f}", x, y); }
	};

	template<typename T>
	Vector2<T> Vector2<T>::Normalize(Vector2<T>& v)
	{
		float mag = v.GetMagnitude();
		return v / mag;
	}

	template<typename T>
	inline std::ostream& operator<<(std::ostream& os, const Vector2<T>& _vector2)
	{
		return os << "{" << _vector2.x << "," << _vector2.y << "}";
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
	T* Vector2<T>::operator*()
	{
		return &x;
	}

	template<typename T>
	const T* Vector2<T>::operator*() const
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
		return Vector2(x * -1.0f, y * -1.0f);
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

	using FVector2 = Vector2<float>;
	using UVector2 = Vector2<uint32>;
	using IVector2 = Vector2<int32>;
	using BVector2 = Vector2<bool>;
}