#ifndef MATRIX_H
#define MATRIX_H

#include <nmmintrin.h> // used for SSE 4.2
#include <cstdint> // used for fixed scalar type

#include <iostream>

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
	
		bool operator==(const Matrix<R, C, T>& matrix);
		bool operator!=(const Matrix<R, C, T>& matrix);
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
