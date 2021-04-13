namespace ssml
{
	template<matrix_size_type R>
	Matrix<R, 4, float>::Matrix()
	 : _row {}
	{}

	template<>
	Matrix<4, 4, float>::Matrix()
	{
		_data[0] = _mm_set_ps(0.f, 0.f, 0.f, 1.f);
		_data[1] = _mm_set_ps(0.f, 0.f, 1.f, 0.f);
		_data[2] = _mm_set_ps(0.f, 1.f, 0.f, 0.f);
		_data[3] = _mm_set_ps(1.f, 0.f, 0.f, 0.f);
	}

	template<matrix_size_type R>
	Matrix<R, 4, float>::Matrix(value_type data[row_size * col_size])
	{
		memcpy(_row, data, sizeof(value_type) * row_size * col_size);
	}

	template<matrix_size_type R>
	typename Matrix<R, 4, float>::row_type& Matrix<R, 4, float>::operator[](const matrix_size_type i)
	{
		return _row[i];
	}

	template<matrix_size_type R>
	const typename Matrix<R, 4, float>::row_type& Matrix<R, 4, float>::operator[](const matrix_size_type i) const
	{
		return _row[i];
	}

	template<matrix_size_type R>
	Matrix<R, 4, float> scalarMult(const Matrix<R, 4, float>& lhs, const Matrix<R, 4, float>& rhs)
	{
		Matrix<R, 4, float> m;
		for(matrix_size_type i = 0; i < R; ++i)
			m._data[i] = _mm_mul_ps(lhs._data[i], rhs._data[i]);
		return m;
	}

	template<>
	Matrix<4, 4, float> transpose(const Matrix<4, 4, float>& obj)
	{
		__m128 r0 = _mm_unpacklo_ps(obj._data[0], obj._data[1]);
		__m128 r1 = _mm_unpackhi_ps(obj._data[0], obj._data[1]);

		__m128 r2 = _mm_unpacklo_ps(obj._data[2], obj._data[3]);
		__m128 r3 = _mm_unpackhi_ps(obj._data[2], obj._data[3]);

		Matrix<4, 4, float> m;

		m._data[0] = _mm_movelh_ps(r0, r2);
		m._data[1] = _mm_movehl_ps(r2, r0);

		m._data[2] = _mm_movelh_ps(r1, r3);
		m._data[3] = _mm_movehl_ps(r3, r1);

		return m;
	}

	template<>
	float determinant(const Matrix<4, 4, float>& obj)
	{
		__m128 m0 = _mm_movelh_ps(obj._data[0], obj._data[1]);
		__m128 m1 = _mm_movehl_ps(obj._data[1], obj._data[0]);

		__m128 m2 = _mm_movelh_ps(obj._data[2], obj._data[3]);
		__m128 m3 = _mm_movehl_ps(obj._data[3], obj._data[2]);

		__m128 det = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(obj._data[0], obj._data[2], 0x88), _mm_shuffle_ps(obj._data[1], obj._data[3], 0xdd)),
			 	_mm_mul_ps(_mm_shuffle_ps(obj._data[0], obj._data[2], 0xdd), _mm_shuffle_ps(obj._data[1], obj._data[3], 0x88)));

		__m128 m0_m1 = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(m0, m0, 0x0f), m1), _mm_mul_ps(_mm_shuffle_ps(m0, m0, 0xa5), _mm_shuffle_ps(m1, m1, 0x4e)));
		__m128 m3_m2 = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(m3, m3, 0x0f), m2), _mm_mul_ps(_mm_shuffle_ps(m3, m3, 0xa5), _mm_shuffle_ps(m2, m2, 0x4e)));

		__m128 tr = _mm_mul_ps(m0_m1, _mm_shuffle_ps(m3_m2, m3_m2, 0xd8));
		
		return det[0] * det[3] + det[1] * det[2] - (tr[0] + tr[1] + tr[2] + tr[3]);
	}

	template<>
	Matrix<4, 4, float> inverse(const Matrix<4, 4, float>& obj)
	{
		__m128 m0 = _mm_movelh_ps(obj._data[0], obj._data[1]);
		__m128 m1 = _mm_movehl_ps(obj._data[1], obj._data[0]);

		__m128 m2 = _mm_movelh_ps(obj._data[2], obj._data[3]);
		__m128 m3 = _mm_movehl_ps(obj._data[3], obj._data[2]);

		__m128 det = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(obj._data[0], obj._data[2], 0x88), _mm_shuffle_ps(obj._data[1], obj._data[3], 0xdd)),
			 		_mm_mul_ps(_mm_shuffle_ps(obj._data[0], obj._data[2], 0xdd), _mm_shuffle_ps(obj._data[1], obj._data[3], 0x88)));

		__m128 m0_m1 = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(m0, m0, 0x0f), m1), _mm_mul_ps(_mm_shuffle_ps(m0, m0, 0xa5), _mm_shuffle_ps(m1, m1, 0x4e)));
		__m128 m3_m2 = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(m3, m3, 0x0f), m2), _mm_mul_ps(_mm_shuffle_ps(m3, m3, 0xa5), _mm_shuffle_ps(m2, m2, 0x4e)));

		__m128 tr = _mm_mul_ps(m0_m1, _mm_shuffle_ps(m3_m2, m3_m2, 0xd8));

		__m128 x_ = _mm_sub_ps(_mm_mul_ps(_mm_set1_ps(det[3]), m0), _mm_add_ps(
					_mm_mul_ps(m1, _mm_shuffle_ps(m3_m2, m3_m2, 0xcc)),
					_mm_mul_ps(_mm_shuffle_ps(m1, m1, 0xb1), _mm_shuffle_ps(m3_m2, m3_m2, 0x66))));

		__m128 w_ = _mm_sub_ps(_mm_mul_ps(_mm_set1_ps(det[0]), m3), _mm_add_ps(
					_mm_mul_ps(m2, _mm_shuffle_ps(m0_m1, m0_m1, 0xcc)),
					_mm_mul_ps(_mm_shuffle_ps(m2, m2, 0xb1), _mm_shuffle_ps(m0_m1, m0_m1, 0x66))));

		__m128 y_ = _mm_sub_ps(_mm_mul_ps(_mm_set1_ps(det[1]), m2), _mm_sub_ps(
					_mm_mul_ps(m3, _mm_shuffle_ps(m0_m1, m0_m1, 0x33)),
					_mm_mul_ps(_mm_shuffle_ps(m3, m3, 0xb1), _mm_shuffle_ps(m0_m1, m0_m1, 0x66))));

		__m128 z_ = _mm_sub_ps(_mm_mul_ps(_mm_set1_ps(det[2]), m1), _mm_sub_ps(
					_mm_mul_ps(m0, _mm_shuffle_ps(m3_m2, m3_m2, 0x33)),
					_mm_mul_ps(_mm_shuffle_ps(m0, m0, 0xb1), _mm_shuffle_ps(m3_m2, m3_m2, 0x66))));

		det = _mm_set1_ps(det[0] * det[3] + det[1] * det[2] - (tr[0] + tr[1] + tr[2] + tr[3]));
		det = _mm_div_ps(_mm_set_ps(1.f, -1.f, -1.f, 1.f), det);

		x_ = _mm_mul_ps(x_, det);
		y_ = _mm_mul_ps(y_, det);
		z_ = _mm_mul_ps(z_, det);
		w_ = _mm_mul_ps(w_, det);
	
		Matrix<4, 4, float> m;

		m._data[0] = _mm_shuffle_ps(x_, y_, 0x77);
		m._data[1] = _mm_shuffle_ps(x_, y_, 0x22);
		m._data[2] = _mm_shuffle_ps(z_, w_, 0x77);
		m._data[3] = _mm_shuffle_ps(z_, w_, 0x22);;

		return m;
	}

	template<matrix_size_type R>
	Matrix<R, 4, float> operator*(const Matrix<R, 4, float>& lhs, const Matrix<4, 4, float>& rhs)
	{
		Matrix<R, 4, float> m;
		
		for(matrix_size_type i = 0; i < R; ++i)
		{
			m._data[i] = _mm_mul_ps(_mm_shuffle_ps(lhs._data[i], lhs._data[i], 0x00), rhs._data[0]);
			m._data[i] = _mm_add_ps(m._data[i], _mm_mul_ps(_mm_shuffle_ps(lhs._data[i], lhs._data[i], 0x55), rhs._data[1]));
			m._data[i] = _mm_add_ps(m._data[i], _mm_mul_ps(_mm_shuffle_ps(lhs._data[i], lhs._data[i], 0xaa), rhs._data[2]));
			m._data[i] = _mm_add_ps(m._data[i], _mm_mul_ps(_mm_shuffle_ps(lhs._data[i], lhs._data[i], 0xff), rhs._data[3]));
		}

		return m;
	}
}
