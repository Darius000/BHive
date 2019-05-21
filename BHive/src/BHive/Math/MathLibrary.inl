#pragma once
#include "MathLibrary.h"

namespace BHive
{
	namespace MathLibrary
	{
		template<typename T> T Clamp(T value, T min, T max)
		{
			if (value <= min) return min;
			if (value >= max) return max;
			return value;
		}

		template<typename T> T Normalize(T value, T min, T max)
		{
			return (value - min) / (max - min);
		}

		template<typename T> T Absolute(T value)
		{
			return std::abs(value);
		}

		template<typename T> T Lerp(T v0, T v1, T t)
		{
			return (1.0f - t) * v0 + t * v1;
		}

		template<typename T> T ToRadians(T degrees)
		{
			return degrees * (PI / 180.0f);
		}

		template<typename T> T ToDegrees(T radians)
		{
			return radians * (180.0f / PI);
		}

		template<typename T> T Modulo(T x, T y)
		{
			float v = std::fmod(x, y);
			return v;
		};

		template<typename T> T ModuloAngle(T x, T y)
		{
			while (x < 0) x = 360 - Absolute(x);
			return Modulo(x, y);
		}

		template<typename T> T ClampAngle(T angle, T min, T max)
		{
			float v = Modulo(Clamp(angle, min, max), 360.0f);
			return v;
		};

		template<typename T> T Increment(T& x, T amount)
		{
			return x += amount;
		}

		template<typename T> T Decrement(T& x, T amount)
		{
			return x -= amount;
		}

		template<typename T> bool IsInfinte(T a)
		{
			return std::isnan(a);
		}

		template<typename T> bool IsUndefinded(T a)
		{
			return std::isinf(a);
		}

		Vector2 LerpVector2(const Vector2 &v0, const Vector2 &v1, float t)
		{
			float x = Lerp(v0.x, v1.x, t);
			float y = Lerp(v0.y, v1.y, t);

			return Vector2(x, y);
		};

		Vector3 LerpVector3(const Vector3 &v0, const Vector3 &v1, float t)
		{
			float x = Lerp(v0.x, v1.x, t);
			float y = Lerp(v0.y, v1.y, t);
			float z = Lerp(v0.z, v1.z, t);

			return Vector3(x, y, z);
		}

		Rotator LerpRotator(const Rotator &r0, const Rotator &r1, float t)
		{
			float x = Lerp(r0.roll, r1.roll, t);
			float y = Lerp(r0.yaw, r1.yaw, t);
			float z = Lerp(r0.pitch, r1.pitch, t);

			return Rotator(x, y, z);
		}
	}
}