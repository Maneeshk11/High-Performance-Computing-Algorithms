#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

int main(int argc, char*argv[]) {
    struct timeval tv1, tv2;
	struct timezone tz;
    double elapsed; 
    double **A;
    double **B;
    double **C;
    int size=atoi(argv[1]);
	int numTh=atoi(argv[2]);
    int power=atoi(argv[3]);
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
    // int power = 2;  // A^power
    gettimeofday(&tv1, &tz);
    
    for (int m = 0; m<power-1;m++) {
        if (m%2 == 0) {
            #pragma omp parallel for shared(A,B,C)
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    for (int k = 0; k < N; k++) { 
                        C[i][j]=B[i][k] * A[k][j];
                    }
                }
	        }
        }
        else {
            #pragma omp parallel for shared(A,B,C)
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    for (int k = 0; k < N; k++) { 
                        B[i][j]=C[i][k] * A[k][j];
                    }
                }
            }
        }
    }
    gettimeofday(&tv2, &tz);
	elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("elapsed time = %4.2lf seconds.\n", elapsed);
}