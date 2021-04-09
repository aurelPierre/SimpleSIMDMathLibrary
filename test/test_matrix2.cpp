#include "Matrix_r2f.h"

#include <gtest/gtest.h>

TEST(Matf2, scalarMult)
{
	float test_data[4] = {
		5.f, 7.f,
		2.f, 3.f
	};

	float result_scalarMult[4] = {
		25.f, 49.f,
		4.f, 9.f
	};
	
	ssml::Matf2 m(test_data);
	ssml::Matf2 ms(result_scalarMult);

	EXPECT_EQ(m.scalarMult(m), ms);
}

TEST(Matf2, transpose)
{
	float test_data[4] = {
		5.f, 7.f,
		2.f, 3.f
	};

	float result_transpose[4] = {
		5.f, 2.f,
		7.f, 3.f
	};
	
	ssml::Matf2 m(test_data);
	ssml::Matf2 mt(result_transpose);

	EXPECT_EQ(m.transpose(), mt);
}

TEST(Matf2, determinant)
{
	float test_data[4] = {
		5.f, 7.f,
		2.f, 3.f
	};

	ssml::Matf2 m(test_data);

	EXPECT_EQ(m.determinant(), 1.f);
}

TEST(Matf2, inverse)
{
	float test_data[4] = {
		5.f, 7.f,
		2.f, 3.f
	};

	float result_inverse[4] = {
		3.f, -7.f,
		-2.f, 5.f
	};

	ssml::Matf2 m(test_data);
	ssml::Matf2 mi(result_inverse);

	EXPECT_EQ(m.inverse(), mi);
}

TEST(Matf2, mult)
{
	float test_data[4] = {
		5.f, 7.f,
		2.f, 3.f
	};

	float result_data[4] = {
		39.f, 56.f, 
		16.f, 23.f,
	};

	ssml::Matf2 m(test_data);
	ssml::Matf2 result(result_data);

	EXPECT_EQ(m * m, result);
}

