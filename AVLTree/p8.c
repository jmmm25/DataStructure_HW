//
//  main.c
//  AVL
//
//  Created by JEONGMIN on 2016. 4. 29..
//  Copyright © 2016년 JEONGMIN. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>

struct AVLNode;
typedef struct AVLNode* Position;
typedef struct AVLNode* AVLTree;
typedef int ElementType;
typedef struct AVLNode{
    ElementType Element;
    AVLTree Left;
    AVLTree Right;
    int Height;
}AVLNode;

Position SingleRotateWithLeft( Position k2 );
Position SingleRotateWithRight( Position k2 );
Position DoubleRotateWithLeft( Position k3 );
Position DoubleRotateWithRight( Position k3 );
AVLTree Insert( ElementType X, AVLTree T );
int Height(Position P);
int Max(ElementType X, ElementType Y);
void printInorder(AVLTree T);

int main(int argc, char * argv[]) {
    
    FILE *fp1 = fopen(argv[1] , "r");
    
    int num;
    AVLTree my_T =NULL;
    
    while(!feof(fp1)){
        fscanf(fp1,"%d", &num);
        my_T = Insert( num, my_T);
    }
    printInorder(my_T);
    printf("\n");
    fclose(fp1);
    free(my_T);
    
    return 0;
}

int Height(Position P){
    if(P == NULL)
        return -1;
    else
        return P->Height;
}       //calculate tree's height.

Position SingleRotateWithLeft( Position k2 ){
    Position k1;
    
    k1 = k2 ->Left;
    k2->Left = k1 -> Right;
    k1->Right = k2;
    
    k2->Height = Max(Height(k2->Left), Height(k2->Right))+1;
    k1->Height = Max(Height(k1->Left), k2->Height)+1;
    return k1;
}       //if AVLtree is LL, rotate right.

Position SingleRotateWithRight( Position k2){
    Position k1;
    
    k1 = k2 ->Right;
    k2->Right = k1->Left;
    k1->Left = k2;
    
    k2->Height = Max(Height(k2->Right), Height(k2->Left))+1;
    k1->Height = Max(Height(k1->Right), k2->Height)+1;
    
    return k1;
}
//if AVLtree is RR, rotate Left.

Position DoubleRotateWithLeft( Position k3 ){
    
    k3->Left = SingleRotateWithRight(k3->Left);
    return SingleRotateWithLeft(k3);
    
}
//if AVLtree is RL, rotate right. and then left.

Position DoubleRotateWithRight( Position k3 ){
    
    k3->Right = SingleRotateWithLeft(k3->Right);
    return SingleRotateWithRight(k3);
}

AVLTree Insert( ElementType X, AVLTree T ) {
    if(T == NULL){
        T = malloc(sizeof(struct AVLNode));
        if(T == NULL)
            printf("out of space\n");
        else{
            T->Element = X;
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
    }           //initiate AVLTree.
    else if ( X < T->Element ) {
        T->Left = Insert( X, T->Left ); /* BST*/
        if( Height( T->Left ) - Height( T->Right ) == 2 ){
            if( X < T->Left->Element )
                T = SingleRotateWithLeft( T );
            else
                T = DoubleRotateWithLeft( T );
        }
    }       //if X'value is less than root'value, perform this conditional text.
    else if( X > T->Element ) {
        T->Right = Insert( X, T->Right );
        if( Height( T->Right ) - Height( T->Left ) == 2 ){
            if( X > T->Right->Element )
                T = SingleRotateWithRight( T );
            else
                T = DoubleRotateWithRight( T );
        }
    }   //if X'value is larger than root'value, perform this conditional text.
    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
    return T;
}
//this function is insert func. insert X in AVLtree.

void printInorder(AVLTree T){
    if(T){
        printInorder(T->Left);
        printf("%d ",T->Element);
        printInorder(T->Right);
    }
}
//print inorder traversal.

int Max(ElementType X, ElementType Y){
    if(X>Y)
        return X;
    else
        return Y;
}

// return Maximum value.

