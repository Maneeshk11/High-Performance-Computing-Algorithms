#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

float min(float x, float y) {
    return (x < y) ? x : y;
}

void merge(float* A, float* temp, int from, int mid, int to, int N)
{
    int k = from, i = from, j = mid + 1;
    while (i <= mid && j <= to)
    {
        if (A[i] < A[j]) {
            temp[k++] = A[i++];
        }
        else {
            temp[k++] = A[j++];
        }
    }
    while (i < N && i <= mid) {
        temp[k++] = A[i++];
    }
    for (int i = from; i <= to; i++) {
        A[i] = temp[i];
    }
}

int main(int argc, char* argv[]) {
    struct timeval tv1, tv2;
	struct timezone tz;
    double elapsed; 

    int size = 40000000;
    int numTh = atoi(argv[1]);
    int N = size;
    float* A;
    float* B;
    A = (float*)calloc(sizeof(float), size);
    B = (float*)calloc(sizeof(float), size);
    omp_set_num_threads(numTh);
    for (int i = 0; i < N; i++) {
        A[i] = rand();
        B[i] = A[i];
    }

    gettimeofday(&tv1, &tz);
    int high = size - 1;
    int low = 0;
    for (int m = 1; m <= high - low; m *= 2)
    {
        #pragma omp parallel for shared(A,B)
        for (int i = low; i < high; i += 2*m)
        {
            int from = i;
            int mid = i + m - 1;
            int to = min(i + 2*m - 1, high);
 
            merge(A, B, from, mid, to, N);
        }
    }
    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("elapsed time = %4.2lf seconds.\n", elapsed);

}