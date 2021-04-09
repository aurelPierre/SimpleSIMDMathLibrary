#include "Matrix.h"
#include "Matrix_r3f.h"

#include <gtest/gtest.h>

TEST(Matf3, scalarMult)
{
	float test_data[9] = {
		5.f, 7.f, 9.f,
		2.f, 3.f, 3.f,
		8.f, 10.f, 2.f
	};

	float result_scalarMult[9] = {
		25.f, 49.f, 81.f,
		4.f, 9.f, 9.f,
		64.f, 100.f, 4.f
	};
	
	ssml::Matf3 m(test_data);
	ssml::Matf3 ms(result_scalarMult);

	EXPECT_EQ(m.scalarMult(m), ms);
}

TEST(Matf3, transpose)
{
	float test_data[9] = {
		5.f, 7.f, 9.f,
		2.f, 3.f, 3.f,
		8.f, 10.f, 2.f
	};

	float result_transpose[9] = {
		5.f, 2.f, 8.f,
		7.f, 3.f, 10.f,
		9.f, 3.f, 2.f
	};
	
	ssml::Matf3 m(test_data);
	ssml::Matf3 mt(result_transpose);

	EXPECT_EQ(m.transpose(), mt);
}

TEST(Matf3, determinant)
{
	float test_data[9] = {
		5.f, 7.f, 9.f,
		2.f, 3.f, 3.f,
		8.f, 10.f, 2.f
	};

	ssml::Matf3 m(test_data);

	EXPECT_EQ(m.determinant(), -16.f);
}

TEST(Matf3, inverse)
{
	float test_data[9] = {
		5.f, 7.f, 9.f,
		2.f, 3.f, 3.f,
		8.f, 10.f, 2.f
	};

	float result_inverse[9] = {
		24.f / 16.f, -76.f / 16.f, 6.f / 16.f,
		-20.f / 16.f, 62.f / 16.f, -3.f / 16.f,
		4.f / 16.f, -6.f / 16.f, -1.f / 16.f
	};

	ssml::Matf3 m(test_data);
	ssml::Matf3 mi(result_inverse);

	EXPECT_EQ(m.inverse(), mi);
}

TEST(Matf3, mult)
{
	float test_data[9] = {
		5.f, 7.f, 9.f,
		2.f, 3.f, 3.f,
		8.f, 10.f, 2.f
	};

	float result_data[9] = {
		111.f, 146.f, 84.f, 
		40.f, 53.f, 33.f,
		76.f, 106.f, 106.f
	};

	ssml::Matf3 m(test_data);
	ssml::Matf3 result(result_data);

	EXPECT_EQ(m * m, result);
}

