#include "Matrix.h"

#include "Logger.h"
#include "Profiler.h"

void log_result(const std::string& name, bool predicate)
{
	LOG(tlbx::INFO, (predicate ? "\033[1;34m[x]\033[0m " : "\033[1;31m[]\033[0m ") + name)
}

void test_mat2()
{
	float test_data2[4] = {
		5.f, 7.f,
		2.f, 3.f
	};

	{
		float result_scalarMult[4] = {
			25.f, 49.f,
			4.f, 9.f
		};

		ssml::Matf2 m(test_data2);
		ssml::Matf2 ms(result_scalarMult);

		ssml::Matf2 result = m.scalarMult(m);
		log_result("scalarMult", result == ms);
	}

	{
		float result_transpose[4] = {
			5.f, 2.f,
			7.f, 3.f
		};

		ssml::Matf2 m(test_data2);
		ssml::Matf2 mt(result_transpose);

		ssml::Matf2 result = m.transpose();
		log_result("transpose", result == mt);
	}
	
	{
		ssml::Matf2 m(test_data2);
		float det = m.determinant();

		log_result("determinant", almost_equal(det, 1.f, 2));
	}

	{
		float result_inverse[4] = {
			3.f, -7.f,
			-2.f, 5.f
		};

		ssml::Matf2 m(test_data2);
		ssml::Matf2 mi(result_inverse);

		ssml::Matf2 result = m.inverse();
		log_result("inverse", result == mi);
	}

	{
		ssml::Matf2 m(test_data2);
		ssml::Matf2 r = m * m;

		float result_data[4] = {
			39.f, 56.f, 
			16.f, 23.f,
		};

		ssml::Matf2 result(result_data);
		log_result("operator*", result == r);	
	}
}

void test_mat3()
{
	float test_data3[9] = {
		5.f, 7.f, 9.f,
		2.f, 3.f, 3.f,
		8.f, 10.f, 2.f
	};

	{
		float result_scalarMult[9] = {
			25.f, 49.f, 81.f,
			4.f, 9.f, 9.f,
			64.f, 100.f, 4.f
		};

		ssml::Matf3 m(test_data3);
		ssml::Matf3 ms(result_scalarMult);

		ssml::Matf3 result = m.scalarMult(m);
		log_result("scalarMult", result == ms);
	}

	{
		float result_transpose[9] = {
			5.f, 2.f, 8.f,
			7.f, 3.f, 10.f,
			9.f, 3.f, 2.f
		};

		ssml::Matf3 m(test_data3);
		ssml::Matf3 mt(result_transpose);

		ssml::Matf3 result = m.transpose();
		log_result("transpose", result == mt);
	}
	
	{
		ssml::Matf3 m(test_data3);
		float det = m.determinant();

		log_result("determinant", almost_equal(det, -16.f, 2));
	}

	{
		float result_inverse[9] = {
			24.f / 16.f, -76.f / 16.f, 6.f / 16.f,
			-20.f / 16.f, 62.f / 16.f, -3.f / 16.f,
			4.f / 16.f, -6.f / 16.f, -1.f / 16.f
		};

		ssml::Matf3 m(test_data3);
		ssml::Matf3 mi(result_inverse);

		ssml::Matf3 result = m.inverse();
		log_result("inverse", result == mi);
	}

	{
		ssml::Matf3 m(test_data3);
		ssml::Matf3 r = m * m;

		float result_data[9] = {
			111.f, 146.f, 84.f, 
			40.f, 53.f, 33.f,
			76.f, 106.f, 106.f
		};

		ssml::Matf3 result(result_data);
		log_result("operator*", result == r);	
	}
}

void test_mat4()
{
	float test_data4[16] = {	
			5.f, 7.f, 9.f, 10.f,
	 		2.f, 3.f, 3.f, 8.f,
			8.f, 10.f, 2.f, 3.f,
			3.f, 3.f, 4.f, 8.f
 	};

	{
		float result_scalarMult[16] = {
			25.f, 49.f, 81.f, 100.f,
			4.f, 9.f, 9.f, 64.f,
			64.f, 100.f, 4.f, 9.f,
			9.f, 9.f, 16.f, 64.f
		};

		ssml::Matf4 m(test_data4);
		ssml::Matf4 ms(result_scalarMult);

		ssml::Matf4 result = m.scalarMult(m);
		log_result("scalarMult", result == ms);
	}

	{
		ssml::Matf4 m(test_data4);
		ssml::Matf4 r = m.transpose();

		float result_data[16] = {
			5.f, 2.f, 8.f, 3.f,
			7.f, 3.f, 10.f, 3.f,
			9.f, 3.f, 2.f, 4.f,
			10.f, 8.f, 3.f, 8.f
		};

		ssml::Matf4 result(result_data);
		log_result("transpose", result == r);
	}

	{
		ssml::Matf4 m(test_data4);
		float det = m.determinant();

		log_result("determinant", almost_equal(det, -361.f, 2));
	}

	{
		ssml::Matf4 m(test_data4);
		ssml::Matf4 r = m.inverse();

		float result_data[16] = {
			-71.f / 361.f, -271.f / 361.f, 26.f / 361.f, 350.f / 361.f,
			51.f / 361.f, 215.f / 361.f, 22.f / 361.f, -287.f / 361.f,
			71.f / 361.f, -90.f / 361.f, -26.f / 361.f, 11.f / 361.f,
			-28.f / 361.f, 66.f / 361.f, -5.f / 361.f, 16.f / 361.f
		};

		ssml::Matf4 result(result_data);

		log_result("inverse", result == r);
	}

	{
		ssml::Matf4 m(test_data4);
		ssml::Matf4 r = m * m;

		float result_data[16] = {
			141.f, 176.f, 124.f, 213.f,
			64.f, 77.f, 65.f, 117.f,
			85.f, 115.f, 118.f, 190.f,
			77.f, 94.f, 76.f, 130.f
		};

		ssml::Matf4 result(result_data);
	
		log_result("operator*", result == r);	
	}
}

int main(int argc, char** argv)
{
	tlbx::Channel::Add<tlbx::StdChannel>();
	tlbx::Channel::Add<tlbx::FileChannel>();

	LOG(tlbx::INFO, "Starting unit test Matf2...")
	LOG(tlbx::INFO, "-----------------------------")
	test_mat2();

	LOG(tlbx::INFO, "")
	LOG(tlbx::INFO, "Starting unit test Matf3...")
	LOG(tlbx::INFO, "-----------------------------")
	test_mat3();

	LOG(tlbx::INFO, "")
	LOG(tlbx::INFO, "Starting unit test Matf4...")
	LOG(tlbx::INFO, "-----------------------------")
	test_mat4();

	return 0;
}
