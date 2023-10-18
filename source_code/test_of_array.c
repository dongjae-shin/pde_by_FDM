#include <stdio.h>
#include "array.h" //Like this, we can use the header file that we made as we use the standard header file.
//warning: '"' needs using, not '<'


int main()
{
	double A[3][3]={{1, 2, 3}, {4, 5, 6},{7, 8, 9}};
	printf("%5e %5e %5e\n%5e %5e %5e\n%5e %5e %5e\n",A[0][0],A[0][1],A[0][2],A[1][0],A[1][1],A[1][2],A[2][0],A[2][1],A[2][2]);
	matrix22(A,3);
	printf("---------changed matrix---------\n%5e %5e %5e\n%5e %5e %5e\n%5e %5e %5e\n",A[0][0],A[0][1],A[0][2],A[1][0],A[1][1],A[1][2],A[2][0],A[2][1],A[2][2]);
	return 0;
	getch();
}
//definition of function can be placed another unit! kkk
