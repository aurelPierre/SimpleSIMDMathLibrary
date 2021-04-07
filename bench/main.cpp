#include <cstdlib>
#include <ctime>

#include "Matrix.h"
#include "glm/matrix.hpp"

#include <benchmark/benchmark.h>

template<uint8_t R, uint8_t C, class T>
ssml::Matrix<R, C, T> create_ssml_matrix()
{
	std::srand(std::time(nullptr));
	
	T test_data[R*C];
	for(size_t i = 0; i < R*C; ++i)
		test_data[i] = std::rand();

	ssml::Matrix<R, C, T> m(test_data);
	return m;
}

template<class T, uint8_t R>
T create_glm_matrix()
{
	std::srand(std::time(nullptr));
	T m;
	for(size_t i = 0; i < R; ++i)
	{
		for(size_t j = 0; j < R; ++j)
			m[i][j] = std::rand();
	}
	return m;
}

template<uint8_t R, class T>
static void BM_ssml_scalarMult(benchmark::State& state)
{
	ssml::Matrix<R, R, T> m = create_ssml_matrix<R, R, T>();
	ssml::Matrix<R, R, T> n = create_ssml_matrix<R, R, T>();
	for(auto _ : state)
		benchmark::DoNotOptimize(m.scalarMult(n));
}
BENCHMARK_TEMPLATE(BM_ssml_scalarMult, 4, float);
BENCHMARK_TEMPLATE(BM_ssml_scalarMult, 3, float);
BENCHMARK_TEMPLATE(BM_ssml_scalarMult, 2, float);

template<class T, uint8_t R>
static void BM_glm_scalarMult(benchmark::State& state)
{
	T m = create_glm_matrix<T, R>();
	T n = create_glm_matrix<T, R>();
	for(auto _ : state)
		benchmark::DoNotOptimize(matrixCompMult(m, n));
}
BENCHMARK_TEMPLATE(BM_glm_scalarMult, glm::mat4, 4);
BENCHMARK_TEMPLATE(BM_glm_scalarMult, glm::mat3, 3);
BENCHMARK_TEMPLATE(BM_glm_scalarMult, glm::mat2, 2);

template<uint8_t R, class T>
static void BM_ssml_transpose(benchmark::State& state)
{
	ssml::Matrix<R, R, T> m = create_ssml_matrix<R, R, T>();
	for(auto _ : state)
		benchmark::DoNotOptimize(m.transpose());
}
BENCHMARK_TEMPLATE(BM_ssml_transpose, 4, float);
BENCHMARK_TEMPLATE(BM_ssml_transpose, 3, float);
BENCHMARK_TEMPLATE(BM_ssml_transpose, 2, float);

template<class T, uint8_t R>
static void BM_glm_transpose(benchmark::State& state)
{
	T m = create_glm_matrix<T, R>();
	for(auto _ : state)
		benchmark::DoNotOptimize(transpose(m));
}
BENCHMARK_TEMPLATE(BM_glm_transpose, glm::mat4, 4);
BENCHMARK_TEMPLATE(BM_glm_transpose, glm::mat3, 3);
BENCHMARK_TEMPLATE(BM_glm_transpose, glm::mat2, 2);

template<uint8_t R, class T>
static void BM_ssml_determinant(benchmark::State& state)
{
	ssml::Matrix<R, R, T> m = create_ssml_matrix<R, R, T>();
	for(auto _ : state)
		benchmark::DoNotOptimize(m.determinant());
}
BENCHMARK_TEMPLATE(BM_ssml_determinant, 4, float);
BENCHMARK_TEMPLATE(BM_ssml_determinant, 3, float);
BENCHMARK_TEMPLATE(BM_ssml_determinant, 2, float);

template<class T, uint8_t R>
static void BM_glm_determinant(benchmark::State& state)
{
	T m = create_glm_matrix<T, R>();
	for(auto _ : state)
		benchmark::DoNotOptimize(determinant(m));
}
BENCHMARK_TEMPLATE(BM_glm_determinant, glm::mat4, 4);
BENCHMARK_TEMPLATE(BM_glm_determinant, glm::mat3, 3);
BENCHMARK_TEMPLATE(BM_glm_determinant, glm::mat2, 2);

template<uint8_t R, uint8_t C, uint8_t NC, class T>
static void BM_ssml_mult(benchmark::State& state)
{
	ssml::Matrix<R, C, T> m = create_ssml_matrix<R, C, T>();
	ssml::Matrix<C, NC, T> n = create_ssml_matrix<C, NC, T>();
	for(auto _ : state)
		benchmark::DoNotOptimize(m * n);
}
BENCHMARK_TEMPLATE(BM_ssml_mult, 4, 4, 4, float);
BENCHMARK_TEMPLATE(BM_ssml_mult, 3, 3, 3, float);
BENCHMARK_TEMPLATE(BM_ssml_mult, 2, 2, 2, float);

template<class T, uint8_t R>
static void BM_glm_mult(benchmark::State& state)
{
	T m = create_glm_matrix<T, R>();
	T n = create_glm_matrix<T, R>();
	for(auto _ : state)
		benchmark::DoNotOptimize(m * n);
}
BENCHMARK_TEMPLATE(BM_glm_mult, glm::mat4, 4);
BENCHMARK_TEMPLATE(BM_glm_mult, glm::mat3, 3);
BENCHMARK_TEMPLATE(BM_glm_mult, glm::mat2, 2);

template<uint8_t R, class T>
static void BM_ssml_inverse(benchmark::State& state)
{
	ssml::Matrix<R, R, T> m = create_ssml_matrix<R, R, T>();
	for(auto _ : state)
		benchmark::DoNotOptimize(m.inverse());
}
BENCHMARK_TEMPLATE(BM_ssml_inverse, 4, float);
BENCHMARK_TEMPLATE(BM_ssml_inverse, 3, float);
BENCHMARK_TEMPLATE(BM_ssml_inverse, 2, float);

template<class T, uint8_t R>
static void BM_glm_inverse(benchmark::State& state)
{
	T m = create_glm_matrix<T, R>();
	for(auto _ : state)
		benchmark::DoNotOptimize(inverse(m));
}
BENCHMARK_TEMPLATE(BM_glm_inverse, glm::mat4, 4);
BENCHMARK_TEMPLATE(BM_glm_inverse, glm::mat3, 3);
BENCHMARK_TEMPLATE(BM_glm_inverse, glm::mat2, 2);

BENCHMARK_MAIN();
