#include <cstring>

namespace ssml
{
	template<uint8_t R, uint8_t C, class T>
	Matrix<R, C, T>::Matrix()
	{
		if constexpr (is_squared)
		{
			for(size_t i = 0; i < row_size; ++i)
				_data[i][i] = 1.f;
		}
	}

	template<uint8_t R, uint8_t C, class T>
	Matrix<R, C, T>::Matrix(value_type data[row_size * col_size])
	{
		memcpy(_data, data, sizeof(value_type) * row_size * col_size);
	}

	template<uint8_t R, uint8_t C, class T>
	Matrix<R, C, T> Matrix<R, C, T>::scalarMult(const matrix_type& matrix) const
	{
		matrix_type m;
		for(size_t i = 0; i < row_size; ++i)
		{
			for(size_t j = 0; j < col_size; ++j)
				m[i][j] = _data[i][j] * matrix[i][j];
		}
		return m;
	}

	template<uint8_t R, uint8_t C, class T>
	template<uint8_t NC>
	void Matrix<R, C, T>::mult(const Matrix<col_size, NC, value_type>& matrix, Matrix<row_size, NC, value_type>& out) const
	{
		for(size_t i = 0; i < row_size; ++i)
		{
			for(size_t j = 0; j < NC; ++j)
			{
				float d = 0.f; 
				for(size_t k = 0; k < col_size; ++k)
					d += _data[i][k] * matrix[k][j];
				out[i][j] = d;
			}
		}
	}
	
	template<uint8_t R, uint8_t C, class T>
	Matrix<R, C, T> Matrix<R, C, T>::transpose() const
	{
		static_assert(is_squared, "matrix is not squared");

		matrix_type m;
		for(size_t i = 0; i < row_size; ++i)
		{
			for(size_t j = 0; j < col_size; ++j)
				m[j][i] = _data[i][j];
		}
		return m;
	}

	template<uint8_t R, uint8_t C, class T>
	T Matrix<R, C, T>::determinant() const
	{
		static_assert(is_squared, "matrix is not squared");
		
		value_type det { 1.f };
		
		// LU decomposition
		value_type lu[row_size][col_size];
		for(size_t i = 0; i < row_size; ++i)
		{
			for(size_t j = i; j < col_size; ++j)
			{
				value_type sum{};
				for(size_t k = 0; k < i; ++k)
					sum += lu[i][k] * lu[k][j];

				lu[i][j] = _data[i][j] - sum;
			}

			for(size_t j = i + 1; j < col_size; ++j)
			{
				value_type sum{};
				for(size_t k = 0; k < i; ++k)
					sum += lu[j][k] * lu[k][i];

				lu[j][i] = (_data[j][i] - sum) / lu[i][i];
			}

			det *= lu[i][i];
		}
	
		return det;
	}

	template<>
	double Matrix<2, 2, double>::determinant() const
	{
		return _data[0][0] * _data[1][1] - _data[0][1] * _data[1][0];
	}

	template<uint8_t R, uint8_t C, class T>
	Matrix<R, C, T> Matrix<R, C, T>::inverse() const
	{
		static_assert(is_squared, "matrix is not squared");

		value_type det = determinant();
		if(det == 0.f)
			return {};

		matrix_type m;	
		for(size_t i = 0; i < row_size; ++i)
		{
			for(size_t j = 0; j < col_size; ++j)
			{
				Matrix<row_size - 1, col_size - 1, value_type> minor;
				for(size_t k = 0; k < row_size; ++k)
				{
					if(k == i)
						continue;

					for(size_t l = 0; l < col_size; ++l)
					{
						if(l == j)
							continue;

						minor[k > i ? k - 1 : k][l > j ? l - 1 : l] = _data[k][l];
					}
				}

				m[j][i] = (((i+j)%2 == 1) ? minor.determinant() * -1.f : minor.determinant()) / det;
			}	
		}

		return m;
	}

	template<>
	Matrix<2, 2, double> Matrix<2, 2, double>::inverse() const
	{
		value_type det = determinant();
		if(det == 0.f)
			return {};

		value_type inv_det = 1.f / det;

		matrix_type m;
		m[0][0] = inv_det * _data[1][1];
		m[0][1] = inv_det * _data[0][1] * -1.f;
		m[1][0] = inv_det * _data[1][0] * -1.f;
		m[1][1] = inv_det * _data[0][0];

		return m;
	}

	template<uint8_t R, uint8_t C, class T>
	template<uint8_t NC>
	Matrix<R, NC, T> Matrix<R, C, T>::operator*(const Matrix<col_size, NC, value_type>& matrix) const
	{
		Matrix<row_size, NC, value_type> m;
		mult(matrix, m);
		return m;
	}

	template<uint8_t R, uint8_t C, class T>
	T* Matrix<R, C, T>::operator[](const uint8_t i)
	{
		return _data[i];
	}

	template<uint8_t R, uint8_t C, class T>
	const T* Matrix<R, C, T>::operator[](const uint8_t i) const
	{
		return _data[i];
	}

	template<uint8_t R, uint8_t C, class T>
	bool Matrix<R, C, T>::operator==(const matrix_type& matrix) const
	{
		return !((*this) != matrix);
	}

	template<uint8_t R, uint8_t C, class T>
	bool Matrix<R, C, T>::operator!=(const matrix_type& matrix) const
	{
		for(size_t i = 0; i < R; ++i)
		{
			for(size_t j = 0; j < C; ++j)
			{
				if(!almost_equal(_data[i][j], matrix[i][j], 2))
			 		return true;	
			}
		}
		return false;
	}

	template<uint8_t R, uint8_t C, class T>
	std::ostream& operator<<(std::ostream& os, const Matrix<R, C, T>& obj)
	{
		for(size_t i = 0; i < R; ++i)
		{
			for(size_t j = 0; j < C; ++j)
				os << '[' << obj[i * R + j] << ']';
			os << '\n';
		}
		return os;
	}
}
