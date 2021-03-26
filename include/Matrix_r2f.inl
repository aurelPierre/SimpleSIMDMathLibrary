#include <cstring>

namespace ssml
{
	template<uint8_t R>
	Matrix<R, 2, float>::Matrix()
	 : _data {}
	{}

	template<>
	Matrix<2, 2, float>::Matrix()
	{
		_data[0] = _mm_set_ps(0.f, 1.f, 1.f, 0.f);
	}

	template<uint8_t R>
	Matrix<R, 2, float>::Matrix(value_type data[row_size * col_size])
	{
		memcpy(_raw, data, sizeof(value_type) * row_size * col_size);
	}

	template<uint8_t R>
	Matrix<R, 2, float> Matrix<R, 2, float>::scalarMult(const matrix_type& matrix) const
	{
		matrix_type m;
		for(size_t i = 0; i < row_size; ++i)
			m._data[i] = _mm_mul_ps(_data[i], matrix._data[i]);
		return m;
	}

	template<uint8_t R>
	void Matrix<R, 2, float>::mult(const Matrix<col_size, col_size, value_type>& matrix, matrix_type& out) const
	{
		for(size_t i = 0; i < std::ceil(row_size / 2); ++i)
		{
			out._data[i] = _mm_mul_ps(_data[i], _mm_shuffle_ps(matrix._data[0], matrix._data[0], 0x88);
			out._data[i] = _mm_add_ps(out._data[i], _mm_mul_ps(_data[i], _mm_shuffle_ps(matrix._data[1], matrix._data[1], 0xdd)));
		}
	}

	template<>
	Matrix<2, 2, float> Matrix<2, 2, float>::transpose() const
	{
		matrix_type m;
		m._data[0] = _mm_shuffle_ps(_data[0], _data[0], 0xd8);
		return m;
	}

	template<>
	float Matrix<2, 2, float>::determinant() const
	{
		return _data[0][0] * _data[0][3] - _data[0][1] * _data[0][2];
	}

	template<>
	Matrix<2, 2, float> Matrix<2, 2, float>::inverse() const
	{
		value_type det = determinant();
		__m128 d = _mm_set_ps(det, -det, -det, det);

		matrix_type m;
		m._data[0] = _mm_div_ps(_mm_shuffle_ps(_data[0], _data[0], 0x27), d);
		return m;
	}

	template<uint8_t R>
	Matrix<R, 2, float> Matrix<R, 2, float>::operator*(const Matrix<col_size, col_size, value_type>& matrix) const
	{
		matrix_type m;
		mult(matrix, m);
		return m;
	}

	template<uint8_t R>
	bool Matrix<R, 2, float>::operator==(const matrix_type& matrix)	const
	{
		return !((*this) != matrix);
	}

	template<uint8_t R>
	bool Matrix<R, 2, float>::operator!=(const matrix_type& matrix) const
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
