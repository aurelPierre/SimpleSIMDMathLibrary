#ifndef MATRIX_H
#define MATRIX_H

#include <cstdint> // used for fixed scalar type

#include <iostream>

#include <cmath>
#include <limits>
#include <type_traits>

template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type almost_equal(T x, T y, int ulp)
{
	return std::fabs(x - y) <= std::numeric_limits<float>::epsilon() * std::fabs(x + y) * ulp 
		|| std::fabs(x - y) < std::numeric_limits<float>::min();
}

namespace ssml
{
	template<uint8_t R, uint8_t C, class T>
	struct Matrix
	{
		static constexpr bool is_squared = R == C;

		T _data[R][C] {};
		
		Matrix();
		Matrix(float data[R*C]);

		Matrix<R, C, T> scalarMult(const Matrix<R, C, T>& matrix) const;

		template<uint8_t NC>
		void mult(const Matrix<C, NC, T>& matrix, Matrix<R, NC, T>& out) const;
		
		Matrix<R, C, T> transpose() const;
		T determinant() const;
		Matrix<R, C, T> inverse() const;

		template<uint8_t NC>
		Matrix<R, NC, T> operator*(const Matrix<C, NC, T>& matrix) const;
	
		bool operator==(const Matrix<R, C, T>& matrix) const;
		bool operator!=(const Matrix<R, C, T>& matrix) const;
	};

	template<uint8_t R, uint8_t C, class T>
	std::ostream& operator<<(std::ostream& os, const Matrix<R, C, T>& obj);

	using Matf4 = Matrix<4, 4, float>;
	using Matf4x4 = Matf4;

	using Matf3 = Matrix<3, 3, float>;
	using Matf3x3 = Matf3;
}

#include "Matrix.inl"

#endif
