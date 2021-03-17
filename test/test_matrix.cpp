#include "Matrix_r4f.h"

#include "Logger.h"

using Matf4x4 = ssml::Matrix<4,4,float>;

void logMatrix(const Matf4x4& matrix)
{
	std::string s = "\n";
	for(size_t i = 0; i < 4; ++i)
	{
		for(size_t j = 0; j < 4; ++j)
			s += '[' + std::to_string(matrix._data[i][j]) + ']';
		s += '\n';
	}
	LOG(tlbx::DEBUG, s);
}

int main(int argc, char** argv)
{
	tlbx::Channel::Add<tlbx::StdChannel>();
	tlbx::Channel::Add<tlbx::FileChannel>();

	float test_data[16] = {
			5.f, 7.f, 9.f, 10.f,
		 	2.f, 3.f, 3.f, 8.f,
			8.f, 10.f, 2.f, 3.f,
			3.f, 3.f, 4.f, 8.f };
	Matf4x4 m(test_data);
	Matf4x4 r = m * m;

	float result_data[16] = {
		141.f, 176.f, 124.f, 213.f,
		64.f, 77.f, 65.f, 117.f,
		85.f, 115.f, 118.f, 190.f,
		77.f, 94.f, 76.f, 130.f
	};

	Matf4x4 result(result_data);

	ASSERT((result == r), "Matf4x4::operator* is incorrect")

	return 0;
}
