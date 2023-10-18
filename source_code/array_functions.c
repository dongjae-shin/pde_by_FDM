#include <stdio.h>//header file needs to be included in each unit!
 
void makearray(void) 
{
	
	int m, n, i, j;
	printf("designate the size of array.\n"),scanf("%d %d",&m,&n);
	double array[m][n];//needs malloc();***************************
    for(i=1;i<m+1;i++)
    {
    	for(j=1;j<n+1;j++)
		{
			printf("enter the component(%d,%d)\n",i,j);
			scanf("%d",&array[i][j]);
		}
    
    }
    for(i=1;i<m+1;i++)
    {
    	printf("\n");   //change the row at the last column.
    	for(j=1;j<n+1;j++)
    	{
    		printf("%5d",array[i][j]);  		
    		
    	}
    }
		return;
		getch();
}

void matrix22(double (*ptr)[3],int m)//this function has functions of:1.receives an temporary array(Call-by-Reference) 
                                     //2.receives elements of a matrix(2x2).
                                     //3.shows the matrix 4.replaces temporary array with received matrix.
{
	int i, j;
	double array[3][3];
	for(i=0;i<m;i++)
    {
    	for(j=0;j<3;j++)
		{
			printf("enter the component(%d,%d)\n",i+1,j+1);
			scanf("%le",&array[i][j]);
		}
    
    }
    printf("---------received matrix---------\n");
    for(i=0;i<m;i++)
    {
      	for(j=0;j<3;j++)
    	{
    		printf("%5e ",array[i][j]);  		
    		
        }
    	printf("\n");   //change the row at the last column.
    }
    for(i=0;i<m;i++)
    {
      	for(j=0;j<3;j++)
    	{
          *(ptr[i]+j)=array[i][j];
        }
    }
}




