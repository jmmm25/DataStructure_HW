#include<stdio.h>
#include<stdlib.h>

#define BLACK 0
#define RED 1
#define FALSE 0
#define TRUE 1
#define MOVE(list)					(list = list->post)
#define APPEND(list, tail)			((tail)->post = (list), MOVE(tail))

//define useful function.

typedef struct _rb_node Node;
typedef struct _rb_node{
    int Element;
    int Color;
    Node* Left;
    Node* Right;
}Node;

typedef struct _rb_tree{
    Node* data;
}RBtree;

typedef struct _linked_list{
    Node *dataPtr;
    struct _linked_list *post;
}List;


//declare used structure in main function.

void Print_LevelOrder(RBtree *src);
void print_Inorder(Node* src);
Node* LL_Rotate(Node* prnt);
Node* RR_Rotate(Node* prnt);
Node* LR_Rotate(Node* prnt);
Node* RL_Rotate(Node* prnt);
RBtree* Init_RBtree();
void Insert_RB_Node(RBtree *src, int input);
Node* Insert_RB(Node* prnt, Node** newNode, int* flag);
Node* Init_Node(int input);     //새로운 노드 초기화


////////////////
    
    int main(int argc, char* argv[]){
        FILE *fi = fopen(argv[1], "r");
        int i=0;
        RBtree* my_Tree = Init_RBtree();
        
        while(!feof(fi)){
            fscanf(fi,"%d ", &i);
            Insert_RB_Node(my_Tree, i);
        }
        
        Print_LevelOrder(my_Tree);
        free(my_Tree);
        fclose(fi);
        return 0;
        
    }
    /////////////////////
    
    RBtree* Init_RBtree(){
        RBtree* newTree =(RBtree*)malloc(sizeof(RBtree));
        newTree->data = NULL;
        return newTree;
    }
        /// to point tree's root
    Node* Init_Node(int input){
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->Left = NULL;
        newNode->Right= NULL;
        newNode->Element = input;
        newNode->Color = RED;
        return newNode;
    }
    // to initiate node.
    
    Node* LL_Rotate(Node* prnt){
        Node* newPrnt;
        newPrnt = prnt->Left;
        newPrnt->Color = BLACK;
        prnt->Left = newPrnt->Right;
        newPrnt->Right = prnt;
        prnt->Color = RED;
        return newPrnt;
        
    }
    //if case is LL, rotate right.
    Node* RR_Rotate(Node* prnt){
        Node* newPrnt;
        newPrnt = prnt->Right;
        newPrnt->Color = BLACK;
        prnt->Right = newPrnt->Left;
        newPrnt->Left = prnt;
        prnt->Color = RED;
        
        return newPrnt;
    }
    //if case is RR, rotate left.
    Node* LR_Rotate(Node* prnt){
        prnt->Left = RR_Rotate(prnt->Left);
        return LL_Rotate(prnt);
    }
    //if case is LR, rotate left and then rotate right.
    
    Node* RL_Rotate(Node* prnt){
        prnt->Right = LL_Rotate(prnt->Left);
        return RR_Rotate(prnt);
    }

    //if case is RL, rotate right, and then rotate left.
    void Insert_RB_Node(RBtree *src, int input){
        int flag = FALSE;
        Node* newNode = Init_Node(input);
        src->data = Insert_RB(src->data, &newNode, &flag);
        src->data->Color = BLACK;
    }
    //change root'color to black.
    
    Node* Insert_RB(Node* prnt, Node **newNode, int *flag){
        if(!prnt){  //if prnt == NULL
            *flag = FALSE;
            return *newNode;
        }
        else if(prnt->Element > (*newNode)->Element){
            prnt->Left = Insert_RB(prnt->Left, newNode, flag);
            if(!*flag)
            { //플래그 == FALSE 0일떄
                if(prnt->Left == (*newNode))
                {
                    if(prnt->Color == BLACK)
                        *flag = TRUE;
                }
                else{
                    if(prnt->Right && prnt->Right->Color == RED){
                        prnt->Right->Color = BLACK;
                        prnt->Left->Color = RED;
                        prnt->Color = RED;
                        *newNode = prnt;
                        return prnt;
                    }
                    else if(prnt->Left->Left == (*newNode))
                        prnt = LL_Rotate(prnt);
                    else //if(prnt->Left->Right ==(*newNode)
                        prnt = LR_Rotate(prnt);
                    *flag = TRUE;
                }				
            }
        }
        
        else{
            prnt->Right = Insert_RB(prnt->Right, newNode, flag);
            if(!*flag){
                if(prnt->Right == (*newNode)){
                    if(prnt->Color == BLACK)
                        *flag = TRUE;
                }
                else{
                    if(prnt->Left && prnt->Left->Color == RED){
                        prnt->Left->Color = BLACK;
                        prnt->Right->Color = BLACK;
                        prnt->Color = RED;
                        *newNode = prnt;
                        return prnt;
                    }
                    else if(prnt->Right->Right == (*newNode))
                        prnt = RR_Rotate(prnt);
                    else
                        prnt = RL_Rotate(prnt);
                    *flag = TRUE;
                }	
            }
        }
        return prnt;
    }
    //use BST Tree algorithm, and then first, insert integer in Node.
    //and then, if tree's blance is unbalance, change node's color and rotate tree's node.


/*
void print_Inorder(Node* src){
    if(src){
        print_Inorder(src->Left);
        if(src->Color == 1)       // 1 is RED.
            printf("%d(R) ",src->Element);
        else
            printf("%d(B) ",src->Element);
        print_Inorder(src->Right);
    }
}
//print inorder traversal.
*/



void Print_LevelOrder(RBtree *src)
{
    List *newQue = NULL, *curQue = NULL;
    List *queHead = NULL, *queTail = NULL;
    int level = 0;
    if(!src->data)
        return;
    queHead = (List*)malloc(sizeof(List));
    queHead->dataPtr = NULL;
    queHead->post = curQue =(List*)malloc(sizeof(List));
    curQue->dataPtr = src->data;
    curQue->post = NULL;
    while(queHead->post)
    {
        curQue = queHead->post;
        queHead->post = NULL;
        queTail = queHead;
        printf("level(%d) : ", ++level);
        while(curQue)
        {
            if(curQue->dataPtr)
            {
                newQue = (List*)malloc(sizeof(List));
                newQue->post= NULL;
                newQue->dataPtr	= curQue->dataPtr->Left;
                APPEND(newQue, queTail);
            
                newQue				= (List*)malloc(sizeof(List));
                newQue->post		= NULL;
                newQue->dataPtr	= curQue->dataPtr->Right;
                APPEND(newQue, queTail);
            }
            newQue = curQue;
            if(!curQue->dataPtr)
                printf("N ");
            else if(curQue->dataPtr->Color == RED)
                printf("%d(R) ", newQue->dataPtr->Element);
            else if(curQue->dataPtr->Color == BLACK)
                printf("%d(B) ", newQue->dataPtr->Element);
            MOVE(curQue);
            free(newQue);
        }
        printf("\n");
    }
    free(queHead);
}

//print level by level tree.

