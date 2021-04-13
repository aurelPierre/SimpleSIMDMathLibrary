#include <cstring>

namespace ssml
{
	template<matrix_size_type R>
	Matrix<R, 2, float>::Matrix()
	 : _data {}
	{}

	template<>
	Matrix<2, 2, float>::Matrix()
	{
		_data[0] = _mm_set_ps(0.f, 1.f, 1.f, 0.f);
	}

	template<matrix_size_type R>
	Matrix<R, 2, float>::Matrix(value_type data[row_size * col_size])
	{
		memcpy(_data, data, sizeof(value_type) * row_size * col_size);
	}

	template<matrix_size_type R>
	typename Matrix<R, 2, float>::row_type& Matrix<R, 2, float>::operator[](const matrix_size_type i)
	{
		return _row[i];
	}

	template<matrix_size_type R>
	const typename Matrix<R, 2, float>::row_type& Matrix<R, 2, float>::operator[](const matrix_size_type i) const
	{
		return _row[i];
	}

	template<matrix_size_type R>
	Matrix<R, 2, float> scalarMult(const Matrix<R, 2, float>& lhs, const Matrix<R, 2, float>& rhs)
	{
		Matrix<R, 2, float> m;
		for(matrix_size_type i = 0; i < std::ceil(R	/ 2); ++i)
			m._data[i] = _mm_mul_ps(lhs._data[i], rhs._data[i]);
		return m;
	}

	template<>
	Matrix<2, 2, float> transpose(const Matrix<2, 2, float>& obj)
	{
		Matrix<2, 2, float> m;
		m._data[0] = _mm_shuffle_ps(obj._data[0], obj._data[0], 0xd8);
		return m;
	}

	template<>
	float determinant(const Matrix<2, 2, float>& obj)
	{
		return obj[0][0] * obj[1][1] - obj[0][1] * obj[1][0];
	}

	template<>
	Matrix<2, 2, float> inverse(const Matrix<2, 2, float>& obj)
	{
		float det = determinant(obj);
		__m128 d = _mm_set_ps(det, -det, -det, det);

		Matrix<2, 2, float> m;
		m._data[0] = _mm_div_ps(_mm_shuffle_ps(obj._data[0], obj._data[0], 0x27), d);
		return m;
	}

	template<matrix_size_type R>
	Matrix<R, 2, float> operator*(const Matrix<R, 2, float>& lhs, const Matrix<2, 2, float>& rhs)
	{
		Matrix<R, 2, float> m;

		for(matrix_size_type i = 0; i < std::ceil(R / 2); ++i)
		{
			m._data[i] = _mm_mul_ps(_mm_shuffle_ps(lhs._data[i], lhs._data[i], 0xa0), _mm_shuffle_ps(rhs._data[0], rhs._data[0], 0x44));
			m._data[i] = _mm_add_ps(m._data[i], _mm_mul_ps(_mm_shuffle_ps(lhs._data[i], lhs._data[i], 0xf5), _mm_shuffle_ps(rhs._data[0], rhs._data[0], 0xee)));
		}

		return m;
	}
}
