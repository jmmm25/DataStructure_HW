#include<stdio.h>

int add(int x,int y); //make add, sub, mul, div function.
int sub(int x,int y);
int mul(int x,int y);
int div(int x,int y);
int main(void){

	int (*pf[4])(int,int)={add,sub,mul,div}; //make pointer pf array with 4Size
	int x,y;	//make variable x,y
	int result=0;
	int num1;

	while(1){	
	
	printf("======================\n");
	printf("0. add\n");
	printf("1. sub\n");
	printf("2. mul\n");
	printf("3. div\n");
	printf("4. exit\n");	
	printf("======================\n");
	
	printf("Select Operation :");
	scanf("%d",&num1);
	if(num1==4)			//if num1 is '4', break this program.
	break;
	printf("Input 2 operand: ");
	scanf("%d %d", &x, &y);
	
	if(num1==0){
	result=(*pf[0])(x,y);	//call add function
	printf("Result = %d\n",result);
	}
	else if(num1==1){
	result=(*pf[1])(x,y);	//call sub function
	printf("Result = %d\n",result);
	}
	else if(num1==2){
	result=(*pf[2])(x,y);	//call mul function
	printf("Result = %d\n",result);
	}
	else if(num1==3){
	result=(*pf[3])(x,y);	//call div function
	printf("Result = %d\n",result);
	}

}

}
	//make add, sub, mul, div Function.
	int add(int x,int y){
	return x+y;
	}
	int sub(int x,int y){
	return x-y;
	}
	int mul(int x,int y){
	return x*y;
	}
	int div(int x,int y){
	return x/y;
	}

