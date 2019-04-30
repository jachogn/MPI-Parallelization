/*
 * Program3a.c
 *
 * Created on: Nov 4, 2016
 *      Author: Chong
 * Description: Multiplying each row of a matrix and multiplying it by a vector, through
 * each processor. Main processor gathers the products and prints it out.
 * Directions
 */
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define comm_sz 4

void printarray(int array[]);

int main(void){
	int master = 0;
	int p;
	int numprocs;
	int product = 0;
	/*
	Initialize MPI.
	*/
	MPI_Init(NULL, NULL);
	/* Get the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	/* Get my rank among all the processes */
	MPI_Comm_rank(MPI_COMM_WORLD, &p);
	int matrix[comm_sz][comm_sz] = {
			{1, 2, 3 , 4} ,
			{5, 6, 7 , 8} ,
			{9, 10, 11 ,12} ,
			{13, 14 ,15, 16}
	};
	int locmatrix[comm_sz];
	int vector[comm_sz] = {1, 2, 3, 4};

	// Send row of matrix to all processors
	MPI_Scatter (matrix, comm_sz, MPI_INT, locmatrix, comm_sz, MPI_INT, 0, MPI_COMM_WORLD );
	// Send vector to all processors
	MPI_Bcast (vector, comm_sz, MPI_INT, master, MPI_COMM_WORLD );
	for(int i = 0; i < comm_sz; i++){
		product += locmatrix[i] * vector[i];
	}
	int results[comm_sz];
	MPI_Gather(&product, 1, MPI_INT, results, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if(p == master){
		printarray(results);
	}


	//Shutdown MPI
	MPI_Finalize ( );
	return 0;
}
//Print an array
void printarray(int array[]){
	for(int i = 0; i < comm_sz; i++){
		printf("%d ", array[i]);
	}
}
