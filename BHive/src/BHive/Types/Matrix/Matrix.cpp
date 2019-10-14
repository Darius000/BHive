#include "BHivePCH.h"
#include "Matrix.h"

namespace BHive
{

	Matrix::Matrix() :M()
	{

	}

	Matrix::Matrix(Vector3 matrix[3]) : M()
	{
		/*M[0][0] = matrix[0][0];
		M[0][1] = matrix[0][1];
		M[0][2] = matrix[0][2];
		M[1][0] = matrix[1][0];
		M[1][1] = matrix[1][1];
		M[1][2] = matrix[1][2];
		M[2][0] = matrix[2][0];
		M[2][1] = matrix[2][1];
		M[2][2] = matrix[2][2];*/
	}

	float Matrix::operator[](unsigned int index)
	{
		return M[index][index];
	}

	FString Matrix::ToString() const
	{
		return FString() + "{" + M[0][0] + "," + M[0][1] + "," + M[0][2] +
					"," + M[1][0] + "," + M[1][1] + "," + M[1][2] +
					"," + M[2][0] + "," + M[2][1] + "," + M[2][2] + 
				"}";
	}
}