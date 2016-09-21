//
//  main.c
//  Queue
//
//  Created by JEONGMIN on 2016. 4. 27..
//  Copyright © 2016년 JEONGMIN. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>


typedef int ElementType;
struct CircularQueue;
typedef struct CircularQueue* Queue;
struct CircularQueue{
    int Capacity;       //maxmimum.
    int Front;
    int Rear;
    int Size;   // now Queues'size
    ElementType *Key;
}QueueRecord;

Queue CreateQueue(int Max);
void Enqueue(ElementType X, Queue Q);
void Dequeue(Queue Q);
int IsFull(Queue Q);
int IsEmpty(Queue Q);
void PrintFront(Queue Q);
void PrintRear(Queue Q);
void DeleteQueue(Queue Q);

int main(int argc, char* argv[]){
    
    Queue my_Q = NULL;
    FILE *fp1 = fopen(argv[1], "r"); //to read expr_input.txt
    char ch;
    ElementType su;
    
    while((ch = fgetc(fp1)) != EOF){
        
        switch(ch){
                
            case 'n':
                fscanf(fp1,"%d",&su);
                my_Q = CreateQueue(su);
                break;
                
            case 'e':
                fscanf(fp1,"%d",&su);
                Enqueue(su, my_Q);
                break;
                
            case 'd':
                Dequeue(my_Q);
                break;
                
            case 'f':
                PrintFront(my_Q);
                break;
                
            case 'r':
                PrintRear(my_Q);
                break;
                
        }//switch end
    }// while end.
    
    DeleteQueue(my_Q);
    
    
    
    return 0;
}

Queue CreateQueue(int Max){
    Queue Q;
    Q= (Queue)malloc(sizeof(struct CircularQueue));
    Q->Key = (int*)malloc(sizeof(int) * Max);
    
    if(Q ==NULL)
        printf("Out of Space\n");
    
    else{
        Q->Front = 1;
        Q->Rear = 0 ;
        Q->Size = 0;
        Q->Capacity = Max;
    }
    return Q;
}

void Enqueue(ElementType X , Queue Q){
    
    if(IsFull(Q))
        printf("insertion failed, queue is full\n");
    
    else{
        Q->Size++;
        Q->Rear = (Q->Rear+1)% Q->Capacity;
        Q->Key[Q->Rear] = X;
    }
}

void Dequeue(Queue Q){
    
    if(IsEmpty(Q))
        printf("deletion failed, queue is empty\n");
    
    else{
        Q->Size--;
        Q->Front++;
    }
}

int IsFull(Queue Q){
    return Q->Size == Q->Capacity;  // if size is Capacity, return 1
}

int IsEmpty(Queue Q){
    return Q->Size == 0;
}

void PrintFront(Queue Q){
    if(Q->Size == 0)
        printf("printfront error, queue is Empty\n");
    else
        printf("%d\n",Q->Key[Q->Front]);
}

void PrintRear(Queue Q){
    if(Q->Size == 0)
        printf("printrear error, Queue is Empty\n");
    else
        printf("%d\n", Q->Key[Q->Rear]);
}

void DeleteQueue(Queue Q){
    
    free(Q->Key);
    free(Q);
}

