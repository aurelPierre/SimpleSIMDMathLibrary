#include <limits>
#include <vector>
#include <cstdlib>

#include <Matrix_r4f.h>
#include <glm/mat4x4.hpp>

#include <gtest/gtest.h>

class T_Matf4 : public testing::Test
{
	std::vector<float> create_data_random()
	{
		std::srand(std::time(nullptr));
	
		std::vector<float> test_data(16);
		for(size_t i = 0; i < 16; ++i)
			test_data[i] = std::rand() % 1000;
		
		return test_data;
	}

	ssml::Matf4 create_ssml_from(std::vector<float>& data)
	{
		ssml::Matf4 m(data.data());
		return m;
	}

	glm::mat4 create_glm_from(std::vector<float>& data)
	{
		glm::mat4 m;
		for(size_t i = 0; i < 4; ++i)
			for(size_t j = 0; j < 4; ++j)
				m[i][j] = data[i * 4 + j];

		return m;
	}

protected:

	const uint8_t NB_ITERATION_RANDOM = 5;

	ssml::Matf4 _sm;
	glm::mat4 	_gm;

	ssml::Matf4 _rsm;
	glm::mat4 	_rgm;

	T_Matf4()
	{
		std::vector<float> test_data {
			5.f, 7.f, 9.f, 10.f,
	 		2.f, 3.f, 3.f, 8.f,
			8.f, 10.f, 2.f, 3.f,
			3.f, 3.f, 4.f, 8.f
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
	bool operator==(const ssml::Matf4& lhs, const glm::mat4& rhs)
	{
		for(size_t i = 0; i < 4; ++i)
			for(size_t j = 0; j < 4; ++j)
				if(!almost_equal(lhs[i][j], rhs[i][j], 4))
					return false;
		return true;
	}
}

namespace glm
{
	std::ostream& operator<<(std::ostream& os, const glm::mat4& obj)
	{
		for(size_t i = 0; i < 4; ++i)
		{
			for(size_t j = 0; j < 4; ++j)
				os << '[' << obj[i][j] << ']';
			os << '\n';
		}
		return os;
	}
}

TEST_F(T_Matf4, scalarMult)
{
	EXPECT_EQ(ssml::scalarMult(_sm, _sm), glm::matrixCompMult(_gm, _gm));
	for(size_t i = 0; i < NB_ITERATION_RANDOM; ++i)
	{
		generate_random_matrix();
		EXPECT_EQ(ssml::scalarMult(_rsm, _rsm), glm::matrixCompMult(_rgm, _rgm));
	}
}

TEST_F(T_Matf4, transpose)
{
	EXPECT_EQ(ssml::transpose(_sm), glm::transpose(_gm));
	for(size_t i = 0; i < NB_ITERATION_RANDOM; ++i)
	{
		generate_random_matrix();
		EXPECT_EQ(ssml::transpose(_rsm), glm::transpose(_rgm));
	}
}

TEST_F(T_Matf4, determinant)
{
	EXPECT_FLOAT_EQ(ssml::determinant(_sm), glm::determinant(_gm));
	for(size_t i = 0; i < NB_ITERATION_RANDOM; ++i)
	{
		generate_random_matrix();
		EXPECT_FLOAT_EQ(ssml::determinant(_rsm), glm::determinant(_rgm));
	}
}

TEST_F(T_Matf4, inverse)
{
	EXPECT_EQ(ssml::inverse(_sm), glm::inverse(_gm));
	for(size_t i = 0; i < NB_ITERATION_RANDOM; ++i)
	{
		generate_random_matrix();
		EXPECT_EQ(ssml::inverse(_rsm), glm::inverse(_rgm)) << "data: " << _rsm;
	}
}

TEST_F(T_Matf4, mult)
{
	EXPECT_EQ(_sm * _sm, _gm * _gm);
	for(size_t i = 0; i < NB_ITERATION_RANDOM; ++i)
	{
		generate_random_matrix();
		EXPECT_EQ(_rsm * _rsm, _rgm * _rgm);
	}
}

