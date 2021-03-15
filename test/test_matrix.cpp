#include "Matrix.h"

#include "Logger.h"
#include "Profiler.h"

void logMatrix(const tlbx::Matrix& matrix)
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

void logMatrixSSE(const tlbx::MatrixSSE& matrix)
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

void unit_test()
{
	float d[16] = {
			5.f, 7.f, 9.f, 10.f,
		 	2.f, 3.f, 3.f, 8.f,
			8.f, 10.f, 2.f, 3.f,
			3.f, 3.f, 4.f, 8.f };
	tlbx::Matrix a(d);
	tlbx::Matrix c = a * a;
	logMatrix(c);

	tlbx::MatrixSSE aa(d);
	tlbx::MatrixSSE cc = aa * aa;
	logMatrixSSE(cc);
}

int main(int argc, char** argv)
{
	tlbx::Channel::Add<tlbx::StdChannel>();
	tlbx::Channel::Add<tlbx::FileChannel>();

	//unit_test();

	float d[16] = {
			5.f, 7.f, 9.f, 10.f,
		 	2.f, 3.f, 3.f, 8.f,
			8.f, 10.f, 2.f, 3.f,
			3.f, 3.f, 4.f, 8.f };

	size_t nb = 10000000;
	for(size_t i = 0; i < nb; ++i)
	{
		tlbx::Matrix m1(d);
		tlbx::Matrix m2(d);

		tlbx::Profiler p("Matrix");

		tlbx::Matrix dst = m1 * m2;
	}

	LOG(tlbx::INFO, "-----------------");
	LOG(tlbx::INFO, "Benchmark Matrix:");
	LOG(tlbx::INFO, "-----------------");
	LOG(tlbx::INFO, "Min: " + std::to_string(tlbx::Profiler::_profile["Matrix"]._min));
	LOG(tlbx::INFO, "Avg: " + std::to_string(tlbx::Profiler::_profile["Matrix"]._avg));
	LOG(tlbx::INFO, "Max: " + std::to_string(tlbx::Profiler::_profile["Matrix"]._max));

	for(size_t i = 0; i < nb; ++i)
	{
		tlbx::MatrixSSE m1(d);
		tlbx::MatrixSSE m2(d);

		tlbx::Profiler p("MatrixESS");

		tlbx::MatrixSSE dst = m1 * m2;
	}

	LOG(tlbx::INFO, "");

	LOG(tlbx::INFO, "--------------------");
	LOG(tlbx::INFO, "Benchmark MatrixESS:");
	LOG(tlbx::INFO, "--------------------");
	LOG(tlbx::INFO, "Min: " + std::to_string(tlbx::Profiler::_profile["MatrixESS"]._min));
	LOG(tlbx::INFO, "Avg: " + std::to_string(tlbx::Profiler::_profile["MatrixESS"]._avg));
	LOG(tlbx::INFO, "Max: " + std::to_string(tlbx::Profiler::_profile["MatrixESS"]._max));

	LOG(tlbx::INFO, "");

	LOG(tlbx::INFO, "--------------------");
	LOG(tlbx::INFO, "Matrix vs MatrixESS:");
	LOG(tlbx::INFO, "--------------------");
	LOG(tlbx::INFO, "Min: " + std::to_string(tlbx::Profiler::_profile["Matrix"]._min / tlbx::Profiler::_profile["MatrixESS"]._min));
	LOG(tlbx::INFO, "Avg: " + std::to_string(tlbx::Profiler::_profile["Matrix"]._avg / tlbx::Profiler::_profile["MatrixESS"]._avg));
	LOG(tlbx::INFO, "Max: " + std::to_string(tlbx::Profiler::_profile["Matrix"]._max / tlbx::Profiler::_profile["MatrixESS"]._max));

	return 0;
}
