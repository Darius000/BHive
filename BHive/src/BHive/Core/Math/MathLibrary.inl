#pragma once
#include "MathLibrary.h"

namespace BHive
{
	namespace MathLibrary
	{
		template<typename T>  
		const T& Clamp(const T& value,  const T& min,  const T& max)
		{
			if (value <= min) return min;
			if (value >= max) return max;
			return value;
		}

		template<typename T> 
		const T Normalize( const T& value, const T& min,  const T& max)
		{
			return (value - min) / (max - min);
		}

		template<typename T> const T  Absolute( const T& value)
		{
			return std::abs(value);
		}

		template<typename T> T 
		const Lerp( const T& v0,  const T& v1,  const T& t)
		{
			return (1.0f - t) * v0 + t * v1;
		}

		template<typename T> 
		const T ToRadians(const T& degrees)
		{
			return degrees * (PI / 180.0f);
		}

		template<typename T>  
		const T ToDegrees(const T& radians)
		{
			return radians * (180.0f / PI);
		}

		template<typename T>  
		const T Modulo( const T& x,  const T& y)
		{
			return std::fmod(x, y);
		};

		template<typename T> 
		const  T ModuloAngle(T& x,  const T& y)
		{
			while (x < 0) x = 360 - Absolute(x);
			return Modulo(x, y);
		}

		template<typename T>  
		const T ClampAngle(const T& angle,  const T& min,  const T& max)
		{
			return Modulo(Clamp(angle, min, max), 360.0f);
		};

		template<typename T>  
		const T Increment(T& x,  const T& amount)
		{
			return x += amount;
		}

		template<typename T>  
		const T Decrement(T& x,  const T& amount)
		{
			return x -= amount;
		}


		template<typename T>
		T  Min(T  a, T  b)
		{
			return (a <= b) ? a : b;
		}


		template<typename T>
		T  Max(T a, T  b)
		{
			return (a >= b) ? a : b;
		}

		template<typename T> 
		const bool IsInfinte( const T& a)
		{
			return std::isnan(a);
		}

		template<typename T> 
		const bool IsUndefinded(const T& a)
		{
			return std::isinf(a);
		}

		template<typename T> 
		const Vector2<T> LerpVector2(const Vector2<T> &v0, const Vector2<T> &v1,  const float& t)
		{
			float x = Lerp(v0.x, v1.x, t);
			float y = Lerp(v0.y, v1.y, t);

			return Vector2(x, y);
		};

		template<typename T> 
		const Vector3<T>  LerpVector3(const Vector3<T> &v0, const Vector3<T> &v1,  const float& t)
		{
			float x = Lerp(v0.x, v1.x, t);
			float y = Lerp(v0.y, v1.y, t);
			float z = Lerp(v0.z, v1.z, t);

			return Vector3(x, y, z);
		}

		const Rotator  LerpRotator(const Rotator &r0, const Rotator &r1,  const float& t)
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

		float Sin(float radians)
		{
			return sin(radians);
		}
	}
}