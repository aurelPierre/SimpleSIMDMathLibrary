#include "glm/matrix.hpp"
#include <cstdlib>
#include <vector>

#include <gtest/gtest.h>

#include <Matrix_r3f.h>
#include <glm/mat3x3.hpp>

class T_Matf3 : public testing::Test
{
	std::vector<float> create_data_random()
	{
		std::srand(std::time(nullptr));
	
		std::vector<float> test_data(9);
		for(size_t i = 0; i < 9; ++i)
			test_data[i] = std::rand() % 1000;
		
		return test_data;
	}

	ssml::Matf3 create_ssml_from(std::vector<float>& data)
	{
		ssml::Matf3 m(data.data());
		return m;
	}

	glm::mat3 create_glm_from(std::vector<float>& data)
	{
		glm::mat3 m;
		for(size_t i = 0; i < 3; ++i)
			for(size_t j = 0; j < 3; ++j)
				m[i][j] = data[i * 3 + j];

		return m;
	}

protected:

	const uint8_t NB_ITERATION_RANDOM = 5;

	ssml::Matf3 _sm;
	glm::mat3 	_gm;

	ssml::Matf3 _rsm;
	glm::mat3 	_rgm;

	T_Matf3()
	{
		std::vector<float> test_data {
			5.f, 7.f, 9.f,
			2.f, 3.f, 3.f,
			8.f, 10.f, 2.f
		};
		
		_sm = create_ssml_from(test_data);
		_gm = create_glm_from(test_data);

		generate_random_matrix();
	}

	void generate_random_matrix()
	{
		std::vector<float> data = create_data_random();

		_rsm = create_ssml_from(data);
		_rgm = create_glm_from(data);
	}
};

namespace ssml
{
	bool operator==(const ssml::Matf3& lhs, const glm::mat3& rhs)
	{
		for(size_t i = 0; i < 3; ++i)
			for(size_t j = 0; j < 3; ++j)
				if(!almost_equal(lhs[i][j], rhs[i][j], 4))
					return false;
		return true;
	}
}

namespace glm
{
	std::ostream& operator<<(std::ostream& os, const glm::mat3& obj)
	{
		for(size_t i = 0; i < 3; ++i)
		{
			for(size_t j = 0; j < 3; ++j)
				os << '[' << obj[i][j] << ']';
			os << '\n';
		}
		return os;
	}
}

TEST_F(T_Matf3, scalarMult)
{
	EXPECT_EQ(ssml::scalarMult(_sm, _sm), glm::matrixCompMult(_gm, _gm));
	for(size_t i = 0; i < NB_ITERATION_RANDOM; ++i)
	{
		generate_random_matrix();
		EXPECT_EQ(ssml::scalarMult(_rsm, _rsm), glm::matrixCompMult(_rgm, _rgm));
	}
}

TEST_F(T_Matf3, transpose)
{
	EXPECT_EQ(ssml::transpose(_sm), glm::transpose(_gm));
	for(size_t i = 0; i < NB_ITERATION_RANDOM; ++i)
	{
		generate_random_matrix();
		EXPECT_EQ(ssml::transpose(_rsm), glm::transpose(_rgm));
	}
}

TEST_F(T_Matf3, determinant)
{
	EXPECT_FLOAT_EQ(ssml::determinant(_sm), glm::determinant(_gm));
	for(size_t i = 0; i < NB_ITERATION_RANDOM; ++i)
	{
		generate_random_matrix();
		EXPECT_FLOAT_EQ(ssml::determinant(_rsm), glm::determinant(_rgm));
	}
}

TEST_F(T_Matf3, inverse)
{
	EXPECT_EQ(ssml::inverse(_sm), glm::inverse(_gm));
	for(size_t i = 0; i < NB_ITERATION_RANDOM; ++i)
	{
		generate_random_matrix();
		EXPECT_EQ(ssml::inverse(_rsm), glm::inverse(_rgm));
	}
}

TEST_F(T_Matf3, mult)
{
	EXPECT_EQ(_sm * _sm, _gm * _gm);
	for(size_t i = 0; i < NB_ITERATION_RANDOM; ++i)
	{
		generate_random_matrix();
		EXPECT_EQ(_rsm * _rsm, _rgm * _rgm);
	}
}

