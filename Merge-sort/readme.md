# This is a multi-thread code for the excecution of mergesort algorith using bottom-up approach in openmp. The implementation is done when the array holds int, double, float values. The default size of the array in this implementation is 4 * 10^7.

* Follow the following steps to excecute the C file.

* Requirements to run the file
    1.  OpenMp
    2.  gcc
 
* The following command can be used to generate the output file.  ``` gcc -fopenmp FILENAME.c -o FILENAME.o ```
* The output file needs 3 input parameters to run
    1. No of threads required to execute the code
* The following command can be run to execute the object file ``` ./FILENAME.o <no. of threads> ```.
* Finally the result will be the time taken for the execution of the merge sort algorithm over the array.