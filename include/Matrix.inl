namespace ssml
{
	template<uint8_t R, uint8_t C, class T>
	Matrix<R, C, T>::Matrix()
	{
		if constexpr (is_squared)
		{
			for(size_t i = 0; i < R ; ++i)
				_data[i][i] = 1.f;
		}
	}

	template<uint8_t R, uint8_t C, class T>
	Matrix<R, C, T>::Matrix(float data[R*C])
	{
		for(size_t i = 0; i < R; ++i)
			for(size_t j = 0; j < C; ++j)
				_data[i][j] = data[i * R + j];
	}

	template<uint8_t R, uint8_t C, class T>
	template<uint8_t NC>
	void Matrix<R, C, T>::mult(const Matrix<C, NC, T>& matrix, Matrix<R, NC, T>& out)
	{
		for(size_t i = 0; i < R; ++i)
		{
			for(size_t j = 0; j < NC; ++j)
			{
				float d = 0.f; 
				for(size_t k = 0; k < C; ++k)
					d += _data[i][k] * matrix._data[k][j];
				out._data[i][j] = d;
			}
		}
	}

	template<uint8_t R, uint8_t C, class T>
	template<uint8_t NC>
	Matrix<R, NC, T> Matrix<R, C, T>::operator*(const Matrix<C, NC, T>& matrix)
	{
		Matrix m;
		mult(matrix, m);
		return m;
	}

	template<uint8_t R, uint8_t C, class T>
	bool Matrix<R, C, T>::operator==(const Matrix<R, C, T>& matrix)
	{
		return !((*this) != matrix);
	}

	template<uint8_t R, uint8_t C, class T>
	bool Matrix<R, C, T>::operator!=(const Matrix<R, C, T>& matrix)
	{
		for(size_t i = 0; i < R; ++i)
		{
			for(size_t j = 0; j < C; ++j)
			{
				if(_data[i][j] != matrix._data[i][j])
			 		return true;	
			}
		}
		return false;
	}
}
