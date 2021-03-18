#ifndef MATRIX_R4F_H
#define MATRIX_R4F_H

#include "Matrix.h"

#include <nmmintrin.h> // used for SSE 4.2

namespace ssml
{
	template<uint8_t R>
	struct Matrix<R, 4, float>
	{
		static constexpr bool is_squared = R == 4;

		__m128 _data[R] {};

		Matrix();
		Matrix(float data[4 * R]);

		Matrix<R, 4, float> scalarMult(const Matrix<R, 4, float>& matrix) const;
		void mult(const Matrix<4, 4, float>& matrix, Matrix<R, 4, float>& out) const;

		Matrix<R, 4, float> transpose() const;
		float determinant() const;
		Matrix<R, 4, float> inverse() const;

		Matrix<R, 4, float> operator*(const Matrix<4, 4, float>& matrix) const;

		bool operator==(const Matrix<R, 4, float>& matrix) const;
		bool operator!=(const Matrix<R, 4, float>& matrix) const;
	};
}

#include "Matrix_r4f.inl"

#endif
