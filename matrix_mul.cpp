#include <iostream>
#include <omp.h>

#define PARALLEL_PROCESSING 
//#define NORMAL_PROCESSING 
#define SIZE 1000
int a[SIZE][SIZE]; //= {{1,2,3,4}, {1,2,3,4}, {1,2,3,4}, {1,2,3,4}};
int b[SIZE][SIZE];//= {{1,2,3,4}, {1,2,3,4}, {1,2,3,4}, {1,2,3,4}};
int c[SIZE][SIZE];

int main()
{

#ifdef PARALLEL_PROCESSING
	int num_threads;
	num_threads = omp_get_max_threads();
	printf("NUMBER OF THREADS IN SYSTEM %d\n", num_threads);

#pragma omp parallel                   
	{
		int t_no, i, j;
		int temp =0;
		int k=0;
		t_no = omp_get_thread_num();
		for(i=t_no; i<SIZE; i=i+num_threads)
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





#endif

#ifdef NORMAL_PROCESSING
	int i,j,k,l=0;
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



















