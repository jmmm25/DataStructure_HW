#include <stdio.h>
void swap(int *a,int *b);
int main(void){
	int a[2];	//create int array
	int **ppA;	//2D and 1D pointer are created.
	int *pA;
	ppA=&pA;	//input pA's address to Variable ppA. 
	pA=&a[0];	
	
	int b[2];	//create int array b[2].
	int **ppB;	//2D and 1D pointer are created.
	int *pB;
	ppB= &pB;
	pB=&b[0];	//input b[0]'s address to pB.

	printf("enter 2 integers\n");
	scanf("%d %d:", &a[0],&b[0]);
	printf("you entered\n%d, %d \n", **ppA,**ppB);
	swap(&a[0],&b[0]); // call swap function.
	printf("after swapping\n%d, %d", **ppA, **ppB);
	printf("\n");

	
	return 0;
}

//Create swap function.

void swap(int *a,int *b){
int temp;
temp = *a;
*a=*b;
*b=temp;
}


