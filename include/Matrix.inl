#include <cstring>

namespace ssml
{
	template<matrix_size_type R, matrix_size_type C, class T>
	Matrix<R, C, T>::Matrix() : _data {}
	{
		if constexpr (is_squared)
		{
			for(matrix_size_type i = 0; i < R; ++i)
				_data[i][i] = 1.f;
		}
	}

	template<matrix_size_type R, matrix_size_type C, class T>
	Matrix<R, C, T>::Matrix(value_type data[R * C])
	{
		memcpy(_data, data, sizeof(value_type) * R * C);
	}

	template<matrix_size_type R, matrix_size_type C, class T>
	typename Matrix<R, C, T>::row_type& Matrix<R, C, T>::operator[](const matrix_size_type i)
	{
		return _data[i];
	}

	template<matrix_size_type R, matrix_size_type C, class T>
	const typename Matrix<R, C, T>::row_type&  Matrix<R, C, T>::operator[](const matrix_size_type i) const
	{
		return _data[i];
	}

	template<uint8_t R, uint8_t C, class T>
	Matrix<R, C, T> scalarMult(const Matrix<R, C, T>& lhs, const Matrix<R, C, T>& rhs)
	{
		Matrix<R, C, T> m;
		for(matrix_size_type i = 0; i < R; ++i)
		{
			for(matrix_size_type j = 0; j < C; ++j)
				m[i][j] = lhs[i][j] * rhs[i][j];
		}
		return m;
	}
	
	template<matrix_size_type R, class T>
	Matrix<R, R, T> transpose(const Matrix<R, R, T>& obj)
	{
		Matrix<R, R, T> m;
		for(matrix_size_type i = 0; i < R; ++i)
		{
			for(matrix_size_type j = 0; j < R; ++j)
				m[j][i] = obj[i][j];
		}
		return m;
	}

	template<matrix_size_type R, class T>
	T determinant(const Matrix<R, R, T>& obj)
	{
		T det { 1.f };
		
		// LU decomposition
		T lu[R][R];
		for(matrix_size_type i = 0; i < R; ++i)
		{
			for(matrix_size_type j = i; j < R; ++j)
			{
				T sum{};
				for(matrix_size_type k = 0; k < i; ++k)
					sum += lu[i][k] * lu[k][j];

				lu[i][j] = obj[i][j] - sum;
			}

			for(matrix_size_type j = i + 1; j < R; ++j)
			{
				T sum{};
				for(matrix_size_type k = 0; k < i; ++k)
					sum += lu[j][k] * lu[k][i];

				lu[j][i] = (obj[j][i] - sum) / lu[i][i];
			}

			det *= lu[i][i];
		}
	
		return det;
	}

	template<>
	double determinant(const Matrix<2, 2, double>& obj)
	{
		return obj[0][0] * obj[1][1] - obj[0][1] * obj[1][0];
	}

	template<matrix_size_type R, class T>
	Matrix<R, R, T> inverse(const Matrix<R, R, T>& obj)
	{
		T det = determinant(obj);
		if(det == 0.f)
			return {};

		Matrix<R, R, T> m;	
		for(matrix_size_type i = 0; i < R; ++i)
		{
			for(matrix_size_type j = 0; j < R; ++j)
			{
				Matrix<R - 1, R - 1, T> minor;
				for(matrix_size_type k = 0; k < R; ++k)
				{
					if(k == i)
						continue;

					for(matrix_size_type l = 0; l < R; ++l)
					{
						if(l == j)
							continue;

						minor[k > i ? k - 1 : k][l > j ? l - 1 : l] = obj[k][l];
					}
				}

				m[j][i] = (((i+j)%2 == 1) ? minor.determinant() * -1.f : minor.determinant()) / det;
			}	
		}

		return m;
	}

	template<>
	Matrix<2, 2, double> inverse(const Matrix<2, 2, double>& obj)
	{
		double det = determinant(obj);
		if(det == 0.f)
			return {};

		double inv_det = 1.f / det;

		Matrix<2, 2, double> m;
		m[0][0] = inv_det * obj[1][1];
		m[0][1] = inv_det * obj[0][1] * -1.f;
		m[1][0] = inv_det * obj[1][0] * -1.f;
		m[1][1] = inv_det * obj[0][0];

		return m;
	}


	template<matrix_size_type R, matrix_size_type C, class T, matrix_size_type NC>
	Matrix<R, NC, T> operator*(const Matrix<R, C, T>& lhs, const Matrix<C, NC, T>& rhs)
	{
		Matrix<R, NC, T> m;

		for(matrix_size_type i = 0; i < R; ++i)
		{
			for(matrix_size_type j = 0; j < NC; ++j)
			{
				T d = 0.f; 
				for(matrix_size_type k = 0; k < C; ++k)
					d += lhs[i][k] * rhs[k][j];
				m[i][j] = d;
			}
		}

		return m;
	}

	template<matrix_size_type R, matrix_size_type C, class T>
	bool operator==(const Matrix<R, C, T>& lhs, const Matrix<R, C, T>& rhs)
	{
		return !(lhs != rhs);
	}

	template<matrix_size_type R, matrix_size_type C, class T>
	bool operator!=(const Matrix<R, C, T>& lhs, const Matrix<R, C, T>& rhs)
	{
		for(matrix_size_type i = 0; i < R; ++i)
		{
			for(matrix_size_type j = 0; j < C; ++j)
			{
				if(!almost_equal(lhs[i][j], rhs[i][j], 2))
			 		return true;	
			}
		}
		return false;
	}

	template<matrix_size_type R, matrix_size_type C, class T>
	std::ostream& operator<<(std::ostream& os, const Matrix<R, C, T>& obj)
	{
		for(size_t i = 0; i < R; ++i)
		{
			for(size_t j = 0; j < C; ++j)
				os << '[' << obj[i][j] << ']';
			os << '\n';
		}
		return os;
	}
}
