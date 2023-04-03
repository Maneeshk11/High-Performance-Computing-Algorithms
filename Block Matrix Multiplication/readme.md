# This is a multi-thread code for the excecution of Block matrix multiplication using Openmp.

- Follow the following steps to excecute the C file.

- Requirements to run the file
 1.  OpenMp
 2.  gcc
 
* The following command can be used to generate the output file.  ``` gcc -fopenmp FILENAME.c -o FILENAME.o ```
* The output file needs 4 input parameters to run:
    1. Size/order of the matrix
    2. Block size
    3. No of threads required to execute the code
    4. The power of the matrix.
* The following command can be run to execute the object file ``` ./FILENAME.o <matrix-order> <BlockSize> <no. of threads> <power of matrix> ```.
* Finally the result will be the time taken for the execution of block matrix multipliocation.