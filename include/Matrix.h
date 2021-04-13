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
	using matrix_size_type = size_t;

	template<matrix_size_type S, class T>
	struct Vector
	{
		static constexpr matrix_size_type size = S;

		using value_type = T;

		value_type _data[size]{};

		value_type& operator[](const matrix_size_type i)
		{
			return _data[i];
		}

		const value_type& operator[](const matrix_size_type i) const
		{
			return _data[i];
		}
	};

	template<matrix_size_type R, matrix_size_type C, class T>
	struct Matrix
	{
		static constexpr matrix_size_type	row_size 		= R;
		static constexpr matrix_size_type col_size 		= C;
		static constexpr bool 						is_squared 	= row_size == col_size;

		using value_type 	= T;
		using row_type 		= Vector<C, T>;
		using matrix_type = Matrix<row_size, col_size, value_type>;

		row_type _data[row_size];
		
		Matrix();
		Matrix(value_type data[row_size * col_size]);

		row_type& operator[](const matrix_size_type i);
		const row_type& operator[](const matrix_size_type i) const;
	};
	
	template<matrix_size_type R, matrix_size_type C, class T>
	Matrix<R, C, T> scalarMult(const Matrix<R, C, T>& lhs, const Matrix<R, C, T>& rhs);
	
	template<matrix_size_type R, class T>
	Matrix<R, R, T> transpose(const Matrix<R, R, T>& obj);
	
	template<matrix_size_type R, class T>
	T determinant(const Matrix<R, R, T>& obj);

	template<matrix_size_type R, class T>
	Matrix<R, R, T> inverse(const Matrix<R, R, T>& obj);

	template<matrix_size_type R, matrix_size_type C, class T, matrix_size_type NC>
	Matrix<R, NC, T> operator*(const Matrix<R, C, T>& lhs, const Matrix<C, NC, T>& rhs);

	template<matrix_size_type R, matrix_size_type C, class T>
	bool operator==(const Matrix<R, C, T>& lhs, const Matrix<R, C, T>& rhs);

	template<matrix_size_type R, matrix_size_type C, class T>
	bool operator!=(const Matrix<R, C, T>& lhs, const Matrix<R, C, T>& rhs);

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

#include "Matrix_r2f.h"
#include "Matrix_r3f.h"
#include "Matrix_r4f.h"

#endif
