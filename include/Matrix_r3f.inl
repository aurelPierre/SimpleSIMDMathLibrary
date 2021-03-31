#include <cstring>
#include <random>
#include <utility>
#include <xmmintrin.h>

namespace ssml
{
	template<uint8_t R>
	Matrix<R, 3, float>::Matrix()
	 : _data {}
	{}

	template<>
	Matrix<3, 3, float>::Matrix()
	{
		for(size_t i = 0; i < row_size; ++i)
			_data[i][i] = 1.f;
	}

	template<uint8_t R>
	Matrix<R, 3, float>::Matrix(value_type data[row_size * col_size])
	{
		memcpy(_data, data, sizeof(value_type) * row_size * col_size);
	}

	template<uint8_t R>
	Matrix<R, 3, float> Matrix<R, 3, float>::scalarMult(const matrix_type& matrix) const
	{
		matrix_type m;
		for(size_t i = 0; i < row_size * col_size; i += 4)
		{
			_mm_store_ps(&m._data[i / row_size][i % row_size],
				 	_mm_mul_ps(_mm_load_ps(&_data[i / row_size][i % row_size]),
					 	_mm_load_ps(&matrix._data[i / row_size][i % row_size])));
		}

		for(size_t i = (row_size * col_size) - (row_size * col_size) % 4; i < row_size * col_size; ++i)
			m._data[row_size - 1][i % row_size] = _data[row_size - 1][i % row_size] * matrix._data[row_size - 1][i % row_size];
		return m;
	}

	template<uint8_t R>
	void Matrix<R, 3, float>::mult(const Matrix<col_size, col_size, value_type>& matrix, matrix_type& out) const
	{
		for(size_t i = 0; i < row_size; ++i)
		{
			__m128 tmp = _mm_mul_ps(_mm_set1_ps(_data[i][0]), _mm_setr_ps(matrix._data[0][0], matrix._data[0][1], matrix._data[0][2], 0));
			tmp = _mm_add_ps(tmp, _mm_mul_ps(_mm_set1_ps(_data[i][1]), _mm_setr_ps(matrix._data[1][0], matrix._data[1][1], matrix._data[1][2], 0)));
			tmp = _mm_add_ps(tmp, _mm_mul_ps(_mm_set1_ps(_data[i][2]), _mm_setr_ps(matrix._data[2][0], matrix._data[2][1], matrix._data[2][2], 0)));
			out._data[i][0] = tmp[0];
		 	out._data[i][1] = tmp[1];
			out._data[i][2] = tmp[2];
		}
	}

	template<>
	Matrix<3, 3, float> Matrix<3, 3, float>::transpose() const
	{
		matrix_type m;
		memcpy(m._data, _data, sizeof(value_type) * row_size * col_size);
		std::swap(m._data[0][1], m._data[1][0]);
		std::swap(m._data[0][2], m._data[2][0]);
		std::swap(m._data[1][2], m._data[2][1]);
		return m;
	}

	template<>
	float Matrix<3, 3, float>::determinant() const
	{
		__m128 tmp1 = _mm_set_ps(_data[1][1], _data[1][0], _data[1][0], 0);
		__m128 tmp2 = _mm_set_ps(_data[2][2], _data[2][2], _data[2][1], 0);

		__m128 tmp3 = _mm_set_ps(_data[1][2], _data[1][2], _data[1][1], 0);
		__m128 tmp4 = _mm_set_ps(_data[2][1], _data[2][0], _data[2][0], 0);

		__m128 tmp5 = _mm_set_ps(_data[0][0], _data[0][1], _data[0][2], 0);

		__m128 det = _mm_mul_ps(tmp5, _mm_sub_ps(_mm_mul_ps(tmp1, tmp2), _mm_mul_ps(tmp3, tmp4)));

		return det[3] - det[2] + det[1];
	}

	template<>
	Matrix<3, 3, float> Matrix<3, 3, float>::inverse() const
	{
		__m128 tmp1 = _mm_set_ps(_data[1][0], _data[0][1], _data[0][1], _data[1][1]);
		__m128 tmp2 = _mm_set_ps(_data[2][2], _data[1][2], _data[2][2], _data[2][2]);

		__m128 tmp3 = _mm_set_ps(_data[1][2], _data[0][2], _data[0][2], _data[1][2]);
		__m128 tmp4 = _mm_set_ps(_data[2][0], _data[1][1], _data[2][1], _data[2][1]);

		__m128 det1 = _mm_sub_ps(_mm_mul_ps(tmp1, tmp2), _mm_mul_ps(tmp3, tmp4));

		tmp1 = _mm_set_ps(_data[0][0], _data[1][0], _data[0][0], _data[0][0]);
		tmp2 = _mm_set_ps(_data[2][1], _data[2][1], _data[1][2], _data[2][2]);

		tmp3 = _mm_set_ps(_data[0][1], _data[1][1], _data[0][2], _data[0][2]);
		tmp4 = _mm_set_ps(_data[2][0], _data[2][0], _data[1][0], _data[2][0]);

		__m128 det2 = _mm_sub_ps(_mm_mul_ps(tmp1, tmp2), _mm_mul_ps(tmp3, tmp4));

		tmp2 = _mm_set1_ps(_data[0][0] * det1[0] - _data[0][1] * det1[3] + _data[0][2] * det2[2]);
		tmp1 = _mm_div_ps(_mm_set_ps(-1.f, 1.f, -1.f, 1.f), tmp2);
		det1 = _mm_mul_ps(det1, tmp1);
		det2 = _mm_mul_ps(det2, tmp1);

		matrix_type m;
		_mm_store_ps(&m._data[0][0], det1);
		_mm_store_ps(&m._data[1][1], det2);
		m._data[2][2] = (_data[0][0] * _data[1][1] - _data[0][1] * _data[1][0]) / tmp2[0];
		return m;
	}

	template<uint8_t R>
	Matrix<R, 3, float> Matrix<R, 3, float>::operator*(const Matrix<col_size, col_size, value_type>& matrix) const
	{
		matrix_type m;
		mult(matrix, m);
		return m;
	}

	template<uint8_t R>
	float* Matrix<R, 3, float>::operator[](const uint8_t i)
	{
		return _data[i];
	}

	template<uint8_t R>
	const float* Matrix<R, 3, float>::operator[](const uint8_t i) const
	{
		return _data[i];
	}

	template<uint8_t R>
	bool Matrix<R, 3, float>::operator==(const matrix_type& matrix)	const
	{
		return !((*this) != matrix);
	}

	template<uint8_t R>
	bool Matrix<R, 3, float>::operator!=(const matrix_type& matrix) const
	{
		for(size_t i = 0; i < row_size; ++i)
		{
			for(size_t j = 0; j < col_size; ++j)
			{
				if(!almost_equal(_data[i][j], matrix._data[i][j], 2))
					return true;
			}
		}
		return false;
	}
}
