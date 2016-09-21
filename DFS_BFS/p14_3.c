#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct GraphNode
{
    int vertex;         // vertex 번호
    struct GraphNode *link;
};

struct GraphNode *graph[MAX_VERTICES];

int visited[MAX_VERTICES] = { 0 };

int head = 0;
int tail = 0;
int que[MAX_VERTICES];

void enque(int v)
{
    if ((tail + 1) % MAX_VERTICES == head)
    {
        printf("Queue is full\n");
        return;
    }
    que[tail] = v;
    tail = (tail + 1) % MAX_VERTICES;
}

int isQueEmpty()
{
    if (head == tail)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int deque()
{
    int temp = -1;
    if (isQueEmpty() == 0)
    {
        temp = que[head];
        head = (head + 1) % MAX_VERTICES;
    }
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
    struct GraphNode *next;
    
    new_one->vertex = v2;
    new_one->link = 0;
    
    if (cur->link == 0)   // v1에 아무 것도 붙어있지 않는 상태
    {
        cur->link = new_one;
    }
    else
    {
        new_one->link = cur->link;
        cur->link = new_one;
    }
    
    return;
}

void addAjacentNonVisitedVertexToQue(int v)
{
    struct GraphNode *cur = graph[v];
    
    while (cur != 0)
    {
        if (visited[cur->vertex] == 0)
        {
            enque(cur->vertex);
        }
        cur = cur->link;
    }
}

void doBFS(int v1, int v2)
{
    enque(v1);
    
    while (isQueEmpty() == 0)
    {
        int k;
        
        k = deque();
        
        if (visited[k] == 0)
        {
            printf("%d ", k);
            visited[k] = 1;
            addAjacentNonVisitedVertexToQue(k);
        }
        if (k == v2)
        {
            break;
        }
    }
    printf("\n");
    
    if (graph[v2] == 0)
    {
        printf("can not found %d\n", v2);
    }
}

int main(int argc, char *argv[])
{
    int i;
    int x = 0;
    int u, v = 0;
    int a=0, b = 0;
//    char ch = 0;
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
    } while (end2 != '\n' && end2 != '\r');
    printf("\n");
    
    while (!feof(fp))
    {
        fscanf(fp, "%d-%d ", &a, &b);
        printf("%d-%d\n", a, b);
    }
    printf("BFS result print : ");
    doBFS(a, b);
    
    fclose(fp);
    return 0;
}