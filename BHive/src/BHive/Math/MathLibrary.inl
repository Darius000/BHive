#pragma once
#include "MathLibrary.h"

namespace BHive
{
	namespace MathLibrary
	{
		template<typename T>
		T Clamp(T value, T min, T max)
		{
			if (value <= min)
				return min;
			if (value >= max)
				return max;

			return value;
		}

		template<typename T>
		T Normalize(T value, T min, T max)
		{
			return (value - min) / (max - min);
		}

		template<typename T>
		T Absolute(T value)
		{
			return std::abs(value);
		}
	}
}