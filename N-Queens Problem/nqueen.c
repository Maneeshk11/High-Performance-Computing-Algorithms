#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <omp.h>

#define MAX_N 16

int n, solutions;
int col[MAX_N];

bool check(int row) {
    for (int i = 0; i < row; i++) {
        if (col[i] == col[row] ||
            abs(col[i] - col[row]) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

void backtrack(int row) {
    if (row == n) {
        #pragma omp atomic
        solutions++;
        return;
    }
    for (int i = 0; i < n; i++) {
        col[row] = i;
        if (check(row)) {
            backtrack(row + 1);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s N\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);
    if (n < 4 || n > MAX_N) {
        printf("N must be between 4 and %d\n", MAX_N);
        return 1;
    }

    int threads;
    double start, end, runtime;

    for (threads = 1; threads <= 12; threads++) {
        solutions = 0;
        omp_set_num_threads(threads);

        start = omp_get_wtime();
        #pragma omp parallel
        {
            #pragma omp single nowait
            backtrack(0);
        }
        end = omp_get_wtime();

        runtime = (end - start) / 5.0;
        printf("Threads: %d, Solutions: %d, Runtime: %.6f\n",
               threads, solutions, runtime);
    }

    return 0;
}