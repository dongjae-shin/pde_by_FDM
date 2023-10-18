#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print2Darray(double **array, int m, int n)
{
	int i, j;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			printf(" %5.3f",*(array[i]+j));
		}
		printf("\n");
	}
		
}

void print1Darray(double *array, int m)
{
	int i;
	for(i=0;i<m;i++)
	{
		printf(" %5.3f\n",*(array+i));
	}
		
}

