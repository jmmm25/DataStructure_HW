#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100


int saver[20]={0,};
int i = 0 ,cnt=0;

struct GraphNode
{
    int vertex;         // vertex nuber
    struct GraphNode *link;
};

struct GraphNode *graph[MAX_VERTICES];

int visited[MAX_VERTICES] = { 0 };
int depth = -1;

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
    
    new_one->vertex = v2;
    new_one->link = 0;
    
    if (cur->link == 0)   // if don't connected
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

void PrintTabs()
{
    int i = depth;
    
    while (i--)
        putchar('\t');
}

// if head to goal, return 1, otherwise return 0
int recursiveDFS(int a, int b)
{
    struct GraphNode *cur;
    struct GraphNode *next;
    ++depth;
    
    printf("%d -> %d", a, b);
    
    if (a == b)   // arrival
    {
        PrintTabs();
        printf("%d arrival\n", a);
        --depth;
        return 1;
    }
    
    // serch
    cur = graph[a];
    printf("  visited %d\n", a);
    visited[a] = 1;
    if(a != 0)
    {
        saver[i++] = a;
    }
    if (cur == 0)
    {
        PrintTabs();
        printf("path isn't %d\n", a);
        --depth;
        return 0;
    }
    
    for (next = cur->link; next != 0; next = next->link)
    {
        if (visited[next->vertex] == 1)
        {
            printf("Already visited %d.\n", next->vertex);
        }
        else
        {
            if (recursiveDFS(next->vertex, b) == 1)
            {
                printf("Before %d\n", a);
                --depth;
                return 1;
            }
        }
    }
    printf("%d No path\n", a);
    --depth;
    return 0;
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
        cnt++;
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
    printf("DFS(recursive) : ");
    printf("\n");
    
    if (recursiveDFS(a, b) == 0)
    {
        printf("No such path exists.\n");
    }
    
    int t=0;
    
    printf("\nDFS recursive result : \n");
    for(t=0; t<= (cnt-1); t++)
    {
        printf("%d ",saver[t]);
    }
    printf("\n");
    fclose(fp);
    return 0;
}