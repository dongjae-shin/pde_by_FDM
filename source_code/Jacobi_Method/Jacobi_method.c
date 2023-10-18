#include <stdio.h>
#include <math.h>
#include "jacobi.h"


int main() 
{
	double A[3][3] = {{3.0,-0.1,-0.2}, {0.1, 7.0, -0.3}, {0.3, -0.2, 10.0}};
	double B[3] = {7.85, -19.3, 71.4};
	double x[3] = {5.0, 5.0, 5.0};//guessing the solution.
	double x1new, x2new, x3new; 
	double eps = 0.001;
	int i;
	
	
	for(i=0;i<100;i++)
	{
		x1new = x[0] + (B[0]-sigma(A,3,x,3,1,3))/A[0][0]; //iterative process
		x2new = x[1] + (B[1]-sigma(A,3,x,3,2,3))/A[1][1];
		x3new = x[2] + (B[2]-sigma(A,3,x,3,3,3))/A[2][2];
		
		if((fabs((x1new-x[0])/x[0])+abs((x2new-x[1])/x[1])+abs((x3new-x[2])/x[2]))<eps)// convergence criterion
			//if(fabs(maxvalue( x1new-x[0], x2new-x[1], x3new-x[2]))/10< eps)//another criterion
			//****there's 3 types of 'abs'function: abs(int),labs(long),fabs(double)
		 {
		 	printf("solution converged!!\n x1 = %5e\n x2 = %5e\n x3 = %5e\n",x[0],x[1],x[2]);
		 	printf("change : %e\n",fabs((x1new-x[0])/x[0])+abs((x2new-x[1])/x[1])+abs((x3new-x[2])/x[2]));
		    break;
		 }
		else if(i==99)
		 printf("solution not converged!!\n");
		
		x[0]= x1new;
		x[1]= x2new;
		x[2]= x3new;
		printf("iteration %d : x= (%5e, %5e, %5e)\n",i+1,x[0],x[1],x[2]);
	}

	getch();	
	return 0;
}
