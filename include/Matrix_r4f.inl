namespace ssml
{
	template<uint8_t R>
	Matrix<R, 4, float>::Matrix()
	{
		if constexpr (is_squared)
		{
			_data[0] = _mm_set_ps(0.f, 0.f, 0.f, 1.f);
			_data[1] = _mm_set_ps(0.f, 0.f, 1.f, 0.f);
			_data[2] = _mm_set_ps(0.f, 1.f, 0.f, 0.f);
			_data[3] = _mm_set_ps(1.f, 0.f, 0.f, 0.f);
		}
	}

	template<uint8_t R>
	Matrix<R, 4, float>::Matrix(float data[4 * R])
	{
		for(size_t i = 0; i < R; ++i)
			_data[i] = _mm_set_ps(data[i * 4 + 3], data[i * 4 + 2], data[i * 4 + 1], data[i * 4]);
	}

	template<uint8_t R>
	void Matrix<R, 4, float>::mult(const Matrix<4, 4, float>& matrix, Matrix<R, 4, float>& out)
	{
		for(size_t i = 0; i < R; ++i)
		{
			out._data[i] = _mm_mul_ps(_mm_shuffle_ps(_data[i], _data[i], 0x00), matrix._data[0]);
			out._data[i] = _mm_add_ps(out._data[i], _mm_mul_ps(_mm_shuffle_ps(_data[i], _data[i], 0x55), matrix._data[1]));
			out._data[i] = _mm_add_ps(out._data[i], _mm_mul_ps(_mm_shuffle_ps(_data[i], _data[i], 0xaa), matrix._data[2]));
			out._data[i] = _mm_add_ps(out._data[i], _mm_mul_ps(_mm_shuffle_ps(_data[i], _data[i], 0xff), matrix._data[3]));
		}
	}

	template<uint8_t R>
	Matrix<R, 4, float> Matrix<R, 4, float>::operator*(const Matrix<4, 4, float>& matrix)
	{
		Matrix<R, 4, float> m;
		mult(matrix, m);
		return m;
	}
}
