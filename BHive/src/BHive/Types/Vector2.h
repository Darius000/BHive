#pragma once

namespace BHive
{
	struct Vector3;

	struct Vector2
	{
		Vector2();
		Vector2(float _x , float _y = 0.0f);
		Vector2(const Vector3& _vector3);
		Vector2(Vector3& _vector3);
		Vector2(const Vector2&) = default;
		Vector2(Vector2&&) = default;
		Vector2& operator=(const Vector2&) = default;
		Vector2& operator=(Vector2&&) = default;
		~Vector2();

		float x = 0.0f; //x component
		float y = 0.0f; //y component

		float GetMagnitude() const; //Get the vector magnitude - Pythagorean Theorem
		Vector2 Normalize(); //Get the unit vector

		static const Vector2 Zero(); // return a vector of zero
		static const Vector2 One(); // return a vector of one
		static Vector2 Add(const Vector2& a, const Vector2& b);
		static Vector2 Subtract(const Vector2& a, const Vector2& b);
		static Vector2 Multiply(const Vector2& v, float s);
		static Vector2 Divide(const Vector2& v, float s);
		static Vector2 Negate(Vector2& v); // Get the opposite vector
		static float DotProduct(const Vector2& a, const Vector2& b);
		static float GetAngle(const Vector2& a, const Vector2& b);

		Vector2 operator+(const Vector2& _other);
		Vector2 operator-(const Vector2& _other);
		Vector2 operator*(float _scalar);
		Vector2 operator/(float _scalar);
		Vector2 operator+=(const Vector2& _other);
		Vector2 operator-=(const Vector2& _other);
		Vector2 operator*=(float _scalar);
		Vector2 operator/=(float _scalar);
		Vector2 operator-(); // Negate vector
		float operator*(const Vector2& _other); //Dot Product
		float operator[](unsigned int index); //Get component of vector
		bool operator==(const Vector2& _other);
		bool operator!=(const Vector2& _other);

		std::string ToString() const;
	};

	inline std::ostream& operator<<(std::ostream& os, const Vector2& _vector2)
	{
		return os << _vector2.ToString();
	}
}