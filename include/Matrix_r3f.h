#ifndef MATRIX_R3F_H
#define MATRIX_R3F_H

#include "Matrix.h"

#include <nmmintrin.h> // used for SSE 4.2

namespace ssml
{
	template<matrix_size_type R>
	struct Matrix<R, 3, float>
	{
		static constexpr matrix_size_type	row_size 		= R;
		static constexpr matrix_size_type col_size 		= 3;
		static constexpr bool 						is_squared 	= row_size == col_size;

		using value_type 	= float;
		using row_type 		= Vector<3, float>;
		using matrix_type = Matrix<row_size, col_size, value_type>;

		alignas(16) row_type _data[row_size];
		
		Matrix();
		Matrix(value_type data[row_size * col_size]);

		row_type& operator[](const matrix_size_type i);
		const row_type& operator[](const matrix_size_type i) const;
	};
}

#include "Matrix_r3f.inl"

#endif
