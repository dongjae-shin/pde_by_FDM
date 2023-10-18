#include <stdio.h>
//                    | A        |A's row     | x    |x's row |row  |N
double sigma(double (*ptrA)[3], int m, double *ptrx, int n, int i, int j)
{
	int k;
	double sig = 0;
	for(k=0;k<j;k++)
	{
		sig += ptrA[i-1][k] * ptrx[k];
	}
	
	return sig;
}

double maxvalue(double a, double b, double c)
{
	if(a > b && a > c)
	{
	    return a;	      	
	}
	else if(b > a && b > c)
	{
		return b;
	}
	else if(c > a && c > b)
	{
		return c;
	}
	else
	printf("failed\n");
}
