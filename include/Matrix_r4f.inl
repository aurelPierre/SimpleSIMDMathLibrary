#include <xmmintrin.h>
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
	Matrix<R, 4, float> Matrix<R, 4, float>::scalarMult(const Matrix<R, 4, float>& matrix) const
	{
		Matrix<R, 4, float> m;
		for(size_t i = 0; i < R; ++i)
			m._data[i] = _mm_mul_ps(_data[i], matrix._data[i]);
		return m;
	}

	template<uint8_t R>
	void Matrix<R, 4, float>::mult(const Matrix<4, 4, float>& matrix, Matrix<R, 4, float>& out) const
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
	Matrix<R, 4, float> Matrix<R, 4, float>::transpose() const
	{
		static_assert(is_squared, "matrix is not squared");
	
		__m128 r0 = _mm_unpacklo_ps(_data[0], _data[1]);
		__m128 r1 = _mm_unpackhi_ps(_data[0], _data[1]);

		__m128 r2 = _mm_unpacklo_ps(_data[2], _data[3]);
		__m128 r3 = _mm_unpackhi_ps(_data[2], _data[3]);

		Matrix<R, 4, float> m;

		m._data[0] = _mm_movelh_ps(r0, r2);
		m._data[1] = _mm_movehl_ps(r2, r0);

		m._data[2] = _mm_movelh_ps(r1, r3);
		m._data[3] = _mm_movehl_ps(r3, r1);

		return m;
	}

	template<uint8_t R>
	float Matrix<R, 4, float>::determinant() const
	{
		static_assert(is_squared, "matrix is not squared");
	}

	template<uint8_t R>
	Matrix<R, 4, float> Matrix<R, 4, float>::inverse() const
	{
		static_assert(is_squared, "matrix is not squared");
	}

	template<uint8_t R>
	Matrix<R, 4, float> Matrix<R, 4, float>::operator*(const Matrix<4, 4, float>& matrix) const
	{
		Matrix<R, 4, float> m;
		mult(matrix, m);
		return m;
	}

	template<uint8_t R>
	bool Matrix<R, 4, float>::operator==(const Matrix<R, 4, float>& matrix)	const
	{
		return !((*this) != matrix);
	}

	template<uint8_t R>
	bool Matrix<R, 4, float>::operator!=(const Matrix<R, 4, float>& matrix) const
	{
		for(size_t i = 0; i < R; ++i)
		{
			for(size_t j = 0; j < 4; ++j)
			{
				if(_data[i][j] != matrix._data[i][j])
					return true;
			}
		}
		return false;
	}
}
