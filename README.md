# SimpleSIMDMathLibrary

![CI](https://github.com/aurelPierre/SimpleSIMDMathLibrary/actions/workflows/ci.yml/badge.svg)
![codecov](https://codecov.io/gh/aurelPierre/SimpleSIMDMathLibrary/branch/main/graph/badge.svg?token=V2K9IRWT94)

### Description
Simple SIMD Math Library (SSML) is a math library built using simd instructions to enhance performance.

### Purpose
It is written as an experimental library to learn SIMD intrinsics and see how it can fare against well established math library such as [glm](https://github.com/g-truc/glm). It is not meant to replace a math library, the content is insufficient and experimental.

### Content
 | Types | Scalar | SSE | AVX |
 |---|---|---|---|
 |Matrix4x4| &#10004;* | &#10004; ||
 |Matrix3x3| &#10004;* | &#10004; ||
 |Matrix2x2| &#10004; | &#10004; ||

 \* *These types are not fully functional*

### Benchmark
Made on my laptop with an [Intel i7-7700HQ](https://ark.intel.com/content/www/us/en/ark/products/97185/intel-core-i7-7700hq-processor-6m-cache-up-to-3-80-ghz.html) using [google benchmark](https://github.com/google/benchmark) and built in cmake Release mode with gcc 10.2.

#### Matrix4x4
| Function | SSML | SSML SSE | GLM |
|---|---|---|---|
| scalarMult | 1.30 | 1.36 | 1.76 |
| transpose | 1.32 | 1.29 | 5.43 |
| determinant | 17.3\* | 0.317 | 7.68 |
| mult | 1.33 | 5.99 | 5.60 |
| inverse | 368\* | 1.31 | 31.2 |

#### Matrix3x3
| Function | SSML | SSML SSE | GLM |
|---|---|---|---|
| scalarMult | 1.03 | 6.86 | 1.21 |
| transpose | 1.01 | 0.977 | 2.95 |
| determinant | 4.38\* | 0.358 | 2.37 |
| mult | 1.01 | 7.76 | 7.41 |
| inverse | 22.0\* | 5.59 | 8.33 |

#### Matrix2x2
| Function | SSML | SSML SSE | GLM |
|---|---|---|---|
| scalarMult | 0.366 | 0.333 | 0.324 |
| transpose | 0.321 | 0.373 | 0.432 |
| determinant | 0.356 | 0.317 | 0.360 |
| mult | 0.331 | 0.349 | 0.342 |
| inverse | 2.04 | 0.336 | 0.359 |

\* *these functions are not working yet* 

### License
This project is under the [MIT License](./License.txt).

