#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double sigma(double **A, double** T, int i, int j, int N)
{
	double sum = 0;
	
		    if(i!=1 && i!=N && j!=1 && j!=N)//case1
			{
				sum += A[(i-1)*N+j-1][i*N+j-1]*T[i][j-1];//right
				sum += A[(i-1)*N+j-1][(i-2)*N+j-1]*T[i-2][j-1];//left
				sum += A[(i-1)*N+j-1][(i-1)*N+j]*T[i-1][j];//upper
				sum += A[(i-1)*N+j-1][(i-1)*N+j-2]*T[i-1][j-2];//lower
				sum += A[(i-1)*N+j-1][(i-1)*N+j-1]*T[i-1][j-1];//middle
				//b[(j-1)*N+i-1]=0;//research needed on the reason why b's index is reversed.
				return sum;
			}
			else if(i==1 && j==N)//case2
			{
			    sum += A[(i-1)*N+j-1][i*N+j-1]*T[i][j-1];//right
				sum += A[(i-1)*N+j-1][(i-1)*N+j-2]*T[i-1][j-2];//lower
				sum += A[(i-1)*N+j-1][(i-1)*N+j-1]*T[i-1][j-1];//middle
				//b[(j-1)*N+i-1]=Tleft+Tupper;
				return sum;
			}
			else if(i==1 && j==1)//case3
			{
				sum += A[(i-1)*N+j-1][i*N+j-1]*T[i][j-1];//right
		     	sum += A[(i-1)*N+j-1][(i-1)*N+j]*T[i-1][j];//upper
				sum += A[(i-1)*N+j-1][(i-1)*N+j-1]*T[i-1][j-1];//middle
				//b[(j-1)*N+i-1]=Tleft+Tlower;
				return sum;
		    }
			else if(i==N && j==N)//case4
			{
			
				sum += A[(i-1)*N+j-1][(i-2)*N+j-1]*T[i-2][j-1];//left
				sum += A[(i-1)*N+j-1][(i-1)*N+j-2]*T[i-1][j-2];//lower
				sum += A[(i-1)*N+j-1][(i-1)*N+j-1]*T[i-1][j-1];//middle
				//b[(j-1)*N+i-1]=Tupper+Tright;
				return sum;
			}
			else if(i==N && j==1)//case5
			{
			
				sum += A[(i-1)*N+j-1][(i-2)*N+j-1]*T[i-2][j-1];//left
				sum += A[(i-1)*N+j-1][(i-1)*N+j]*T[i-1][j];//upper
				sum += A[(i-1)*N+j-1][(i-1)*N+j-1]*T[i-1][j-1];//middle
				//b[(j-1)*N+i-1]=Tright+Tlower;
				return sum;
			}
			else if(i==1 && j!=N && j!=1)//case6
			{
				sum += A[(i-1)*N+j-1][i*N+j-1]*T[i][j-1];//right
				sum += A[(i-1)*N+j-1][(i-1)*N+j]*T[i-1][j];//upper
				sum += A[(i-1)*N+j-1][(i-1)*N+j-2]*T[i-1][j-2];//lower
				sum += A[(i-1)*N+j-1][(i-1)*N+j-1]*T[i-1][j-1];//middle
				//b[(j-1)*N+i-1]=Tleft;
				return sum;
			}
			else if(i==N && j!=N && j!=1)//case7
			{
		
				sum += A[(i-1)*N+j-1][(i-2)*N+j-1]*T[i-2][j-1];//left
				sum += A[(i-1)*N+j-1][(i-1)*N+j]*T[i-1][j];//upper
				sum += A[(i-1)*N+j-1][(i-1)*N+j-2]*T[i-1][j-2];//lower
				sum += A[(i-1)*N+j-1][(i-1)*N+j-1]*T[i-1][j-1];//middle
				//b[(j-1)*N+i-1]=Tright;
				return sum;
			}
			else if(j==N && i!=1 && i!=N)//case8
			{
				sum += A[(i-1)*N+j-1][i*N+j-1]*T[i][j-1];//right
				sum += A[(i-1)*N+j-1][(i-2)*N+j-1]*T[i-2][j-1];//left
				sum += A[(i-1)*N+j-1][(i-1)*N+j-2]*T[i-1][j-2];//lower
				sum += A[(i-1)*N+j-1][(i-1)*N+j-1]*T[i-1][j-1];//middle
				//b[(j-1)*N+i-1]=Tupper;
				return sum;
			}
			else if(j==1 && i!=1 && i!=N)//case9
			{
				sum += A[(i-1)*N+j-1][i*N+j-1]*T[i][j-1];//right
				sum += A[(i-1)*N+j-1][(i-2)*N+j-1]*T[i-2][j-1];//left
				sum += A[(i-1)*N+j-1][(i-1)*N+j]*T[i-1][j];//upper
				sum += A[(i-1)*N+j-1][(i-1)*N+j-1]*T[i-1][j-1];//middle
				//b[(j-1)*N+i-1]=Tlower;
				return sum;
			}
			else
			printf("error%d%d:none of cases chosen!\n",i,j);
}

void print2Darray(double **array, int m, int n)
{
	int i, j;
	for(i=0;i<m;i++)//마지막에 솔루션을 출력했을 때 위아래가 바뀜 A: 1,1부터 위에서 출력되서 그런것 ,//행과 열이 바뀜....왜? 
	{
		for(j=0;j<n;j++)
		{
			printf(" %5.3f",array[j][i]);
		}
		printf("\n");
	}
		
}

void print1Darray(double *array, int m)
{
	int i;
	for(i=0;i<m;i++)
	{
		printf(" %5.3f\n",array[i]);
	}
		
}
