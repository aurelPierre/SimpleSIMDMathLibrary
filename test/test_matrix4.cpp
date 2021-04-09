#include "Matrix_r4f.h"

#include <gtest/gtest.h>

TEST(Matf4, scalarMult)
{
	float test_data[16] = {	
			5.f, 7.f, 9.f, 10.f,
	 		2.f, 3.f, 3.f, 8.f,
			8.f, 10.f, 2.f, 3.f,
			3.f, 3.f, 4.f, 8.f
 	};

	float result_scalarMult[16] = {
		25.f, 49.f, 81.f, 100.f,
		4.f, 9.f, 9.f, 64.f,
		64.f, 100.f, 4.f, 9.f,
		9.f, 9.f, 16.f, 64.f
	};
	
	ssml::Matf4 m(test_data);
	ssml::Matf4 ms(result_scalarMult);

	EXPECT_EQ(m.scalarMult(m), ms);
}

TEST(Matf4, transpose)
{
	float test_data[16] = {	
			5.f, 7.f, 9.f, 10.f,
	 		2.f, 3.f, 3.f, 8.f,
			8.f, 10.f, 2.f, 3.f,
			3.f, 3.f, 4.f, 8.f
 	};

	float result_transpose[16] = {
		5.f, 2.f, 8.f, 3.f,
		7.f, 3.f, 10.f, 3.f,
		9.f, 3.f, 2.f, 4.f,
		10.f, 8.f, 3.f, 8.f
	};
	
	ssml::Matf4 m(test_data);
	ssml::Matf4 mt(result_transpose);

	EXPECT_EQ(m.transpose(), mt);
}

TEST(Matf4, determinant)
{
	float test_data[16] = {	
			5.f, 7.f, 9.f, 10.f,
	 		2.f, 3.f, 3.f, 8.f,
			8.f, 10.f, 2.f, 3.f,
			3.f, 3.f, 4.f, 8.f
 	};

	ssml::Matf4 m(test_data);

	EXPECT_EQ(m.determinant(), -361.f);
}

TEST(Matf4, inverse)
{
	float test_data[16] = {	
			5.f, 7.f, 9.f, 10.f,
	 		2.f, 3.f, 3.f, 8.f,
			8.f, 10.f, 2.f, 3.f,
			3.f, 3.f, 4.f, 8.f
 	};

	float result_inverse[16] = {
		-71.f / 361.f, -271.f / 361.f, 26.f / 361.f, 350.f / 361.f,
		51.f / 361.f, 215.f / 361.f, 22.f / 361.f, -287.f / 361.f,
		71.f / 361.f, -90.f / 361.f, -26.f / 361.f, 11.f / 361.f,
		-28.f / 361.f, 66.f / 361.f, -5.f / 361.f, 16.f / 361.f
	};

	ssml::Matf4 m(test_data);
	ssml::Matf4 mi(result_inverse);

	EXPECT_EQ(m.inverse(), mi);
}

TEST(Matf4, mult)
{
	float test_data[16] = {	
			5.f, 7.f, 9.f, 10.f,
	 		2.f, 3.f, 3.f, 8.f,
			8.f, 10.f, 2.f, 3.f,
			3.f, 3.f, 4.f, 8.f
 	};

	float result_data[16] = {
		141.f, 176.f, 124.f, 213.f,
		64.f, 77.f, 65.f, 117.f,
		85.f, 115.f, 118.f, 190.f,
		77.f, 94.f, 76.f, 130.f
	};

	ssml::Matf4 m(test_data);
	ssml::Matf4 result(result_data);

	EXPECT_EQ(m * m, result);
}

