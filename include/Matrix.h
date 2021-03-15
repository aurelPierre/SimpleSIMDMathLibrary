#ifndef MATRIX_H
#define MATRIX_H

#include <nmmintrin.h> // used for SSE 4.2

namespace tlbx
{
	struct Matrix
	{
		float _data[4][4] {};
		
		Matrix()
		{
			_data[0][0] = 1.f;
			_data[1][1] = 1.f;
			_data[2][2] = 1.f;
			_data[3][3] = 1.f;
		}

		Matrix(float data[16])
		{
			for(size_t i = 0; i < 4; ++i)
				for(size_t j = 0; j < 4; ++j)
					_data[i][j] = data[i * 4 + j];
		}

		void mult(const Matrix& matrix, Matrix& out)
		{
			for(size_t i = 0; i < 4; ++i)
			{
				for(size_t j = 0; j < 4; ++j)
				{
					float d = 0.f; 
					for(size_t k = 0; k < 4; ++k)
						d += _data[i][k] * matrix._data[k][j];
					out._data[i][j] = d;
				}
			}
		}

		Matrix operator*(const Matrix& matrix)
		{
			Matrix m;
			mult(matrix, m);
			return m;
		}
	};

	struct MatrixSSE
	{
		__m128 _data[4];

		MatrixSSE()
		{
			_data[0] = _mm_set_ps(0.f, 0.f, 0.f, 1.f);
			_data[1] = _mm_set_ps(0.f, 0.f, 1.f, 0.f);
			_data[2] = _mm_set_ps(0.f, 1.f, 0.f, 0.f);
			_data[3] = _mm_set_ps(1.f, 0.f, 0.f, 0.f);
		}

		MatrixSSE(float data[16])
		{
			for(size_t i = 0; i < 4; ++i)
				_data[i] = _mm_set_ps(data[i * 4 + 3], data[i * 4 + 2], data[i * 4 + 1], data[i * 4]);
		}

		void mult(const MatrixSSE& matrix, MatrixSSE& out)
		{
			for(size_t i = 0; i < 4; ++i)
			{
				out._data[i] = _mm_mul_ps(_mm_shuffle_ps(_data[i], _data[i], 0x00), matrix._data[0]);
				out._data[i] = _mm_add_ps(out._data[i], _mm_mul_ps(_mm_shuffle_ps(_data[i], _data[i], 0x55), matrix._data[1]));
				out._data[i] = _mm_add_ps(out._data[i], _mm_mul_ps(_mm_shuffle_ps(_data[i], _data[i], 0xaa), matrix._data[2]));
				out._data[i] = _mm_add_ps(out._data[i], _mm_mul_ps(_mm_shuffle_ps(_data[i], _data[i], 0xff), matrix._data[3]));
			}
		}

		MatrixSSE operator*(const MatrixSSE& matrix)
		{
			MatrixSSE m;
			mult(matrix, m);
			return m;
		}
	};
}

#endif
