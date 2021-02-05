#pragma once
#include "MathLibrary.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>


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
		const T RemapValue(const T& v, const T& max, const T& min, const T& newmax, const T& newmin)
		{
			return newmin + (v - min) * (newmax - newmin) / (max - min);
		}

		template<typename T> 
		const T ToRadians(const T& degrees)
		{
			return degrees * ((T)PI / 180.0f);
		}

		template<typename T>  
		const T ToDegrees(const T& radians)
		{
			return radians * (180.0f / (T)PI);
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

		float CosD(float degrees)
		{
			return cos(degrees * ((float)PI / 180.0f));
		}

		float SinD(float degrees)
		{
			return sin(degrees * ((float)PI / 180.0f));
		}


		bool DecomposeMatrixToTransform(glm::mat4& transform, FVector3& translation, FVector3& rotation, FVector3& scalefactor)
		{
			// From glm::decompose in matrix_decompose.inl

			using namespace glm;
			using T = float;

			mat4 LocalMatrix(transform);

			// Normalize the matrix.
			if (epsilonEqual(LocalMatrix[3][3], static_cast<float>(0), epsilon<T>()))
				return false;

			// First, isolate perspective.  This is the messiest.
			if (
				epsilonNotEqual(LocalMatrix[0][3], static_cast<T>(0), epsilon<T>()) ||
				epsilonNotEqual(LocalMatrix[1][3], static_cast<T>(0), epsilon<T>()) ||
				epsilonNotEqual(LocalMatrix[2][3], static_cast<T>(0), epsilon<T>()))
			{
				// Clear the perspective partition
				LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
				LocalMatrix[3][3] = static_cast<T>(1);
			}

			// Next take care of translation (easy).
			translation = FVector3(LocalMatrix[3][0], LocalMatrix[3][1], LocalMatrix[3][2]);
			LocalMatrix[3] = vec4(0, 0, 0, LocalMatrix[3].w);

			vec3 Row[3];

			// Now get scale and shear.
			for (length_t i = 0; i < 3; ++i)
				for (length_t j = 0; j < 3; ++j)
					Row[i][j] = LocalMatrix[i][j];

			scalefactor;
			// Compute X scale factor and normalize first row.
			scalefactor.x = length(Row[0]);
			Row[0] = detail::scale(Row[0], static_cast<T>(1));
			scalefactor.y = length(Row[1]);
			Row[1] = detail::scale(Row[1], static_cast<T>(1));
			scalefactor.z = length(Row[2]);
			Row[2] = detail::scale(Row[2], static_cast<T>(1));

			// At this point, the matrix (in rows[]) is orthonormal.
			// Check for a coordinate system flip.  If the determinant
			// is -1, then negate the matrix and the scaling factors.
#if 0
			vec3 Pdum3;
			Pdum3 = cross(Row[1], Row[2]); // v3Cross(row[1], row[2], Pdum3);
			if (dot(Row[0], Pdum3) < 0)
			{
				for (length_t i = 0; i < 3; i++)
				{
					scalefactor[i] *= static_cast<T>(-1);
					Row[i] *= static_cast<T>(-1);
				}
			}
#endif

			rotation.y = asin(-Row[0][2]);
			if (cos(rotation.y) != 0) {
				rotation.x = atan2(Row[1][2], Row[2][2]);
				rotation.z = atan2(Row[0][1], Row[0][0]);
			}
			else {
				rotation.x = atan2(-Row[2][0], Row[1][1]);
				rotation.z = 0;
			}

			return true;
		}
	}
}