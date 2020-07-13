#pragma once
#include "MathLibrary.h"

namespace BHive
{
	namespace MathLibrary
	{
		template<typename T> T const& Clamp(T const& value, T const& min, T const& max)
		{
			if (value <= min) return min;
			if (value >= max) return max;
			return value;
		}

		template<typename T> T const Normalize(T const& value, T const& min, T const& max)
		{
			return (value - min) / (max - min);
		}

		template<typename T> T const Absolute(T const& value)
		{
			return std::abs(value);
		}

		template<typename T> T const Lerp(T const& v0, T const& v1, T const& t)
		{
			return (1.0f - t) * v0 + t * v1;
		}

		template<typename T> T const ToRadians(T const& degrees)
		{
			return degrees * (PI / 180.0f);
		}

		template<typename T> T const ToDegrees(T const& radians)
		{
			return radians * (180.0f / PI);
		}

		template<typename T> T const Modulo(T const& x, T const& y)
		{
			return std::fmod(x, y);
		};

		template<typename T> T const ModuloAngle(T& x, T const& y)
		{
			while (x < 0) x = 360 - Absolute(x);
			return Modulo(x, y);
		}

		template<typename T> T const ClampAngle(T const& angle, T const& min, T const& max)
		{
			return Modulo(Clamp(angle, min, max), 360.0f);
		};

		template<typename T> T const Increment(T& x, T const& amount)
		{
			return x += amount;
		}

		template<typename T> T const Decrement(T& x, T const& amount)
		{
			return x -= amount;
		}


		template<typename T>
		T  Min(T  a, T  b)
		{
			return a <= b ? a : b;
		}


		template<typename T>
		T  Max(T a, T  b)
		{
			return a >= b ? a : b;
		}

		template<typename T> bool const IsInfinte(T const& a)
		{
			return std::isnan(a);
		}

		template<typename T> bool const IsUndefinded(T const& a)
		{
			return std::isinf(a);
		}

		template<typename T> Vector2<T> const LerpVector2(const Vector2<T> &v0, const Vector2<T> &v1, float const& t)
		{
			float x = Lerp(v0.x, v1.x, t);
			float y = Lerp(v0.y, v1.y, t);

			return Vector2(x, y);
		};

		template<typename T> Vector3<T> const LerpVector3(const Vector3<T> &v0, const Vector3<T> &v1, float const& t)
		{
			float x = Lerp(v0.x, v1.x, t);
			float y = Lerp(v0.y, v1.y, t);
			float z = Lerp(v0.z, v1.z, t);

			return Vector3(x, y, z);
		}

		Rotator const LerpRotator(const Rotator &r0, const Rotator &r1, float const& t)
		{
			float x = Lerp(r0.roll, r1.roll, t);
			float y = Lerp(r0.yaw, r1.yaw, t);
			float z = Lerp(r0.pitch, r1.pitch, t);

			return Rotator(x, y, z);
		}

		float Cos(float radians)
		{
			return cos(radians);
		}

		inline float Sin(float radians)
		{
			return sin(radians);
		}
	}
}