#define _CRT_SECURE_NO_WARNINGS
#define MAX_CAPACITY 100
#define EMPTY_TOS (-1)
//define const value.

typedef char ElementType;			//ElementType is char.
typedef struct StackNode* Stack;	//pointer to stacknode.
typedef struct StackNode {

	ElementType *key;
	int TopOfStack;
	int MaxElement;

}StackNode;		//uni data structure.

Stack Create_Stack(int max);		//declare main func.
void Make_Empty(Stack S);
void Push(ElementType X, Stack S);
int Pop(Stack S);
int IsEmpty(Stack S);
int IsFull(Stack S);


#include<stdio.h>
#include<stdlib.h>			//to use dynamic allocation.

int main(int argc, char* argv[]) {

	char expr[100];
	char postfix;
	int i, index = 0;
	char su;
	int top2, top1, value = 0;
	FILE *fp1 = fopen(argv[1], "r");			//read expr_input.txt
	Stack my_Stack;			// to use struct Stack.
	my_Stack = Create_Stack(MAX_CAPACITY);			//initiate stack.


	while ((postfix = fgetc(fp1)) != EOF) {		//to save expr_input.txt character.
		expr[index] = postfix;
		index++;
	}
	index--;
	printf("converted postfix form : ");
	for (i = 0; i < index; i++)
		printf("%c", expr[i]);
	printf("\n");
	//print all characters in expr[].

	index = 0;
	while (1) {
		su = expr[index];

		if (su != '*' && su != '/' && su != '+' && su != '-' && su != '%') {
			if (su == '#')
				break;
			value = su - '0';				// because su is ASCII Code. so minus '0'.
			Push(value, my_Stack);
		}
		else {
			top2 = Pop(my_Stack);	// input top's value of stack to top2.
			top1 = Pop(my_Stack);	// input following top's value of stack to top1.

			switch (su) {
			case '+':
				value = top1 + top2;
				Push(value, my_Stack);
				break;
			case '-':
				value = top1 - top2;
				Push(value, my_Stack);
				break;
			case '*':
				value = top1 * top2;
				Push(value, my_Stack);
				break;
			case '%':
				value = top1 % top2;
				Push(value, my_Stack);
				break;
			case '/':
				value = top1 / top2;
				Push(value, my_Stack);
				break;
			} //switch end
		} // else end
		index++;
	}

	printf("evaluation result : %d\n", Pop(my_Stack));		//print terminal value.
	fclose(fp1);
	free(my_Stack->key);
	free(my_Stack);	//release dynamic allocation.
	return 0;

}



Stack Create_Stack(int max) {

	Stack S;
	S = (Stack)malloc(sizeof(StackNode));
	if (S == NULL)
		printf("Out of Space!!!!");

	S->MaxElement = max;
	S->key = (ElementType*)malloc(sizeof(ElementType)*max);	//declare dynamic allocation.	
	Make_Empty(S);	//initiate top -1.

	return S;
}		//create stack.

void Make_Empty(Stack S) {
	S->TopOfStack = EMPTY_TOS;	// EMPTY_TOS is (-1).

}

void Push(ElementType X, Stack S) {
	if (IsFull(S))
		printf("Stack is FULL!!!");
	else
		S->key[++S->TopOfStack] = X;	// push func is save function in stack.
}

int Pop(Stack S) {
	if (IsEmpty(S)) {
		printf("Stack is Empty");
	}
	else 
	{
	return S->key[S->TopOfStack--];	//Pop func return top's value of stack.
}
	return 0;
}

int IsEmpty(Stack S) {

	return S->TopOfStack == EMPTY_TOS;			// if the top's value of stack is -1, return 1.
}
int IsFull(Stack S) {
	return S->TopOfStack == (MAX_CAPACITY - 1);
}			//if top of stack is FULL, return 1.
