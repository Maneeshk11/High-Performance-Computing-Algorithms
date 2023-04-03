#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include <math.h>
#define MIN_MATRIX_SIZE 512
#define MAX_MATRIX_SIZE 2048
#define MIN_BLOCK_SIZE 4
#define MAX_BLOCK_SIZE 64
#define MIN_POWER 2
#define MAX_POWER 16
#define NUM_ITERATIONS 10

void fill_matrix(int matrix_size, double *matrix) {
    int i;
    for (i = 0; i < matrix_size * matrix_size; i++) {
        matrix[i] = (double)rand() / RAND_MAX;
    }
}

void transpose_block(int block_size, double *A, double *B, int ldA, int ldB) {
    int i, j;
    for (i = 0; i < block_size; i++) {
        for (j = 0; j < block_size; j++) {
            B[j * ldB + i] = A[i * ldA + j];
        }
    }
}

void block_multiply(int block_size, double *A, double *B, double *C, int ldA, int ldB, int ldC) {
    int i, j, k;
    for (i = 0; i < block_size; i++) {
        for (j = 0; j < block_size; j++) {
            double sum = 0;
            for (k = 0; k < block_size; k++) {
                sum += A[i * ldA + k] * B[k * ldB + j];
            }
            C[i * ldC + j] = sum;
        }
    }
}

void block_matrix_multiply_parallel(int matrix_size, int block_size, double *A, double *B, double *C) {
    int i, j, k;
    int ldA = matrix_size;
    int ldB = matrix_size;
    int ldC = matrix_size;
    double *B_transposed = malloc(matrix_size * matrix_size * sizeof(double));
    for (i = 0; i < matrix_size; i += block_size) {
        for (j = 0; j < matrix_size; j += block_size) {
            for (k = 0; k < matrix_size; k += block_size) {
            #pragma omp parallel
            {
                int i_local, j_local, k_local;
                int A_local_index, B_local_index, C_local_index;
                double *A_local, *B_local, *C_local;
                A_local = &A[i * ldA + k];
                B_local = &B[k * ldB + j];
                C_local = &C[i * ldC + j];
                transpose_block(block_size, &B[k * ldB + j], &B_transposed[j * ldB + k], ldB, ldB);
                #pragma omp for
                for (i_local = 0; i_local < block_size; i_local++) {
                    for (j_local = 0; j_local < block_size; j_local++) {
                        double sum = 0;
                        for (k_local = 0; k_local < block_size; k_local++) {
                            sum += A_local[i_local * ldA + k_local] * B_transposed[j_local * ldB + k_local];
                        }
                        C_local[i_local * ldC + j_local] = sum;
                    }
                }
            }
            }
        }   
    }
    free(B_transposed);
}

int main(int argc, char *argv[]) {
    struct timeval tv1, tv2;
	struct timezone tz;
    double elapsed; 
    double **A;
    double **B;
    double **C;
    int size=atoi(argv[1]);
    int block_size=atoi(argv[2]);
	int numTh=atoi(argv[3]);
    int power=atoi(argv[4]);
    int N=size;
    A=(double **)calloc(sizeof(double *), size);
	B=(double **)calloc(sizeof(double *), size);
	C=(double **)calloc(sizeof(double *), size);
    for(int i=0;i<N;i++)
	{
		A[i]=(double *)calloc(sizeof(double), size);
		B[i]=(double *)calloc(sizeof(double), size);
		C[i]=(double *)calloc(sizeof(double), size);
	}
    omp_set_num_threads(numTh); // no of threads
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            A[i][j] = (double)rand() / (double)RAND_MAX;
            B[i][j] = A[i][j];
        }
    }
    gettimeofday(&tv1, &tz);
    block_matrix_multiply_parallel(size, block_size, A, B, C);
    gettimeofday(&tv1, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("elapsed time = %4.2lf seconds.\n", elapsed);
    return 0;
}