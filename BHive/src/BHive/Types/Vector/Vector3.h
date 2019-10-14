#pragma once

namespace BHive
{
	struct Vector2;
		
	/*Three component vector*/

	struct Vector3
	{
		Vector3();
		Vector3(float _x);
		Vector3(float _x, float _y , float _z);
		Vector3(const Vector2& _vector2, float _z);
		Vector3(Vector2& _vector2, float _z = 0.0f);
		Vector3(const Vector3& other);
		//Vector3(Vector3&&) = default;
		//Vector3& operator=(const Vector3&) = default;
		//Vector3& operator=(Vector3&&) = default;

		float x; //x component
		float y; //y component
		float z; //z component

		float GetMagnitude() const; //Get the vector magnitude - Pythagorean Theorem
		Vector3 Normalize(); //Get the unit vector

		static const Vector3 Zero(); // return a vector of zero
		static const Vector3 One(); // return a vector of one
		static Vector3 Add(const Vector3& a, const Vector3& b);
		static Vector3 Subtract(const Vector3& a, const Vector3& b);
		static Vector3 Multiply(const Vector3& v, float s);
		static Vector3 Divide(const Vector3& v, float s); 
		static Vector3 Negate(Vector3& v); // Get the opposite vector
		static float DotProduct(const Vector3& a, const Vector3& b);
		static float GetAngle(const Vector3& a, const Vector3& b);
		static Vector3 CrossProduct(const Vector3& a, const Vector3& b);

		Vector3 operator+(const Vector3& _other);
		Vector3 operator-(const Vector3& _other);
		Vector3 operator*(float _scalar);
		Vector3 operator/(float _scalar);
		Vector3 operator+=(const Vector3& _other);
		Vector3 operator-=(const Vector3& _other);
		Vector3 operator*=(float _scalar);
		Vector3 operator/=(float _scalar);
		Vector3 operator-(); // Negate vector
		float operator*(const Vector3& _other); //Dot Product
		Vector3 operator^(const Vector3& _other); //Cross Product
		float operator[](unsigned int index); //Get component of vector
		bool operator==(const Vector3& _other);
		bool operator!=(const Vector3& _other);

		FString ToString() const; //return as string object
	};

	inline std::ostream& operator<<(std::ostream& os, const Vector3& _vector3)
	{
		return os << _vector3.ToString();
	}
}


