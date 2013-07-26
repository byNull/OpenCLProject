#include "mm_mul.h"
//#include <immintrin.h>

int R_Size = 2048;
int C_Size = 2048;

void SpMV_NONE(char matrix[2048][2048], unsigned char vector[2048], int result[2048])
{
    int i, j;

    for (i = 0; i < 2048; i++) {
	    char *row = matrix[i];
		int sum = 0;

		for (j = 0; j < 2048; j++) {
		    char c = row[j];

		    if (c) {
			    unsigned short a = vector[j];
				short b = c;
			    short v = a * c;

				sum += v;
			}
		}
		result[i] = sum;
	}
}

void SpMV_SSE(char matrix[2048][2048], unsigned char vector[2048], int result[2048])
{
   /* int i, j;

    for (i = 0; i < R_Size; i++) {
	    char *row = matrix[i];
		__m128i sum = _mm_setzero_si128();

		for (j = 0; j < C_Size / sizeof(__m128i); j++) {
		    __m128i a = _mm_load_si128((__m128i *)vector + j);
			__m128i b = _mm_load_si128((__m128i *)row + j);
			__m128i c = _mm_maddubs_epi16(a, b);

			__m128i c0 = _mm_cvtepi16_epi32(c);
			__m128i c1 = _mm_cvtepi16_epi32(_mm_srli_si128(c, 8));

			sum = _mm_add_epi32(sum, c0);
			sum = _mm_add_epi32(sum, c1);
		}

		sum = _mm_hadd_epi32(sum, sum);
		sum = _mm_hadd_epi32(sum, sum);
		result[i] = _mm_cvtsi128_si32(sum);
	}*/
}

#if 0
void SpMV_AVX(char matrix[2048][2048], unsigned char vector[2048], int result[2048])
{
   /* int i, j;

    for (i = 0; i < 2048; i++) {
	    char *row = matrix[i];
		__m256i sum = _mm256_setzero_si256();

		for (j = 0; j < 2048 / sizeof(__m256i); j++) {
		    __m256i a = _mm256_load_si256((__m256i *)vector + j);
			__m256i b = _mm256_load_si256((__m256i *)row + j);
			__m256i c = _mm256_maddubs_epi16(a, b);

			__m256i c0 = _mm256_cvtepi16_epi32(c);
			__m256i c1 = _mm256_cvtepi16_epi32(_mm256_srli_si256(c, 16));

			sum = _mm256_add_epi32(sum, c0);
			sum = _mm256_add_epi32(sum, c1);
		}

		sum = _mm256_hadd_epi32(sum, sum);
		sum = _mm256_hadd_epi32(sum, sum);
		sum = _mm256_hadd_epi32(sum, sum);
		result[i] = _mm256_cvtsi256_si32(sum);
	}*/
}
#endif