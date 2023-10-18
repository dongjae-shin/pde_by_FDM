#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "PDE_solving.h"

int main()
{
	double** T;
	double** Tnew;
	double** A;
	double* b;
	double Tleft, Tright, Tupper, Tlower, deltaT;
	double initialA, initialT, initialb ;
	double eps = 0.0001;
	int i, j, k, l, N;
	printf("enter the number of points where you'll make equation:\n");
	scanf("%d",&N);
	printf("enter the initial value of A's ele.:\n(this must be 'zero'.)\n");
	scanf("%lf",&initialA);
	printf("enter the initial value of T's ele.:\n");
	scanf("%lf",&initialT);
	printf("enter the initial value of b's ele.:\n");
	scanf("%lf",&initialb);
    printf("enter the boudary temperature:\n(left,right,upper,lower)\n");
	scanf("%lf %lf %lf %lf",&Tleft,&Tright,&Tupper,&Tlower);
	
	/*Making 'A' array*/
	A = (double**) malloc(sizeof(double*)*N*N);
	if(A==NULL)
	printf("allocation failed.\n");
	for(k=0;k<N*N;k++)
	{
		A[k] = (double*) malloc(sizeof(double)*N*N);//k번째 행 배열의 주소를 나타내는 T[k]에 각각 N  개의 double형 메모리를 할당. 
		if(A[k]==NULL)
	    printf("allocation failed.\n");
		
		for(l=0;l<N*N;l++)
		{
			A[k][l] = initialA;
		}
	}
	
    /*Making 'T' array*/
	T = (double**) malloc(sizeof(double*)*N);//meaning:"Allocate N memories of the type of 'double*' to the double pointer T"
	                                             //Here, 'N' is the number of the rows of array.  
	                                             //T[k](kth row's address)라는 싱글 포인터를 N개 할당할 수 있는 메모리를 T라는 더
												 //(i.e. we declare a double pointer to save single pointers) 
    if(T==NULL)
	printf("allocation failed.\n");
	for(k=0;k<N;k++)
	{
		T[k] = (double*) malloc(sizeof(double)*N);//k번째 행 배열의 주소를 나타내는 T[k]에 각각 N개의 double형 메모리를 할당. 
		if(T[k]==NULL)
	    printf("allocation failed.\n");
		
		for(l=0;l<N;l++)
		{
			T[k][l] = initialT;
		} 
	}
	/*Initializing 'Tnew' array*/
	Tnew = (double**) malloc(sizeof(double*)*N); 
    if(Tnew==NULL)
	printf("allocation failed.\n");
	for(k=0;k<N;k++)
	{
		Tnew[k] = (double*) malloc(sizeof(double)*N);//k번째 행 배열의 주소를 나타내는 T[k]에 각각 N개의 double형 메모리를 할당. 
		if(Tnew[k]==NULL)
	    printf("allocation failed.\n");
		
		for(l=0;l<N;l++)
		{
			Tnew[k][l] = 0;
		} 
	}
	
	/*Making 'b' array*/
	b = (double*) malloc(sizeof(double)*N*N);
	
    if(b==NULL)
	printf("allocation failed.\n");
	for(k=0;k<N*N;k++)
	{
		b[k] = initialb;
	}

	/*confirming that the dynamic allocation is well performed*/
   // printf("A is initialized as\n");print2Darray(A,N*N,N*N);//this function receives the dynamically allocated array and show it.
   // printf("T is initialized as\n");print2Darray(T,N,N);
   // printf("Tnew is initialized as\n");print2Darray(Tnew,N,N);
   // printf("b is initialized as\n");print1Darray(b,N*N);

	/*T[i+1][j]+T[i-1][j]+T[i][j+1]+T[i][j-1] - 4*T[i][j] == 0*/
	for(i=1;i<N+1;i++)
	{
		for(j=1;j<N+1;j++)
		{   
			if(i!=1 && i!=N && j!=1 && j!=N)//case1
			{
				A[(i-1)*N+j-1][i*N+j-1]=-1;//right
				A[(i-1)*N+j-1][(i-2)*N+j-1]=-1;//left
				A[(i-1)*N+j-1][(i-1)*N+j]=-1;//upper
				A[(i-1)*N+j-1][(i-1)*N+j-2]=-1;//lower
				A[(i-1)*N+j-1][(i-1)*N+j-1]=4;//middle
				b[(j-1)*N+i-1]=0;//research needed on the reason why b's index is reversed.
			}
			else if(i==1 && j==N)//case2
			{
			    A[(i-1)*N+j-1][i*N+j-1]=-1;//right
				//A[(i-1)*N+j-1][(i-2)*N+j-1]=-1;//left
				//A[(i-1)*N+j-1][(i-1)*N+j]=-1;//upper
				A[(i-1)*N+j-1][(i-1)*N+j-2]=-1;//lower
				A[(i-1)*N+j-1][(i-1)*N+j-1]=4;//middle
				b[(j-1)*N+i-1]=Tleft+Tupper;
			}
			else if(i==1 && j==1)//case3
			{
				A[(i-1)*N+j-1][i*N+j-1]=-1;//right
				//A[(i-1)*N+j-1][(i-2)*N+j-1]=-1;//left
				A[(i-1)*N+j-1][(i-1)*N+j]=-1;//upper
				//A[(i-1)*N+j-1][(i-1)*N+j-2]=-1;//lower
				A[(i-1)*N+j-1][(i-1)*N+j-1]=4;//middle
				b[(j-1)*N+i-1]=Tleft+Tlower;
		    }
			else if(i==N && j==N)//case4
			{
				//A[(i-1)*N+j-1][i*N+j-1]=-1;//right
				A[(i-1)*N+j-1][(i-2)*N+j-1]=-1;//left
				//A[(i-1)*N+j-1][(i-1)*N+j]=-1;//upper
				A[(i-1)*N+j-1][(i-1)*N+j-2]=-1;//lower
				A[(i-1)*N+j-1][(i-1)*N+j-1]=4;//middle
				b[(j-1)*N+i-1]=Tupper+Tright;
			}
			else if(i==N && j==1)//case5
			{
				//A[(i-1)*N+j-1][i*N+j-1]=-1;//right
				A[(i-1)*N+j-1][(i-2)*N+j-1]=-1;//left
				A[(i-1)*N+j-1][(i-1)*N+j]=-1;//upper
				//A[(i-1)*N+j-1][(i-1)*N+j-2]=-1;//lower
				A[(i-1)*N+j-1][(i-1)*N+j-1]=4;//middle
				b[(j-1)*N+i-1]=Tright+Tlower;
			}
			else if(i==1 && j!=N && j!=1)//case6
			{
				A[(i-1)*N+j-1][i*N+j-1]=-1;//right
				//A[(i-1)*N+j-1][(i-2)*N+j-1]=-1;//left
				A[(i-1)*N+j-1][(i-1)*N+j]=-1;//upper
				A[(i-1)*N+j-1][(i-1)*N+j-2]=-1;//lower
				A[(i-1)*N+j-1][(i-1)*N+j-1]=4;//middle
				b[(j-1)*N+i-1]=Tleft;
			}
			else if(i==N && j!=N && j!=1)//case7
			{
				//A[(i-1)*N+j-1][i*N+j-1]=-1;//right
				A[(i-1)*N+j-1][(i-2)*N+j-1]=-1;//left
				A[(i-1)*N+j-1][(i-1)*N+j]=-1;//upper
				A[(i-1)*N+j-1][(i-1)*N+j-2]=-1;//lower
				A[(i-1)*N+j-1][(i-1)*N+j-1]=4;//middle
				b[(j-1)*N+i-1]=Tright;
			}
			else if(j==N && i!=1 && i!=N)//case8
			{
				A[(i-1)*N+j-1][i*N+j-1]=-1;//right
				A[(i-1)*N+j-1][(i-2)*N+j-1]=-1;//left
				//A[(i-1)*N+j-1][(i-1)*N+j]=-1;//upper
				A[(i-1)*N+j-1][(i-1)*N+j-2]=-1;//lower
				A[(i-1)*N+j-1][(i-1)*N+j-1]=4;//middle
				b[(j-1)*N+i-1]=Tupper;
			}
			else if(j==1 && i!=1 && i!=N)//case9
			{
				A[(i-1)*N+j-1][i*N+j-1]=-1;//right
				A[(i-1)*N+j-1][(i-2)*N+j-1]=-1;//left
				A[(i-1)*N+j-1][(i-1)*N+j]=-1;//upper
				//A[(i-1)*N+j-1][(i-1)*N+j-2]=-1;//lower
				A[(i-1)*N+j-1][(i-1)*N+j-1]=4;//middle
				b[(j-1)*N+i-1]=Tlower;
			}
			else
			printf("error%d%d:none of cases chosen!\n",i,j);
		}
	}
	printf("values of A, b are substituted well!\n");
    
	/*confirming that substitution is well performed*/
	printf("[A|b] is initialized as\n");
	/*for(k=0;k<N*N;k++)
	{
	    for(l=0;l<N*N;l++)
		{
			printf(" %6.3f",A[k][l]);
		}
		printf(" | %5.3f\n",b[k]);
	}*/
	
	/*Solving AT=b using jacobi method*/
	for(k=0;k<100000;k++)
	{
		deltaT = 0;
	    for(i=1;i<N+1;i++)
	    {
		    for(j=1;j<N+1;j++)
		    {
			    Tnew[i-1][j-1] = T[i-1][j-1] + (b[(j-1)*N+i-1] - sigma(A,T,i,j,N))/A[(i-1)*N+j-1][(i-1)*N+j-1];
			    deltaT += fabs((Tnew[i-1][j-1] - T[i-1][j-1])/T[i-1][j-1]);
		    }
	    }
		
		/*
		x1new = x[0] + (B[0]-sigma(A,3,x,3,1,3))/A[0][0]; //iterative process
		x2new = x[1] + (B[1]-sigma(A,3,x,3,2,3))/A[1][1];
		x3new = x[2] + (B[2]-sigma(A,3,x,3,3,3))/A[2][2];
		*/
		
	    if(deltaT < eps)// convergence criterion
		{
		   	printf("solution converged!!\n");
		   	print2Darray(T,N,N);
		    break;
	    }
	    else if(k==99999)
	        printf("solution not converged!!\n");
		
		for(i=1;i<N+1;i++)
	    {
		    for(j=1;j<N+1;j++)
		    {
			    T[i-1][j-1] = Tnew[i-1][j-1];
			}
	    }
	    printf("iteration %d, change : %5.3f\n",k+1,deltaT);
	}
	

	/*freeing the memories dynamically allocated on 'heap' area*/
	for(k=0;k<N;k++)
	free(T[k]),free(A[k]);
	
	free(T),free(A),free(b);

	return 0;
}
