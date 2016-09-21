//
//  main.c
//  ex
//
//  Created by JEONGMIN on 2016. 5. 23..
//  Copyright © 2016년 JEONGMIN. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>

typedef struct ListNode List;
typedef struct HashTable Table;
struct ListNode
{
    int data;
    List* next;
};

struct HashTable
{
    int TableSize;
    List** TheLists;
};

Table* CreateHash(int size);
List* Find(int input, Table* tbl);
void Insert(int input, Table* tbl);
int Hash(int input, int size);


int main(int argc, char* argv[])
{
    
    FILE *fi = fopen(argv[1], "r");
    int val;
    char ch;
    fscanf(fi, "%d" ,&val);
    
    struct HashTable* myHash = NULL;
    myHash = CreateHash(val);
    
    do
    {
        fscanf(fi, "%d", &val);
        Insert(val, myHash);
	ch = fgetc(fi);
    }
    while( ch != '\n'&& ch != '\r');
    
    while(1)
    {
        if(fscanf(fi,"%d",&val) == EOF)
            break;
        if(Find(val,myHash))
            printf("Find: %d is in hashTable\n",val);
        else
            printf("Find: %d is not in hashTable\n",val);
    }
    
    free(myHash->TheLists);
    free(myHash);
    fclose(fi);
    return 0;
}

Table* CreateHash(int size)
{
    Table* tbl;
    int i=0;
    tbl = (Table*)malloc(sizeof(Table));
    tbl->TableSize = size;
    tbl->TheLists = (struct ListNode**)malloc(sizeof(struct ListNode*)*(tbl->TableSize));
    
    while(1)
    {
        if(i==30)
            break;
        tbl->TheLists[i] = 0;
        i++;
    }
    
    return tbl;
}

List* Find(int input, Table* tbl)
{
	List* P= NULL;
	int index =0;
	index = Hash(input, tbl->TableSize);
	P = tbl->TheLists[index];
	
	while(P!=NULL && P->data != input)
		P = P->next;
	
	return P;
}


void Insert(int input, Table* tbl)
{
    List* Temp;
//    List* L;
    List* Pos;
    
    Pos=  Find(input, tbl);
    
    if(Pos ==NULL)
    {
        Temp = (List*)malloc(sizeof(List));
        Temp->data = input;
        Temp->next = NULL;
        int index = Hash(input, tbl->TableSize);
        if(tbl -> TheLists[index] == NULL)
        {
            tbl->TheLists[index] = Temp;
            return;
        }
        Temp -> next = tbl -> TheLists[index];
        tbl -> TheLists[index] = Temp;
    }
    else
    {
        printf("%d is already in Hash\n",input);
    }
}

int Hash(int input, int size)
{
    return input%size;
}
