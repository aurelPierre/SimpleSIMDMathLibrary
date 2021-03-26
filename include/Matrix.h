#ifndef MATRIX_H
#define MATRIX_H

#include <cstdint> // used for fixed scalar type

#include <iostream>

#include <cmath>
#include <limits>
#include <type_traits>

// from cppreference
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
		static constexpr uint8_t 	row_size 		= R;
		static constexpr uint8_t 	col_size 		= C;
		static constexpr bool 		is_squared 	= row_size == col_size;

		using value_type 	= T;
		using matrix_type = Matrix<row_size, col_size, value_type>;

		value_type _data[row_size][col_size] {};
		
		Matrix();
		Matrix(value_type data[row_size * col_size]);

		Matrix<R, C, T> scalarMult(const matrix_type& matrix) const;
		template<uint8_t NC>
		void mult(const Matrix<col_size, NC, value_type>& matrix, Matrix<row_size, NC, value_type>& out) const;
		
		Matrix<R, C, T> transpose() const;
		T determinant() const;
		Matrix<R, C, T> inverse() const;

		template<uint8_t NC>
		Matrix<R, NC, T> operator*(const Matrix<col_size, NC, value_type>& matrix) const;
	
		bool operator==(const matrix_type& matrix) const;
		bool operator!=(const matrix_type& matrix) const;
	};

	template<uint8_t R, uint8_t C, class T>
	std::ostream& operator<<(std::ostream& os, const Matrix<R, C, T>& obj);

	using Matf4 = Matrix<4, 4, float>;
	using Matf4x4 = Matf4;

	using Matf3 = Matrix<3, 3, float>;
	using Matf3x3 = Matf3;

	using Matf2 = Matrix<2, 2, float>;
	using Matf2x2 = Matf2;
}

#include "Matrix.inl"

#endif
