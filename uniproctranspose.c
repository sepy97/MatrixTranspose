#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

int A [10000][10000];

//printing out a matrix for debugging purposes
void printA (int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf ("%d \n", A [i][j]);
		}
	}
}

int main (int argc, char** argv)
{
	//used for timing
	struct timeval start, end;
	
	int n = 8;
	if (argc > 1) n = atoi (argv [1]);  //size of a matrix taken from a command line argument
	
	//matrix initialization
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			A [i][j] = i*n+j;
		}
	}
	
	//time measurement
	gettimeofday(&start, NULL);
	//transpose matrix
	for (int i = 0; i < n; i++)
	{
		for (int j = i+1; j < n; j++)
		{
			int temp = A [i][j];
			A [i][j] = A [j][i];
			A [j][i] = temp;
		}
	}
	//time measurement
	gettimeofday(&end, NULL);
	//printing out matrix for a debugging purposes
	if (n == 8) printA (n);
	
	printf ("%.8f \n",
	        (double)((end.tv_sec * 1000000 + end.tv_usec) -
	                 (start.tv_sec * 1000000 + start.tv_usec))/1000000.0);
	return 0;
}
