#pragma  once

namespace BHive
{
	namespace MathLibrary
	{
		constexpr float PI  = 22.0f/7.0f;

		template<typename T> inline const T& Clamp( const T& value, const T& min,  const T& max);
		template<typename T> inline const T  Normalize( const T& value,  const T& min,  const T& max);
		template<typename T> inline const T  Absolute( const T& value);
		template<typename T> inline const T  Lerp(const T& v0,  const T& v1,  const T& t);
		template<typename T> inline const T  ToRadians(const T& degrees);
		template<typename T> inline const T  ToDegrees(const T& radians);
		template<typename T> inline const T  Modulo(const T& x, const T& y);
		template<typename T> inline const T  ModuloAngle(T& x, const T& y);
		template<typename T> inline const T  ClampAngle(const T& angle, const T& min, const T& max);
		template<typename T> inline const T  Increment(T& x, const T& amount);
		template<typename T> inline const T  Decrement(T& x, const T& amount);
		template<typename T> inline T Min(T  a, T  b);
		template<typename T> inline T Max(T  a, T  b);
		template<typename T> inline bool const IsInfinte( const T& a);
		template<typename T> inline bool const IsUndefinded( const T& a);

		//inline Vector2 const ClampVector2(const Vector2 & value, const Vector2 &min, const Vector2 &max);
		//inline Vector3 const ClampVector3(const Vector3 & value, const Vector3 &min, const Vector3 &max);
		//inline Rotator const ClampRotator(const Rotator & value, const Rotator &min, const Rotator &max);

		template<typename T> inline  const Vector2<T> LerpVector2(const Vector2<T>& v0, const Vector2<T>& v1, const float& t);
		template<typename T> inline  const Vector3<T> LerpVector3(const Vector3<T>& v0, const Vector3<T>& v1, const float& t);
		inline const Rotator LerpRotator(const Rotator &r0, const Rotator &r1,  const float& t);
		inline float Cos(float radians);
		inline float Sin(float radians);
		//inline Color const Lerp(const Color &v, const Color &min, const Color &max);
		//inline LinearColor const Lerp(const LinearColor &v, const LinearColor &min, const LinearColor &max);
	};
}

#include "MathLibrary.inl"
