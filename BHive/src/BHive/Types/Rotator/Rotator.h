#pragma once

namespace BHive
{
	struct Vector3;

	enum EAxis
	{
		X,
		Y,
		Z
	};

	struct Rotator
	{
		Rotator();
		Rotator(float _roll, float _yaw, float _pitch);
		Rotator(const Vector3& vector);

		float roll	= 0.0f;
		float pitch = 0.0f;
		float yaw	= 0.0f;

		static Rotator FromVector(const Vector3& v);
		static Rotator Add(const Rotator& a, const Rotator& b); //Add to components of the rotator
		static Rotator Substract(const Rotator& a, const Rotator& b);
		static Rotator Multiply(const Rotator& a, float s);
		static Rotator Divide(const Rotator& a, float s);

		void Normalize(); //Keep angles between 0 - 360
		void NormalizeAxis(EAxis axis); //Keep specified axis angle between 0 - 360
		bool IsNearlyZero(float tolerance = 0.000001);
		bool IsZero();
		bool IsNAN() const; // Checks if a component is nan or infinite
		float GetAxis(EAxis axis) const;
		Vector3 ToVector() const;
		FString ToString() const;
		
		Rotator operator+(const Rotator& r);
		Rotator operator-(const Rotator& r);
		Rotator operator+=(const Rotator& r);
		Rotator operator-=(const Rotator& r);
		Rotator operator/ (float s);
		Rotator operator/=(float s);
		Rotator operator*(float s);
		Rotator operator*=(float s);
		float operator[](unsigned int index);
		bool operator==(const Rotator& r);
		bool operator!=(const Rotator& r);

		static const Rotator Zero();
	};

	inline std::ostream& operator<<(std::ostream& os, const Rotator& rotator)
	{
		return os << rotator.ToString();
	}
}