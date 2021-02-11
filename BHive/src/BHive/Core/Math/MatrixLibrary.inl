#pragma once

namespace BHive
{ 
	namespace MatrixLibrary
	{
		bool DecomposeMatrixToTransform(const glm::mat4& transformionMatrix, FVector3& translation, Rotator& rotation, FVector3& scale)
		{
			/*auto localMatrix = transformionMatrix;

			//extract translation from last column since its not affected
			//by the scale or rotation
			auto& tx = localMatrix[3][0];
			auto& ty = localMatrix[3][1];
			auto& tz = localMatrix[3][2];

			auto translation = FVector3(tx, ty, tz);

			tx = ty = tz = 0.0f;
			 
			auto& c0 = localMatrix[0];
			auto& c1 = localMatrix[1];
			auto& c2 = localMatrix[2];

			//extract scale getting length of first 3 columns
			auto sx = glm::length(c0);
			auto sy = glm::length(c1);
			auto sz = glm::length(c2);

			auto scale = FVector3(sx, sy, sz);

			c0 = glm::normalize(c0);
			c1 = glm::normalize(c1);
			c2 = glm::normalize(c2);

			Quaternion quat = Quaternion(localMatrix);
			auto rotation = quat.ToRotator(quat);

			auto oldRotation = transform.GetRotation();
			auto deltaRotation = rotation - oldRotation;
			auto newRotation = oldRotation + deltaRotation;

			transform = Transform(translation, rotation, scale);*/

			using namespace glm;
			using T = float;

			mat4 LocalMatrix(transformionMatrix);

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
#if 1
			vec3 Pdum3;
#endif
			vec3 Row[3];

			// Now get scale and shear.
			for (length_t i = 0; i < 3; ++i)
				for (length_t j = 0; j < 3; ++j)
					Row[i][j] = LocalMatrix[i][j];

			// Compute X scale factor and normalize first row.
			scale.x = length(Row[0]);
			Row[0] = detail::scale(Row[0], static_cast<T>(1));
			scale.y = length(Row[1]);
			Row[1] = detail::scale(Row[1], static_cast<T>(1));
			scale.z = length(Row[2]);
			Row[2] = detail::scale(Row[2], static_cast<T>(1));

			// At this point, the matrix (in rows[]) is orthonormal.
			// Check for a coordinate system flip.  If the determinant
			// is -1, then negate the matrix and the scaling factors.
#if 1
			Pdum3 = cross(Row[1], Row[2]); // v3Cross(row[1], row[2], Pdum3);
			if (dot(Row[0], Pdum3) < 0)
			{
				for (length_t i = 0; i < 3; i++)
				{
					scale[i] *= static_cast<T>(-1);
					Row[i] *= static_cast<T>(-1);
				}
			}
#endif
			mat4 matrix = mat4(vec4(Row[0], 0.0f), vec4(Row[1], 0.0f), 
				vec4(Row[2], 0.0f), vec4(0, 0, 0, LocalMatrix[3].w));

			Quaternion quat = Quaternion(matrix);
			rotation = quat.ToRotator();

			return true;	
		}

	}

}