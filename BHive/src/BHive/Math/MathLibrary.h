#pragma once
#include "DataTypes.h"

namespace BHive
{
	namespace MathLibrary
	{
		#define PI 22.0f/7.0f

		template<typename T> inline T Clamp(T value, T min, T max);
		template<typename T> inline T Normalize(T value, T min, T max);
		template<typename T> inline T Absolute(T value);
		template<typename T> inline T Lerp(T v0, T v1, T t);
		template<typename T> inline T ToRadians(T degrees);
		template<typename T> inline T ToDegrees(T radians);
		template<typename T> inline T Modulo(T x, T y);
		template<typename T> inline T ModuloAngle(T x, T y);
		template<typename T> inline T ClampAngle(T angle, T min, T max);
		template<typename T> inline T Increment(T& x, T amount);
		template<typename T> inline T Decrement(T& x, T amount);
		template<typename T> inline bool IsInfinte(T a);
		template<typename T> inline bool IsUndefinded(T a);

		//inline Vector2 ClampVector2(const Vector2 & value, const Vector2 &min, const Vector2 &max);
		//inline Vector3 ClampVector3(const Vector3 & value, const Vector3 &min, const Vector3 &max);
		//inline Rotator ClampRotator(const Rotator & value, const Rotator &min, const Rotator &max);

		inline Vector2 LerpVector2(const Vector2 &v0, const Vector2 &v1, float t);
		inline Vector3 LerpVector3(const Vector3 &v0, const Vector3 &v1, float t);
		inline Rotator LerpRotator(const Rotator &r0, const Rotator &r1, float t);
		//inline Color Lerp(const Color &v, const Color &min, const Color &max);
		//inline LinearColor Lerp(const LinearColor &v, const LinearColor &min, const LinearColor &max);
	};
}

#include "MathLibrary.inl"