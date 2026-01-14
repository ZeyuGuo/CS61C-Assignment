#include <time.h>
#include <stdio.h>
#include <x86intrin.h>
#include "simd.h"

long long int sum(int vals[NUM_ELEMS]) {
	clock_t start = clock();

	long long int sum = 0;
	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		for(unsigned int i = 0; i < NUM_ELEMS; i++) {
			if(vals[i] >= 128) {
				sum += vals[i];
			}
		}
	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return sum;
}

long long int sum_unrolled(int vals[NUM_ELEMS]) {
	clock_t start = clock();
	long long int sum = 0;

	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		for(unsigned int i = 0; i < NUM_ELEMS / 4 * 4; i += 4) {
			if(vals[i] >= 128) sum += vals[i];
			if(vals[i + 1] >= 128) sum += vals[i + 1];
			if(vals[i + 2] >= 128) sum += vals[i + 2];
			if(vals[i + 3] >= 128) sum += vals[i + 3];
		}

		//This is what we call the TAIL CASE
		//For when NUM_ELEMS isn't a multiple of 4
		//NONTRIVIAL FACT: NUM_ELEMS / 4 * 4 is the largest multiple of 4 less than NUM_ELEMS
		for(unsigned int i = NUM_ELEMS / 4 * 4; i < NUM_ELEMS; i++) {
			if (vals[i] >= 128) {
				sum += vals[i];
			}
		}
	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return sum;
}

long long int sum_simd(int vals[NUM_ELEMS]) {
	clock_t start = clock();
	__m128i _127 = _mm_set1_epi32(127);		// This is a vector with 127s in it... Why might you need this?
	long long int result = 0;				   // This is where you should put your final result!
	/* DO NOT DO NOT DO NOT DO NOT WRITE ANYTHING ABOVE THIS LINE. */
	
	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		/* YOUR CODE GOES HERE */
		__m128i sum_vec = _mm_setzero_si128();
		for(unsigned int i = 0; i < NUM_ELEMS / 4 * 4; i += 4) {
			__m128i load_data = _mm_loadu_si128((__m128i*)(vals + i));
			// (a_i > b_i ? 0xffffffff : 0x0 for i from 0 to 3)
			__m128i mask = _mm_cmpgt_epi32(load_data, _127);
			__m128i add_data = _mm_and_si128(load_data, mask);
			sum_vec = _mm_add_epi32(sum_vec, add_data);
		}
		/* You'll need a tail case. */
		int tail_sum = 0;
		for(unsigned int i = NUM_ELEMS / 4 * 4; i < NUM_ELEMS; i++) {
			if (vals[i] >= 128) {
				tail_sum += vals[i];
			}
		}
		int sum_arr[4] = {0};
		_mm_storeu_si128((__m128i*)sum_arr, sum_vec);
		result += sum_arr[0] + sum_arr[1] + sum_arr[2] + sum_arr[3] + tail_sum;
	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return result;
}

long long int sum_simd_unrolled(int vals[NUM_ELEMS]) {
	clock_t start = clock();
	__m128i _127 = _mm_set1_epi32(127);
	long long int result = 0;
	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		/* COPY AND PASTE YOUR sum_simd() HERE */
		/* MODIFY IT BY UNROLLING IT */
		__m128i sum_vec_0 = _mm_setzero_si128();
		__m128i sum_vec_1 = _mm_setzero_si128();
		__m128i sum_vec_2 = _mm_setzero_si128();
		__m128i sum_vec_3 = _mm_setzero_si128();
		for(unsigned int i = 0; i < NUM_ELEMS / 16 * 16; i += 16) {
			__m128i load_data = _mm_loadu_si128((__m128i*)(vals + i));
			__m128i mask = _mm_cmpgt_epi32(load_data, _127);
			__m128i add_data = _mm_and_si128(load_data, mask);
			sum_vec_0 = _mm_add_epi32(sum_vec_0, add_data);

			load_data = _mm_loadu_si128((__m128i*)(vals + i + 4));
			mask = _mm_cmpgt_epi32(load_data, _127);
			add_data = _mm_and_si128(load_data, mask);
			sum_vec_1 = _mm_add_epi32(sum_vec_1, add_data);

			load_data = _mm_loadu_si128((__m128i*)(vals + i + 8));
			mask = _mm_cmpgt_epi32(load_data, _127);
			add_data = _mm_and_si128(load_data, mask);
			sum_vec_2 = _mm_add_epi32(sum_vec_2, add_data);

			load_data = _mm_loadu_si128((__m128i*)(vals + i + 12));
			mask = _mm_cmpgt_epi32(load_data, _127);
			add_data = _mm_and_si128(load_data, mask);
			sum_vec_3 = _mm_add_epi32(sum_vec_3, add_data);
		}
		/* You'll need 1 or maybe 2 tail cases here. */
		int tail_sum = 0;
		for(unsigned int i = NUM_ELEMS / 16 * 16; i < NUM_ELEMS; i++) {
			if (vals[i] >= 128) {
				tail_sum += vals[i];
			}
		}
		int sum_arr[4] = {0};
		_mm_storeu_si128((__m128i*)sum_arr, sum_vec_0);
		result += sum_arr[0] + sum_arr[1] + sum_arr[2] + sum_arr[3];
		
		_mm_storeu_si128((__m128i*)sum_arr, sum_vec_1);
		result += sum_arr[0] + sum_arr[1] + sum_arr[2] + sum_arr[3];

		_mm_storeu_si128((__m128i*)sum_arr, sum_vec_2);
		result += sum_arr[0] + sum_arr[1] + sum_arr[2] + sum_arr[3];

		_mm_storeu_si128((__m128i*)sum_arr, sum_vec_3);
		result += sum_arr[0] + sum_arr[1] + sum_arr[2] + sum_arr[3];

		result += tail_sum;
	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return result;
}