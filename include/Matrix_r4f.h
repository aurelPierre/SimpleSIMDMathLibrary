#ifndef MATRIX_R4F_H
#define MATRIX_R4F_H

#include "Matrix.h"

namespace ssml
{
	template<uint8_t R>
	struct Matrix<R, 4, float>
	{
		static constexpr bool is_squared = R == 4;

		__m128 _data[R] {};

		Matrix();
		Matrix(float data[4 * R]);

		void mult(const Matrix<4, 4, float>& matrix, Matrix<R, 4, float>& out);

		Matrix<R, 4, float> operator*(const Matrix<4, 4, float>& matrix);

		bool operator==(const Matrix<R, 4, float>& matrix);
		bool operator!=(const Matrix<R, 4, float>& matrix);
	};
}

#include "Matrix_r4f.inl"

#endif
