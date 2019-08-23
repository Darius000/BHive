#pragma once
#include "DataTypes.h"

namespace BHive
{
	namespace MathLibrary
	{
		#define PI 22.0f/7.0f

		template<typename T> inline T const& Clamp(T const& value, T const& min, T const& max);
		template<typename T> inline T const Normalize(T const& value, T const& min, T const& max);
		template<typename T> inline T const Absolute(T const& value);
		template<typename T> inline T const Lerp(T const& v0, T const& v1, T const& t);
		template<typename T> inline T const ToRadians(T const& degrees);
		template<typename T> inline T const ToDegrees(T const& radians);
		template<typename T> inline T const Modulo(T const& x, T const& y);
		template<typename T> inline T const ModuloAngle(T& x, T const& y);
		template<typename T> inline T const ClampAngle(T const& angle, T const& min, T const& max);
		template<typename T> inline T const Increment(T& x, T const& amount);
		template<typename T> inline T const Decrement(T& x, T const& amount);
		template<typename T> inline T const& Min(T const& a, T const& b);
		template<typename T> inline T const& Max(T const& a, T const& b);
		template<typename T> inline bool const IsInfinte(T const& a);
		template<typename T> inline bool const IsUndefinded(T const& a);

		//inline Vector2 const ClampVector2(const Vector2 & value, const Vector2 &min, const Vector2 &max);
		//inline Vector3 const ClampVector3(const Vector3 & value, const Vector3 &min, const Vector3 &max);
		//inline Rotator const ClampRotator(const Rotator & value, const Rotator &min, const Rotator &max);

		inline Vector2 const LerpVector2(const Vector2 &v0, const Vector2 &v1, float const& t);
		inline Vector3 const LerpVector3(const Vector3 &v0, const Vector3 &v1, float const& t);
		inline Rotator const LerpRotator(const Rotator &r0, const Rotator &r1, float const& t);
		//inline Color const Lerp(const Color &v, const Color &min, const Color &max);
		//inline LinearColor const Lerp(const LinearColor &v, const LinearColor &min, const LinearColor &max);
	};
}

#include "MathLibrary.inl"