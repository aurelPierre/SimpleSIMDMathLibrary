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

	float d[16] = {
			5.f, 7.f, 9.f, 10.f,
		 	2.f, 3.f, 3.f, 8.f,
			8.f, 10.f, 2.f, 3.f,
			3.f, 3.f, 4.f, 8.f };
	Matf4x4 a(d);
	Matf4x4 c = a * a;
	logMatrix(c);

	return 0;
}
