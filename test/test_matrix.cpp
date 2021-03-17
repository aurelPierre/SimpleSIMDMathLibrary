#include "Matrix.h"
#include "Matrix_r4f.h"

#include "Logger.h"

int main(int argc, char** argv)
{
	tlbx::Channel::Add<tlbx::StdChannel>();
	tlbx::Channel::Add<tlbx::FileChannel>();

	{
		float test_data[16] = {
				5.f, 7.f, 9.f, 10.f,
		 		2.f, 3.f, 3.f, 8.f,
				8.f, 10.f, 2.f, 3.f,
				3.f, 3.f, 4.f, 8.f };
		ssml::Matf4 m(test_data);
		ssml::Matf4 r = m * m;

		float result_data[16] = {
			141.f, 176.f, 124.f, 213.f,
			64.f, 77.f, 65.f, 117.f,
			85.f, 115.f, 118.f, 190.f,
			77.f, 94.f, 76.f, 130.f
		};

		ssml::Matf4 result(result_data);
		
		ASSERT((result == r), "Matf4x4::operator* is incorrect")
	}
	
	{
		ssml::Matrix<10, 10, float> m;
		std::cout << m;
	}

	return 0;
}
