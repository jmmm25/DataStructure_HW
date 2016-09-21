#include<stdio.h>
#include<stdlib.h>
typedef struct Node* PtrToNode;		//make struct Node* PtrToNode.
typedef int ElementType;
typedef PtrToNode Position;
typedef PtrToNode List;
typedef struct Node {		//struct Node is Node.
	ElementType Element;
	Position Next;
}Node;

//make func.

List MakeEmpty(List H) {
	H = (List)malloc(sizeof(Node));
	H->Element = 0;
	H->Next = NULL;
	return H;
}	//Make pointer Node* variable MakeEmpty. 

int IsEmpty(List L) {
	return L->Next == NULL;
}	// L->Next is NULL.

int IsLast(Position P, List L) {
	return P->Next == NULL;
}	//P->Next is NULL.

Position Find(ElementType X, List L) {
	Position P;
	P = L->Next;
	while (P != NULL && P->Element != X)
		P = P->Next;
	return P;
}
// Making Find func, We can find X. 

Position FindPrevious(ElementType X, List L) {
	Position P;
	P = L;
	while (P->Next != NULL && P->Next->Element != X)
		P = P->Next;
	return P;
}
	// Making FindPrevious function, we can find previous X.

void Insert(ElementType X, List L, Position P) {
	Position TmpCell;
	TmpCell = malloc(sizeof(struct Node));
	if (TmpCell == NULL)
	printf("Out of space!!!!");

	TmpCell->Element = X;
	TmpCell->Next = P->Next;
	P->Next = TmpCell;
}
//Make Insert func.
//Input value X between prev X and post X.

void Delete(ElementType X, List L) {
	Position P, TmpCell;
	P = FindPrevious(X, L);
	if (!IsLast(P, L)) {
		TmpCell = P->Next;
		P->Next = TmpCell->Next;
		free(TmpCell);
	}
}
//To delete X in the list, make Delete func.

void DeleteList(List L) {
	Position P, Tmp;
	P = L->Next;
	L->Next = NULL;
	while (P != NULL) {
		Tmp = P->Next;
		free(P);
		P = Tmp;
	}
}
//To delete all list, make DeleteList func.

void PrintResult(List L) {
	Position P;
	P = L->Next;
	while (P != NULL) 
	{
		printf("key:%d	", P->Element);
		P = P->Next;
	}
	printf("\n");
}
//To print value Key, make PrintResult.

int main(int argc, char* argv[]) {

	FILE *fp1;
	fp1= fopen(argv[1], "r");		//Read lab3_input.txt.
	char symbol;
	ElementType x, y;		//int x,y.
	Position Pos = NULL;
	List Start_List = NULL;		// 2 pointer is NULL.
	Start_List = MakeEmpty(Start_List); //Make pointer struct Start_List. this is header.


	while (!feof(fp1))
	{
		fscanf(fp1, "%c", &symbol);	//read character in the lab3_input.txt.
		switch (symbol)
		{
		case 'i':

			fscanf(fp1, "%d %d", &x, &y);
			Pos = Find(y, Start_List);		//Find y's address, and then input to pointer struct Pos.
			if (y == -1)
				Insert(x, Start_List, Start_List);		//if y is -1, input X to first node in the list.
			else if (Pos != NULL)
				Insert(x, Start_List, Pos);				//if y isn't -1, input X to Y's back in the list.	
			else
				printf("Insertion(%d) Failed : element %d is not in the list\n", x, y); //if x don't exist, print error message.
			break;

		case 'd':

			fscanf(fp1, "%d", &x);			//read integer in the lab3_input.txt
			Pos = Find(x, Start_List);		//Find x's address, and then input to pointer struct Pos.
			if (Pos != NULL)
				Delete(x, Start_List);		//if Pos isn't NULL, Delete x in the list.
			else
				printf("Deletion failed : element %d is not in the list\n", x);	//otherwise, print error message.
			break;

		case 'f':

			fscanf(fp1, "%d", &x);		//read integer in the lab3_input.txt
			Pos = FindPrevious(x, Start_List);		//Find x's previous address, and then input to pointer struct Pos.
			if (Pos->Next == NULL)
				printf("Could not find %d in the list\n", x);	//if struct Pos's next node is NULL, print error message.
			else if (Pos == Start_List)
				printf("Key of the previous node of %d is header.\n", x);	//if struct node is seconde node, print this message.
			else
				printf("Key of the previous node of %d is %d.\n", x,Pos->Element); //otherwise, print previous node's value. 
			break;

		case 'p':
			
			PrintResult(Start_List);	//call PrintResult function.
			break;
		}
	}
	DeleteList(Start_List); //delete all node in the list.
	fclose(fp1); //close lab3_input.txt
	return 0;
}

