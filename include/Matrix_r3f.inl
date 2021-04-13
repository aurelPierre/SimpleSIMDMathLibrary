#include <cstring>
#include <utility>

namespace ssml
{
	template<matrix_size_type R>
	Matrix<R, 3, float>::Matrix()
	 : _data {}
	{}

	template<>
	Matrix<3, 3, float>::Matrix()
	{
		for(matrix_size_type i = 0; i < row_size; ++i)
			_data[i][i] = 1.f;
	}

	template<matrix_size_type R>
	Matrix<R, 3, float>::Matrix(value_type data[row_size * col_size])
	{
		memcpy(_data, data, sizeof(value_type) * row_size * col_size);
	}

	template<matrix_size_type R>
	typename Matrix<R, 3, float>::row_type& Matrix<R, 3, float>::operator[](const matrix_size_type i)
	{
		return _data[i];
	}

	template<matrix_size_type R>
	const typename Matrix<R, 3, float>::row_type& Matrix<R, 3, float>::operator[](const matrix_size_type i) const
	{
		return _data[i];
	}

	template<matrix_size_type R>
	Matrix<R, 3, float> scalarMult(const Matrix<R, 3, float>& lhs, const Matrix<R, 3, float>& rhs)
	{
		Matrix<R, 3, float> m;
		for(matrix_size_type i = 0; i < R * 3; i += 4)
		{
			_mm_store_ps(&m._data[i / R][i % R],
				 	_mm_mul_ps(_mm_load_ps(&lhs._data[i / R][i % R]),
					 	_mm_load_ps(&rhs._data[i / R][i % R])));
		}

		for(matrix_size_type i = (R * 3) - (R * 3) % 4; i < R * 3; ++i)
			m._data[R - 1][i % R] = lhs._data[R - 1][i % R] * rhs._data[R - 1][i % R];
		return m;
	}

	template<>
	Matrix<3, 3, float> transpose(const Matrix<3, 3, float>& obj)
	{
		Matrix<3, 3, float> m;
		memcpy(m._data, obj._data, sizeof(float) * 3 * 3);
		std::swap(m._data[0][1], m._data[1][0]);
		std::swap(m._data[0][2], m._data[2][0]);
		std::swap(m._data[1][2], m._data[2][1]);
		return m;
	}

	template<>
	float determinant(const Matrix<3, 3, float>& obj)
	{
		__m128 tmp1 = _mm_set_ps(obj._data[1][1], obj._data[1][0], obj._data[1][0], 0);
		__m128 tmp2 = _mm_set_ps(obj._data[2][2], obj._data[2][2], obj._data[2][1], 0);

		__m128 tmp3 = _mm_set_ps(obj._data[1][2], obj._data[1][2], obj._data[1][1], 0);
		__m128 tmp4 = _mm_set_ps(obj._data[2][1], obj._data[2][0], obj._data[2][0], 0);

		__m128 tmp5 = _mm_set_ps(obj._data[0][0], obj._data[0][1], obj._data[0][2], 0);

		__m128 det = _mm_mul_ps(tmp5, _mm_sub_ps(_mm_mul_ps(tmp1, tmp2), _mm_mul_ps(tmp3, tmp4)));

		return det[3] - det[2] + det[1];
	}

	template<>
	Matrix<3, 3, float> inverse(const Matrix<3, 3, float>& obj)
	{
		__m128 tmp1 = _mm_set_ps(obj._data[1][0], obj._data[0][1], obj._data[0][1], obj._data[1][1]);
		__m128 tmp2 = _mm_set_ps(obj._data[2][2], obj._data[1][2], obj._data[2][2], obj._data[2][2]);

		__m128 tmp3 = _mm_set_ps(obj._data[1][2], obj._data[0][2], obj._data[0][2], obj._data[1][2]);
		__m128 tmp4 = _mm_set_ps(obj._data[2][0], obj._data[1][1], obj._data[2][1], obj._data[2][1]);

		__m128 det1 = _mm_sub_ps(_mm_mul_ps(tmp1, tmp2), _mm_mul_ps(tmp3, tmp4));

		tmp1 = _mm_set_ps(obj._data[0][0], obj._data[1][0], obj._data[0][0], obj._data[0][0]);
		tmp2 = _mm_set_ps(obj._data[2][1], obj._data[2][1], obj._data[1][2], obj._data[2][2]);

		tmp3 = _mm_set_ps(obj._data[0][1], obj._data[1][1], obj._data[0][2], obj._data[0][2]);
		tmp4 = _mm_set_ps(obj._data[2][0], obj._data[2][0], obj._data[1][0], obj._data[2][0]);

		__m128 det2 = _mm_sub_ps(_mm_mul_ps(tmp1, tmp2), _mm_mul_ps(tmp3, tmp4));

		tmp2 = _mm_set1_ps(obj._data[0][0] * det1[0] - obj._data[0][1] * det1[3] + obj._data[0][2] * det2[2]);
		tmp1 = _mm_div_ps(_mm_set_ps(-1.f, 1.f, -1.f, 1.f), tmp2);
		det1 = _mm_mul_ps(det1, tmp1);
		det2 = _mm_mul_ps(det2, tmp1);

		Matrix<3, 3, float> m;
		_mm_store_ps(&m._data[0][0], det1);
		_mm_store_ps(&m._data[1][1], det2);
		m._data[2][2] = (obj._data[0][0] * obj._data[1][1] - obj._data[0][1] * obj._data[1][0]) / tmp2[0];
		return m;
	}

	template<matrix_size_type R>
	Matrix<R, 3, float> operator*(const Matrix<R, 3, float>& lhs, const Matrix<3, 3, float>& rhs)
	{
		Matrix<R, 3, float> m;

		for(matrix_size_type i = 0; i < R; ++i)
		{
			__m128 tmp = _mm_mul_ps(_mm_set1_ps(lhs._data[i][0]), _mm_setr_ps(rhs._data[0][0], rhs._data[0][1], rhs._data[0][2], 0));
			tmp = _mm_add_ps(tmp, _mm_mul_ps(_mm_set1_ps(lhs._data[i][1]), _mm_setr_ps(rhs._data[1][0], rhs._data[1][1], rhs._data[1][2], 0)));
			tmp = _mm_add_ps(tmp, _mm_mul_ps(_mm_set1_ps(lhs._data[i][2]), _mm_setr_ps(rhs._data[2][0], rhs._data[2][1], rhs._data[2][2], 0)));
			m._data[i][0] = tmp[0];
		 	m._data[i][1] = tmp[1];
			m._data[i][2] = tmp[2];
		}
		
		return m;
	}
}
