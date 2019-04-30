# MPI-Parallelization

Program3a.c:
Implements matrix-vector multiplication using a block-column distribution of the matrix.
Process 0 reads in the matrix and then distributes the matrix to the other processes.

Program3b.c:
Times the cost of sending messages using MPI. Repeatedly sends messages between process 0 and process 1.
