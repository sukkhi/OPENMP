#include <iostream>
#include <omp.h>

#define THREADS 4

//#define NORMAL_PROCESSING 
//#define INTERLEAVED_PROCESSING 
#define BATCH_PROCESSING

//#define PRINT
#define REPEAT 1

#define SIZE 800
int a[SIZE][SIZE];// = {{1,2,3,4}, {1,2,3,4}, {1,2,3,4}, {1,2,3,4}};
int b[SIZE][SIZE];// = {{1,2,3,4}, {1,2,3,4}, {1,2,3,4}, {1,2,3,4}};
int c[SIZE][SIZE];


int main()
{

#ifdef INTERLEAVED_PROCESSING
	int num_threads;
	num_threads = omp_get_max_threads();

#pragma omp parallel num_threads(THREADS)                   
	{
		int t_no, i, j;
		int temp =0;
		int k=0;
		t_no = omp_get_thread_num();
		int repeat = REPEAT;

		while(repeat --)
		{
			for(i=t_no; i<SIZE; i=i+THREADS)
			{
				temp =0;
				k=0;
				while(k != SIZE)
				{
					for(j=0; j<SIZE; j++)
					{
						temp += (a[i][j] * b[j][k]);
					}
					c[i][k] = temp;
					temp =0;
					k++;
				}
			}
		}

	}





#endif


#ifdef BATCH_PROCESSING
	int num_threads;
	num_threads = omp_get_max_threads();

	int quantum = SIZE/THREADS;
	if(SIZE % THREADS != 0)
		quantum ++;

#pragma omp parallel num_threads(THREADS)                   
	{
		int t_no, i, j;
		int temp =0;
		int k=0;
		t_no = omp_get_thread_num();
		int repeat = REPEAT;
		while(repeat --)
		{
			for(i=(t_no*quantum); i<((t_no+1)*quantum); i++)
			{
				temp =0;
				k=0;
				while(k != SIZE)
				{
					for(j=0; j<SIZE; j++)
					{
						temp += (a[i][j] * b[j][k]);
					}
					c[i][k] = temp;
					temp =0;
					k++;
				}
			}

		}
	}

#endif

	int i,j;

#ifdef NORMAL_PROCESSING
	int k,l=0;
	int temp = 0;
	for(i=0; i<SIZE; i++)
	{
		temp =0;
		k=0;
		while(k != SIZE)
		{
			for(j=0; j<SIZE; j++)
			{
				temp += (a[i][j] * b[j][k]);
			}
			c[i][k] = temp;
			temp =0;
			k++;
		}
	}


#endif


#ifdef PRINT

	for(i=0; i<SIZE; i++)
	{
		for(j=0; j<SIZE; j++)
		{
			printf("%d ", c[i][j]);
		}
		printf("\n");
	}
#endif

}



















