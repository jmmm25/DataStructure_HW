//
//  main.c
//  Topological
//
//  Created by JEONGMIN on 2016. 5. 27..
//  Copyright © 2016년 JEONGMIN. All rights reserved.
//


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _circularQ queue;

struct _circularQ
{
    int* key;
    int first;
    int rear;
    int qsize;
    int max_q_size;
};

queue* CreateQ(int max);
int isEmpty(queue* q);
int isFull(queue* q);
int deQueue(queue* q);
void enqueue(queue* q, int input);
int arr[100][100];
int in_degree[100];
void topSort(int numVertex);

int main(int argc, char* argv[])
{
    FILE* fi = fopen(argv[1],"r");
    
    char buf[100];
    char node[10];
    char tok[] = " \n";
    char* token = NULL;
    char* saver = NULL;
    int a,b;
    int cnt = 0;
    
    
    fgets(buf, sizeof(buf), fi);
    
   token = strtok(buf,tok);
    cnt++;
    while(token != NULL)
    {
        token = strtok(NULL,tok);
        if(token == NULL)
            break;
        cnt++;
    }
    
    while(fscanf(fi, "%s",node) != EOF) // fscanf can read character by ch '\0'
    {
        saver = strtok(node,"-");
        a = atoi(saver);
        saver = strtok(NULL,"\0");
        b = atoi(saver);
        arr[a][b] = 1;
        in_degree[b]++;
        
    }
    topSort(cnt);
    
    fclose(fi);
    return 0;
    
}


queue* CreateQ(int max)
{
    queue* q;
    q = (queue*)malloc(sizeof(queue));

    q->first = 1;
    q->rear= 0;
    q->max_q_size = max;
    q->qsize = 0;
    q->key = (int*)malloc(sizeof(int)*max);
    
    return q;
}

int isEmpty(queue* q)
{
    return q->qsize == 0;
}

int isFull(queue* q)
{
    return q->qsize == q->max_q_size;
}

int deQueue(queue* q)
{
    int data;
    q->qsize--;
    data = q->key[q->first];
    q->first++;
    q->first = (q->first) % q->max_q_size;
    return data;
}

void enqueue(queue* q, int input)
{
    q->qsize++;
    q->rear = (++q->rear) % (q->max_q_size);
    q->key[q->rear] = input;
}

void topSort(int numVertex)
{
    queue* Q;
    int cnt = 0;
    int* topNum = calloc(numVertex, sizeof(int));
    int i = 0 ,j=0;
    int now;

    
    Q = CreateQ(numVertex);
    
    for( i=1 ; i<=numVertex ; i++)
    {
        if(in_degree[i] == 0)
        {
            enqueue(Q, i);
        }
    }
    
    while(!isEmpty(Q))
    {
        now = deQueue(Q);
        topNum[cnt++] = now;
        
        for (j = 1; j <= numVertex; j++)
        {
            if (j == now)
            {
                continue;
            }
            if (arr[now][j] != 0)
            {
                in_degree[j]--;
                
                if (in_degree[j] == 0)
                {
                    enqueue(Q, j);
                }
            }
        }
    }
    
    if (cnt != numVertex)
    {
        printf("Graph has a cycle\n");
    }
    else
    {
        for (i = 0; i < numVertex; i++)
        {
            printf("%d ", topNum[i]);
        }
        printf("\n");
    }
}





