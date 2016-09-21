#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX_CAPACITY 100

typedef char ElementType;	// ElementType is char.
typedef struct StackNode* Stack;	//pointer to stacknode.
typedef struct StackNode {

	ElementType *key;
	int TopOfStack;
	int MaxElement;

}StackNode;		//uni data structure.

Stack Create_Stack(int max);
void Make_Empty(Stack S);	
void Push(ElementType X, Stack S);
void Pop(Stack S);
int IsEmpty(Stack S);
int IsFull(Stack S);
ElementType TopAndPop(Stack S); //Pop operate. and then print element. 
int Priority(ElementType X);	//set priority, return 1,2,3.
void Compare_Priority(ElementType X, Stack S);





int main(int argc, char* argv[]) {	//Call the expr_input.txt

	FILE *fp1 = fopen(argv[1], "r");	// Read expr_input.txt
	ElementType* expr;		//pointer expr.
	ElementType ch, temp;		
	int index = 0, i;
	int woosun, instack;
	Stack my_Stack;		//Pointer struct  my_Stack 
	my_Stack = Create_Stack(MAX_CAPACITY);	// my_Stack's Size = 100;
	expr = (ElementType*)malloc(sizeof(ElementType)*MAX_CAPACITY);
	//Set dynamic allocation.
	
	
	while ((ch = fgetc(fp1)) != EOF) {
		expr[index] = ch;
		index++;
	}		// If expr_input.txt isn't finish, input character to array.
	printf("original infix form: ");
	for (i = 0; i < index; i++)
		printf("%c", expr[i]);	//print all array.
	printf("\n");
	printf("converted postfix form : ");
	index = 0;
	while (expr[index] != '#') {
		woosun = Priority(expr[index]);	// Call the Priority func.
		if (woosun == 0) {

			printf("%c", expr[index]);

		}		// if woosun is '0', print operand.

		else if (woosun == 1 || woosun == 2) {

			

			if (IsEmpty(my_Stack)) {
				Push(expr[index], my_Stack);
			}	// if Stack is empty, Push the character.
			else {
				Compare_Priority(expr[index], my_Stack);
			}	// call the Compare_Priority.
		}
			
	else if (woosun == 3) {		// meet operator '(',')'.

		if (expr[index] == '(') {
		Push(expr[index], my_Stack);	//meet '(', push a character.
			index++;
	
		while (expr[index] != ')') {
		woosun = Priority(expr[index]);
		instack = Priority(my_Stack->key[my_Stack->TopOfStack]);	// meet ')' , calculate priority, and then input return'value to woosun and instack. 
					
		if (woosun == 0) {
			printf("%c", expr[index]);
			}	//meet operan, print it.

		else if (woosun == 1 || woosun == 2) {
		// meet *,/,%,+,-

		if (instack >= woosun) {
		if (my_Stack->key[my_Stack->TopOfStack] == '(')
			Push(expr[index], my_Stack);
		//meet '(', Push it in Stack.

		else {
		temp = TopAndPop(my_Stack);	//Call the TopAndPop func.
		printf("%c", temp);
		Push(expr[index], my_Stack);	//Call the Push func.
		}
	}
		else if (instack < woosun) {
		Push(expr[index], my_Stack);
			}
		}
		index++;
		}
		}
		
		if (expr[index] == ')') {
			//meet ')'
		while (my_Stack->key[my_Stack->TopOfStack] != '(') {
			temp = TopAndPop(my_Stack);
			printf("%c", temp);
			}
			Pop(my_Stack);
			}
		}	// if it can't meet '(', Print and Pop Stack's value
		index++;
	}

	while (!IsEmpty(my_Stack)) {
		temp = TopAndPop(my_Stack);
		printf("%c", temp);
	}// if stack is not empty, print and Pop in Stack.
	printf("%c", expr[index]);
	printf("\n");



	fclose(fp1);		//Close expr_input.txt
	free(my_Stack ->key);	//Free dynamic allocation.
	free(expr);		//free dynamic allocation.
	return 0;

	}

	Stack Create_Stack(int max) {	// Create Stack func.

		Stack S;
		S = (Stack)malloc(sizeof(StackNode));
		//declare allocation dynamic to Stack.
		if (S == NULL)
			printf("Out of Space!!!!");

		S->MaxElement = max;
		S->key = (ElementType*)malloc(sizeof(ElementType)*max);
		// declare dynamic allocation to pointer key.
		Make_Empty(S);

		return S;
	}

	void Make_Empty(Stack S) {
		S->TopOfStack = -1;

	}	// initialize Stack.

	void Push(ElementType X, Stack S) {
		if (IsFull(S))
			printf("Stack is FULL!!!");
		else
			S->key[++S->TopOfStack] = X;
	}	// plus Top in the stack, input X

	void Pop(Stack S) {
		if (IsEmpty(S)) {
			printf("Stack is Empty");
		}
		else {
			S->TopOfStack--;
		}
	}		//Pop Stack's top, and then minus 1 top's order.

	ElementType TopAndPop(Stack S) {
		if (IsEmpty(S)) {
			printf("Stack is Empty!!");
		}
		else {
			return S->key[S->TopOfStack--];
		}
	}	// Pop and Print value in the stack.
	int IsEmpty(Stack S) {

		return S->TopOfStack == -1;	//compare a==b, return 1 or b
	}
	int IsFull(Stack S) {
		return S->TopOfStack == (MAX_CAPACITY - 1);
	}


	int Priority(ElementType X) {	// set priority.
		switch (X) {
		case '(':
			return 3;
		case ')':
			return 3;
		case '*':
			return 2;
		case '/':
			return 2;
		case '%':
			return 2;
		case '+':
			return 1;
		case '-':
			return 1;
		default:
			return 0;

		}
	}

	void Compare_Priority(ElementType X, Stack S) {
//compare in_stack and in_coming.
		int in_Stack, in_Coming;
		char result;

		while (1) {
			in_Stack = Priority(S->key[S->TopOfStack]);
			in_Coming = Priority(X);

			if (in_Stack >= in_Coming) {
				result = TopAndPop(S);
				printf("%c", result);
			}
			else {
				Push(X, S);
				break;
				//push in_Stack.


			}

		}
	}
