#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct GraphNode
{
    int vertex;         // vertex number
    struct GraphNode *link;
};

struct GraphNode *graph[MAX_VERTICES];

int visited[MAX_VERTICES] = { 0 };

int stack[MAX_VERTICES];
int top = -1;

void push(int v)
{
    if (top == MAX_VERTICES - 1)
    {
        printf("Stack is full\n");
        return;
    }
    top++;
    stack[top] = v;
}

int isStackEmpty()
{
    if (top == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int pop()
{
    int temp = 0;
    if (top == -1)
    {
        printf("stack is empty\n");
        return -1;
    }
    temp = stack[top];
    top--;
    return temp;
}

void insert_vertex(int v)
{
    graph[v] = (struct GraphNode *)malloc(sizeof(struct GraphNode));
    (graph[v])->vertex = v;
    graph[v]->link = NULL;
}

void addEdge(int v1, int v2)
{
    struct GraphNode *new_one = (struct GraphNode *)malloc(sizeof(struct GraphNode));
    struct GraphNode *cur = graph[v1];
    //    struct GraphNode *next;
    
    new_one->vertex = v2;
    new_one->link = 0;
    
    if (cur->link == 0)   // if not connected
    {
        cur->link = new_one;
    }
    else   // link newnode
    {
        new_one->link = cur->link;
        cur->link = new_one;
    }
    
    return;
}

// find adjacent vertex
int findNextVertex(int v)
{
    struct GraphNode *cur = graph[v];
    
    while (cur != 0)
    {
        if (visited[cur->vertex] == 0)
        {
            return cur->vertex;
        }
        cur = cur->link;
    }
    return -1;
}

void doDFS(int v1, int v2)
{
    printf("%d ", v1);
    visited[v1] = 1;
    push(v1);
    
    while (isStackEmpty() == 0)
    {
        int next_vertex = -1;
        next_vertex = findNextVertex(stack[top]);
        
        if (next_vertex == -1)   // if not exist adjacent vertex, pop
        {
            pop();
        }
        else
        {
            printf("%d ", next_vertex);
            visited[next_vertex] = 1;
            push(next_vertex);
        }
        
        if (stack[top] == v2)
        {
            break;
        }
    }
    printf("\n");
    
    if (graph[v2] == 0)
    {
        printf("Can not find %d\n", v2);
    }
}

int main(int argc, char *argv[])
{
    int i;
    int x = 0;
    int u, v = 0;
    int a=0, b = 0;
    char end1 = 0;
    char end2 = 0;
    FILE *fp;
    for (i = 0; i < MAX_VERTICES; i++)
    {
        graph[i] = NULL;
    }
    fp = fopen(argv[1], "r");
    do
    {
        fscanf(fp, "%d", &x);
        printf("%d ", x);
        insert_vertex(x);
        end1 = fgetc(fp);
    } while (end1 != '\n' && end1 != '\r');
    printf("\n");
    do
    {
        fscanf(fp, "%d-%d", &u, &v);
        addEdge(u, v);
        printf("%d-%d ", u, v);
        end2 = fgetc(fp);
    } while(end2 != '\n' && end2 != '\r');
    printf("\n");
    while (!feof(fp))
    {
        fscanf(fp, "%d-%d ", &a, &b);
        printf("%d-%d\n", a, b);
    }
    printf("DFS(iterative) print : ");
    doDFS(a, b);
    fclose(fp);
    return 0;
}