#include <stdio.h>
#include <omp.h>

int main() {
	#pragma omp parallel
	{
		int thread_ID = omp_get_thread_num();
		printf("hello world %d\n", thread_ID);
		printf("number of threads: %d\n", omp_get_num_threads());
	}
}
