#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

int A [10000][10000];
int sharedCounter = 0;
pthread_mutex_t lock;

struct thread_args {
	int size;      //size of a matrix
};

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

void* transpose (void* arg)
{
	int n = ((struct thread_args *) arg)->size; //matrix size as a thread argument
	int num = 0;
	while (sharedCounter < n*n)
	{
		//securely read and increment shared counter
		pthread_mutex_lock (&lock);
		num = sharedCounter;
		sharedCounter++;
		pthread_mutex_unlock (&lock);
		
		//computing array indexes
		int i = num / n;
		int j = num % n;
		if (j > i)
		{
			int temp = A[i][j];
			A[i][j] = A[j][i];
			A[j][i] = temp;
		}
	}
}

int main (int argc, char** argv)
{
	//used for timing
	struct timeval start, end;
	
	int n = 8;
	if (argc > 1) n = atoi (argv [1]); //size of a matrix taken from a command line argument
	
	//matrix initialization
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			A [i][j] = i*n+j;
		}
	}
	
	int t = 1;
	if (argc > 2) t = atoi (argv[2]); //number of threads taken from a command line argument
	pthread_t my_thread[t+1];
	pthread_mutex_init(&lock, NULL);
	struct thread_args* thr = (struct thread_args*) malloc (sizeof (struct thread_args));
	thr->size = n;
	
	//time measurement
	gettimeofday(&start, NULL);
	for (int id = 1; id <= t; id++)
	{
		pthread_create(&my_thread[id], NULL, &transpose, (void*) thr);
	}
	for (int id = 1; id <= t; id++)
	{
		pthread_join (my_thread[id], NULL);
	}
	//time measurement
	gettimeofday(&end, NULL);
	//printing out a matrix for a debugging purposes
	if (n == 8) printA (n);
	
	printf ("%.8f ; ",
	        (double)((end.tv_sec * 1000000 + end.tv_usec) -
	                 (start.tv_sec * 1000000 + start.tv_usec))/1000000.0);
	return 0;
}
