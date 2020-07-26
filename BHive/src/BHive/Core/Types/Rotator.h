#pragma once

#include "Vector3.h"

namespace BHive
{
	enum class EAxis
	{
		X,
		Y,
		Z
	};

	struct Rotator
	{
		Rotator();
		Rotator(float _roll, float _yaw, float _pitch);
		Rotator(const FVector3& vector);

		union { float roll, x, r; };
		union { float yaw,  y,  g; };
		union { float pitch, z, b; };
		
		static Rotator FromVector(const FVector3& v);

		void Normalize(); //Keep angles between 0 - 360
		void NormalizeAxis(EAxis axis); //Keep specified axis angle between 0 - 360
		bool IsNearlyZero(float tolerance = 0.000001);
		bool IsZero();
		bool IsNAN() const; // Checks if a component is nan or infinite
		float GetAxis(EAxis axis) const;
		FVector3 ToVector() const;
		BString ToString() const;
		
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