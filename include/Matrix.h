#ifndef MATRIX_H
#define MATRIX_H

#include <nmmintrin.h> // used for SSE 4.2
#include <cstdint> // used for fixed scalar type

namespace ssml
{
	template<uint8_t R, uint8_t C, class T>
	struct Matrix
	{
		static constexpr bool is_squared = R == C;

		T _data[R][C] {};
		
		Matrix();
		Matrix(float data[R*C]);

		template<uint8_t NC>
		void mult(const Matrix<C, NC, T>& matrix, Matrix<R, NC, T>& out);

		template<uint8_t NC>
		Matrix<R, NC, T> operator*(const Matrix<C, NC, T>& matrix);
	};

	using Matf4x4 = Matrix<4,4,float>;
}

#include "Matrix.inl"

#endif
