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
##### Without SSE
| Function | SSML | GLM | ratio |
|---|---|---|---|
| scalarMult | 1.30 | 2.14 | 0.67 |
| transpose | 1.32 | 5.33 | 0.24 |
| determinant | 17.3\* | 7.68 | 2.25 |
| mult | 1.33 | 5.99 | 0.22 |
| inverse | 368\* | 30.2 | 12.18 |

##### With SSE
| Function | SSML | GLM | ratio |
|---|---|---|---|
| scalarMult | 1.36 | 1.76 | 0.77 |
| transpose | 1.29 | 5.43 | 0.23 |
| determinant | 0.317 | 7.68 | 0.04 |
| mult | 1.29 | 5.60 | 0.23 |
| inverse | 1.31 | 31.2 | 0.04 |

#### Matrix3x3
##### Without SSE
| Function | SSML | GLM | ratio |
|---|---|---|---|
| scalarMult | 1.03 | 1.23 | 0.83 |
| transpose | 1.01 | 2.85 | 0.35 |
| determinant | 4.38\* | 2.41 | 1.81 |
| mult | 1.01 | 7.76 | 0.13 |
| inverse | 22.0\* | 8.53 | 2.57 |

##### With SSE
| Function | SSML | GLM | ratio |
|---|---|---|---|
| scalarMult | 6.86 | 1.21 | 5.66 |
| transpose | 0.977 | 2.95 | 0.33 |
| determinant | 0.358 | 2.37 | 0.15 |
| mult | 1.04 | 7.41 | 0.14 |
| inverse | 5.59 | 8.33 | 0.67 |

#### Matrix2x2
##### Without SSE
| Function | SSML | GLM | ratio |
|---|---|---|---|
| scalarMult | 0.366 | 0.322 | 1.13 |
| transpose | 0.321 | 0.337 | 0.95 |
| determinant | 0.356 | 0.362 | 0.98 |
| mult | 0.331 | 0.320 | 1.03 |
| inverse | 2.04 | 0.317 | 6.43 |

##### With SSE
| Function | SSML | GLM | ratio |
|---|---|---|---|
| scalarMult | 0.333 | 0.324 | 1.02 |
| transpose | 0.373 | 0.432 | 0.86 |
| determinant | 0.317 | 0.360 | 0.88 |
| mult | 0.349 | 0.342 | 1.02 |
| inverse | 0.336 | 0.359 | 0.93 |

\* *these functions are not working yet* 

### License
This project is under the [MIT License](./License.txt).

