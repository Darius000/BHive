#pragma once


namespace BHive
{
	template<typename T>
	struct Matrix3x3
	{
		Matrix3x3() {};
		Matrix3x3(Vector3<T> matrix[3]) {};

		//static Matrix Add(const Matrix& a, const Matrix& b); //Must be same size 3x3 * 3x3
		//static Matrix Subtract(const Matrix& a, const Matrix& b); //Must be same size 3x3 * 3x3
		//static Matrix Multiply(const Matrix& a, float s);
		//static Matrix Multiply(const Matrix& a, const Matrix& b); //Must have same a row size and b column size and vice versa ex. 2x3 * 3x2, M*N != N*M
		//static Matrix Identity();
		//static Matrix Inverse();
		//static Matrix Transpose();

		T operator[](uint32 index);

		BString ToString() const;

	private:
		Vector3<T> matrix[3];
	};

	template<typename T>
	inline std::ostream& operator<<(std::ostream& os, const Matrix3x3<T>& matrix)
	{
		return os << matrix.ToString();
	}

	template<typename T>
	T Matrix3x3<T>::operator[](uint32 index)
	{
		return matrix[index];
	}

	template<typename T>
	BString Matrix3x3<T>::ToString() const
	{
		return BString() + "{" + M[0][0] + "," + M[0][1] + "," + M[0][2] +
			"," + M[1][0] + "," + M[1][1] + "," + M[1][2] +
			"," + M[2][0] + "," + M[2][1] + "," + M[2][2] +
			"}";
	}
}