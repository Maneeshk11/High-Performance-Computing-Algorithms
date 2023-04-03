# This is a multi-thread code for the excecution of n-queens problem using Openmp.

- Follow the following steps to excecute the C file.

- Requirements to run the file
 1.  OpenMp
 2.  gcc
 
* The following command can be used to generate the output file.  ``` gcc -fopenmp FILENAME.c -o FILENAME.o ```
* The output file needs 1 input parameters to run:
    1. size of the board
* The following command can be run to execute the object file ``` ./FILENAME.o <size of board> ```.
* Finally the result will be the time taken for the solving the n-queens problem for number of threads ranging from 4 to 16. The number of solutions possible/calculated is also shown.