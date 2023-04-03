# This is a multi-thread code for the excecution of Ordinary matrix multiplication using Openmp.

- Follow the following steps to excecute the C file.

- Requirements to run the file
 * Openmp
 * gcc
 
* The following command can be used to generate the output file.  ``` gcc -fopenmp FILENAME.c -o FILENAME.o ```
* The output file needs 3 input parameters to run
    1. Size/order of the matrix
    2. No of threads required to execute the code
    3. The power of the matrix.
* The following command can be run to execute the object file ``` ./FILENAME.o <matrix-order> <no. of threads> <power of matrix> ```.
* Finally the result will be the time taken for the execution of the multiplication of the matrix.