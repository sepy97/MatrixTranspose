#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

int A [10000][10000];
int sharedCounter = 0;
pthread_mutex_t lock;

void printA (int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf ("%d ", A [i][j]);
		}
		printf ("\n");
	}
}
int main ()
{
	printf ("Hello, World!\n");
	
	struct timeval start, end;
	
	srand (time (NULL));
	int n = 32;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			A [i][j] = i*n+j;//rand () % 500;
		}
	}
	printA (n);
	printf ("##################\n\n");
	
	gettimeofday(&start, NULL);
	
	for (int i = 0; i < n; i++)
	{
		for (int j = i+1; j < n; j++)
		{
			int temp = A [i][j];
			A [i][j] = A [j][i];
			A [j][i] = temp;
		}
	}
	
	gettimeofday(&end, NULL);
	
	printA (n);
	
	printf ("%.8f ; \n ",
	        (double)((end.tv_sec * 1000000 + end.tv_usec) -
	                 (start.tv_sec * 1000000 + start.tv_usec))/1000000.0);
	return 0;
}
