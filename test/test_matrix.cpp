#include "Matrix.h"
#include "Matrix_r4f.h"

#include "Logger.h"
#include "Profiler.h"

int main(int argc, char** argv)
{
	tlbx::Channel::Add<tlbx::StdChannel>();
	tlbx::Channel::Add<tlbx::FileChannel>();

	float test_data3[9] = {
		5.f, 7.f, 9.f,
		2.f, 3.f, 3.f,
		8.f, 10.f, 2.f
	};

	float test_data4[16] = {	
			5.f, 7.f, 9.f, 10.f,
	 		2.f, 3.f, 3.f, 8.f,
			8.f, 10.f, 2.f, 3.f,
			3.f, 3.f, 4.f, 8.f
 	};

	{
		LOG(tlbx::INFO, "Starting unit test Matf4x4::operator*...")

		ssml::Matf4 m(test_data4);
		ssml::Matf4 r = m * m;

		float result_data[16] = {
			141.f, 176.f, 124.f, 213.f,
			64.f, 77.f, 65.f, 117.f,
			85.f, 115.f, 118.f, 190.f,
			77.f, 94.f, 76.f, 130.f
		};

		ssml::Matf4 result(result_data);
		
		ASSERT((result == r), "Matf4x4::operator* is incorrect")
		LOG(tlbx::INFO, "Unit test Matf4x4::operator* is done.")
	}

	{
		LOG(tlbx::INFO, "Starting unit test Matf4x4::transpose...")

		ssml::Matf4 m(test_data4);
		ssml::Matf4 r = m.transpose();

		float result_data[16] = {
			5.f, 2.f, 8.f, 3.f,
			7.f, 3.f, 10.f, 3.f,
			9.f, 3.f, 2.f, 4.f,
			10.f, 8.f, 3.f, 8.f
		};

		ssml::Matf4 result(result_data);

		ASSERT((result == r), "Matf4x4::transpose is incorrect")
		LOG(tlbx::INFO, "Unit test Matf4x4::transpose is done.")
	}

	{
		LOG(tlbx::INFO, "Starting unit test Matf4x4::determinant...")

		ssml::Matf4 m(test_data4);
		float det = m.determinant();

		ASSERT(almost_equal(det, -361.f, 2), "Matf4x4::determinant is incorrect")
		LOG(tlbx::INFO, "Unit test Matf4x4::determinant is done.")
	}

	{
		LOG(tlbx::INFO, "Starting unit test Matf4x4::inverse...")

		ssml::Matf4 m(test_data4);
		ssml::Matf4 r = m.inverse();

		float result_data[16] = {
			-71.f / 361.f, -271.f / 361.f, 26.f / 361.f, 350.f / 361.f,
			51.f / 361.f, 215.f / 361.f, 22.f / 361.f, -287.f / 361.f,
			71.f / 361.f, -90.f / 361.f, -26.f / 361.f, 11.f / 361.f,
			-28.f / 361.f, 66.f / 361.f, -5.f / 361.f, 16.f / 361.f
		};

		ssml::Matf4 result(result_data);

		ASSERT((result == r), "Matf4x4::inverse is incorrect")
		LOG(tlbx::INFO, "Unit test Matf4x4::inverse is done.")
	}

	{
		LOG(tlbx::INFO, "Starting unit test Matf3x3::determinant...")

		ssml::Matf3 m(test_data3);
		float det = m.determinant();

		ASSERT(almost_equal(det, -16.f, 2), "Matf3x3::determinant is incorrect")
		LOG(tlbx::INFO, "Unit test Matf3x3::determinant is done.")
	}

	{
		LOG(tlbx::INFO, "Starting unit test Matf3x3::transpose...")

		float result_transpose[9] = {
			5.f, 2.f, 8.f,
			7.f, 3.f, 10.f,
			9.f, 3.f, 2.f
		};

		ssml::Matf3 m(test_data3);
		ssml::Matf3 mt(result_transpose);

		ssml::Matf3 result = m.transpose();
		ASSERT((result == mt), "Matf3x3::transpose is incorrect")
		LOG(tlbx::INFO, "Unit test Matf3x3::transpose is done.")
	}

	{
		LOG(tlbx::INFO, "Starting unit test Matf3x3::scalarMult...")

		float result_scalarMult[9] = {
			25.f, 49.f, 81.f,
			4.f, 9.f, 9.f,
			64.f, 100.f, 4.f
		};

		ssml::Matf3 m(test_data3);
		ssml::Matf3 ms(result_scalarMult);

		ssml::Matf3 result = m.scalarMult(m);
		ASSERT((result == ms), "Matf3x3::scalarMult is incorrect")
		LOG(tlbx::INFO, "Unit test Matf3x3::scalarMult is done.")
	}

	{
		LOG(tlbx::INFO, "Starting unit test Matf3x3::inverse...")

		float result_inverse[9] = {
			1.5f, -4.75f, 0.375f,
			-1.25f, 3.875f, -0.1875f,
			0.25f, -0.375f, -0.0625f
		};

		ssml::Matf3 m(test_data3);
		ssml::Matf3 mi(result_inverse);

		ssml::Matf3 result = m.inverse();
		ASSERT((result == mi), "Matf3x3::inverse is incorrect")
		LOG(tlbx::INFO, "Unit test Matf3x3::inverse is done.")
	}

	{
		ssml::Matf3 m;
		std::cout << m << std::endl;
	}

	return 0;
}
