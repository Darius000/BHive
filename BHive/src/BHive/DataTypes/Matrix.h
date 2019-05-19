#pragma once


namespace BHive
{
	struct Matrix
	{
		Matrix();;
		Matrix(Vector3 matrix[3]);
		Matrix(const Matrix&) = default;
		Matrix(Matrix&&) = default;
		Matrix& operator=(const Matrix&) = default;
		Matrix& operator=(Matrix&&) = default;
		~Matrix() {}

		//static Matrix Add(const Matrix& a, const Matrix& b); //Must be same size 3x3 * 3x3
		//static Matrix Subtract(const Matrix& a, const Matrix& b); //Must be same size 3x3 * 3x3
		//static Matrix Multiply(const Matrix& a, float s);
		//static Matrix Multiply(const Matrix& a, const Matrix& b); //Must have same a row size and b column size and vice versa ex. 2x3 * 3x2, M*N != N*M
		//static Matrix Identity();
		//static Matrix Inverse();
		//static Matrix Transpose();

		float operator[](unsigned int index);

		std::string ToString() const;

	private:

		float M[3][3];
	};

	inline std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
	{
		return os << matrix.ToString();
	}
}