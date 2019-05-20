#pragma once


namespace BHive
{
	namespace MathLibrary
	{
		template<typename T>
		inline T Clamp(T value, T min, T max);

		template<typename T>
		inline T Normalize(T value, T min, T max);

		template<typename T>
		inline T Absolute(T value);

		inline float Modulo(float x, float y);
		inline float ModuloAngle(float x, float y);
		inline float ClampAngle(float angle, float min, float max);
		//inline float Interprolate(float value, float min, float max);

		float Modulo(float x, float y)
		{
			float v = std::fmod(x, y);
			return v;
		};

		float ModuloAngle(float x, float y)
		{
			while(x < 0) x = 360 - Absolute(x);
			return Modulo(x, y);
		}

		float ClampAngle(float angle, float min, float max) 
		{ 
			float v = Modulo(Clamp(angle, min, max), 360.0f);
			return v;
		};
	};
}

#include "MathLibrary.inl"