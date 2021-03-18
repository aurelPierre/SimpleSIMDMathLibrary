#include <bits/c++config.h>
#include <type_traits>
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
	Matrix<R, C, T> Matrix<R, C, T>::scalarMult(const Matrix<R, C, T>& matrix) const
	{
		Matrix<R, C, T> m;
		for(size_t i = 0; i < R; ++i)
		{
			for(size_t j = 0; j < C; ++j)
				m._data[i][j] = _data[i][j] * matrix._data[i][j];
		}
		return m;
	}

	template<uint8_t R, uint8_t C, class T>
	template<uint8_t NC>
	void Matrix<R, C, T>::mult(const Matrix<C, NC, T>& matrix, Matrix<R, NC, T>& out) const
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
	Matrix<R, C, T> Matrix<R, C, T>::transpose() const
	{
		Matrix<R, C, T> m;
		for(size_t i = 0; i < R; ++i)
		{
			for(size_t j = 0; j < C; ++j)
				m._data[j][i] = _data[i][j];
		}
		return m;
	}

	template<uint8_t R, uint8_t C, class T>
	T Matrix<R, C, T>::determinant() const
	{
		static_assert(is_squared, "matrix is not squared");
		
		T det{};
		for(size_t i = 0; i < C; ++i)
		{
			Matrix<R - 1, C - 1, T> m;
			for(size_t j = 1; j < R; ++j)
			{
				for(size_t k = 0; k < C; ++k)
				{
					if(k == i)
						continue;

					m._data[j - 1][k > i ? k - 1 : k] = _data[j][k];
				}
			}

			if(i%2 == 0)
				det += _data[0][i] * m.determinant();
			else
				det -= _data[0][i] * m.determinant();
		}
		return det;
	}

	template<>
	float Matrix<2, 2, float>::determinant() const
	{
		return _data[0][0] * _data[1][1] - _data[0][1] * _data[1][0];
	}

	template<>
	double Matrix<2, 2, double>::determinant() const
	{
		return _data[0][0] * _data[1][1] - _data[0][1] * _data[1][0];
	}

	template<uint8_t R, uint8_t C, class T>
	Matrix<R, C, T> Matrix<R, C, T>::inverse() const
	{
		T det = determinant();
		if(det == 0.f)
			return {};

		Matrix<R, C, T> m;	
		for(size_t i = 0; i < R; ++i)
		{
			for(size_t j = 0; j < C; ++j)
			{
				Matrix<R - 1, C - 1, T> minor;
				for(size_t k = 0; k < R; ++k)
				{
					if(k == i)
						continue;

					for(size_t l = 0; l < C; ++l)
					{
						if(l == j)
							continue;

						minor._data[k > i ? k - 1 : k][l > j ? l - 1 : l] = _data[k][l];
					}
				}

				m._data[j][i] = (((i+j)%2 == 1) ? minor.determinant() * -1.f : minor.determinant()) / det;
			}	
		}

		return m;
	}

	template<>
	Matrix<2, 2, float> Matrix<2, 2, float>::inverse() const
	{
		float det = determinant();
		if(det == 0.f)
			return {};

		float inv_det = 1.f / det;

		Matrix<2, 2, float> m;
		m._data[0][0] = inv_det * _data[1][1];
		m._data[0][1] = inv_det * _data[0][1] * -1.f;
		m._data[1][0] = inv_det * _data[1][0] * -1.f;
		m._data[1][1] = inv_det * _data[0][0];
		
		return m;
	}

	template<>
	Matrix<2, 2, double> Matrix<2, 2, double>::inverse() const
	{
		double det = determinant();
		if(det == 0.f)
			return {};

		double inv_det = 1.f / det;

		Matrix<2, 2, double> m;
		m._data[0][0] = inv_det * _data[1][1];
		m._data[0][1] = inv_det * _data[0][1] * -1.f;
		m._data[1][0] = inv_det * _data[1][0] * -1.f;
		m._data[1][1] = inv_det * _data[0][0];

		return m;
	}

	template<uint8_t R, uint8_t C, class T>
	template<uint8_t NC>
	Matrix<R, NC, T> Matrix<R, C, T>::operator*(const Matrix<C, NC, T>& matrix) const
	{
		Matrix m;
		mult(matrix, m);
		return m;
	}

	template<uint8_t R, uint8_t C, class T>
	bool Matrix<R, C, T>::operator==(const Matrix<R, C, T>& matrix) const
	{
		return !((*this) != matrix);
	}

	template<uint8_t R, uint8_t C, class T>
	bool Matrix<R, C, T>::operator!=(const Matrix<R, C, T>& matrix) const
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

	template<uint8_t R, uint8_t C, class T>
	std::ostream& operator<<(std::ostream& os, const Matrix<R, C, T>& obj)
	{
		for(size_t i = 0; i < R; ++i)
		{
			for(size_t j = 0; j < C; ++j)
				os << '[' << obj._data[i][j] << ']';
			os << '\n';
		}
		return os;
	}
}
