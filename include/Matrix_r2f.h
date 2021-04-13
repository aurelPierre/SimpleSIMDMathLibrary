#ifndef MATRIX_R2F_H
#define MATRIX_R2F_H

#include "Matrix.h"

#include <nmmintrin.h> // used for SSE 4.2

#include <cmath>

namespace ssml
{
	template<matrix_size_type R>
	struct Matrix<R, 2, float>
	{
		static constexpr matrix_size_type	row_size 		= R;
		static constexpr matrix_size_type col_size 		= 2;
		static constexpr bool 						is_squared 	= row_size == col_size;

		using value_type 	= float;
		using row_type 		= Vector<2, float>;
		using matrix_type = Matrix<row_size, col_size, value_type>;

		union alignas(16) {
			__m128  	 _data[row_size % 2 == 0 ? row_size / 2 : (row_size / 2) + 1];
			row_type   _row[row_size];
		};

		Matrix();
		Matrix(value_type data[row_size * col_size]);

		row_type& operator[](const matrix_size_type i);
		const row_type& operator[](const matrix_size_type i) const;
	};
}

#include "Matrix_r2f.inl"

#endif
