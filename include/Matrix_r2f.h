#ifndef MATRIX_R2F_H
#define MATRIX_R2F_H

#include "Matrix.h"

#include <nmmintrin.h> // used for SSE 4.2

#include <cmath>

namespace ssml
{
	template<uint8_t R>
	struct Matrix<R, 2, float>
	{
		static constexpr uint8_t 	row_size 		= R;
		static constexpr uint8_t 	col_size 		= 2;
		static constexpr bool 		is_squared 	= row_size == col_size;

		using value_type 	= float;
		using matrix_type = Matrix<row_size, col_size, value_type>;

		union {
			value_type 	_raw[row_size][col_size];
			__m128 			_data[row_size % 2 == 0 ? row_size / 2 : (row_size / 2) + 1];
		};

		Matrix();
		Matrix(value_type data[row_size * col_size]);

		Matrix<R, 2, float> scalarMult(const matrix_type& matrix) const;
		void mult(const Matrix<col_size, col_size, value_type>& matrix, matrix_type& out) const;

		Matrix<R, 2, float> transpose() const;
		float determinant() const;
		Matrix<R, 2, float> inverse() const;

		Matrix<R, 2, float> operator*(const Matrix<col_size, col_size, value_type>& matrix) const;

		float* operator[](const uint8_t i);
		const float* operator[](const uint8_t i) const;

		bool operator==(const matrix_type& matrix) const;
		bool operator!=(const matrix_type& matrix) const;
	};
}

#include "Matrix_r2f.inl"

#endif
