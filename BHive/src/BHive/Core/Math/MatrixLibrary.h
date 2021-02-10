#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

namespace BHive
{
	namespace MatrixLibrary
	{
		inline bool DecomposeMatrixToTransform(const glm::mat4& transformionMatrix, FVector3& translation, Rotator& rotation, FVector3& scale);
	}
}

#include "MatrixLibrary.inl"