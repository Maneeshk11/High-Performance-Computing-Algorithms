# This is a multi-thread code for the excecution of Ordinary matrix multiplication.

- Follow the following steps to excecute the C file.
 
* The following command can be used to generate the output file.  ``` gcc -fopenmp FILENAME.c -o FILENAME.o ```
* The output file needs 3 input parameters to run
    1. Size/order of the matrix
    2. No of threads required to execute the code
    3. The power of the matrix.
* ``` ./FILENAME.o <matrix-order> <no. of threads> <power of matrix>