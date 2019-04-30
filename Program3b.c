/*
 * Program3b.c
 *
 *  Created on: Nov 4, 2016
 *      Author: Chong
 *  Description: Keeps sending message back and forth from processor 0 and 1, and times
 *  the runtime for processor 0 and 1 sending n times.
 */
#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <time.h>

int main(int argc, char* argv[]){
	int  my_rank; /* rank of process */
	int  p;       /* number of processes */
	int tag = 0;
	char message[100]; // size of message
	MPI_Status status;

	/* start up MPI */

	MPI_Init(&argc, &argv);

	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	//sets number of processors
	p = 2;

	for(int n = 1; n < 100000000; n *= 2){
		//begins the timer
		clock_t begin = clock();
		double start = MPI_Wtime();
		for(int i = 0; i < n; i++)
			if(my_rank == 0){
				sprintf(message, "Hello MPI World from process %d!", my_rank);
				//Sending message to process 1
				MPI_Send(message, strlen(message)+1, MPI_CHAR, 1, tag, MPI_COMM_WORLD);
				//Receiving message from process 1
				MPI_Recv(message, 100, MPI_CHAR, 1, tag, MPI_COMM_WORLD, &status);
			}
			else if(my_rank == 1){
				//Receiving message from process 0
				MPI_Recv(message, 100, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
				//Sending message from process 1
				MPI_Send(message, strlen(message)+1, MPI_CHAR, 0, tag, MPI_COMM_WORLD);
			}
		double end = MPI_Wtime();
		clock_t end1 = clock();
		double time_spent = (double)(end1 - begin) / CLOCKS_PER_SEC;
		printf("Ping: %d\n", n);
		printf("Time in seconds: %f\n", time_spent);
		printf("Runtime=%f\n", end-start);
	}



	/* shut down MPI */
	MPI_Finalize();


	return 0;
}
