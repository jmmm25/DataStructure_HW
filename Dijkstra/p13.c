#define INF 1000
#define INTMAX 1231292
#define MAX_VERTICES 1000
#define TRUE 1
#define FALSE 0



#include<stdio.h>
#include<stdlib.h>

typedef struct graph_Type
{
	int cnt;
	int matrix[MAX_VERTICES][MAX_VERTICES];
	int distance[MAX_VERTICES];
	int found[MAX_VERTICES];
}gType;

void insertVertex(gType* g, int input, int index);
void insertEdge(gType* g, int u, int v, int w);
void graph_init(gType* g);
void printMat(gType* g);
int findIndex(gType* g, int input);
void insert_vertex(gType* g, int input, int index);
void shortest_path(gType* g, int startNum);
int chooseMin(gType* g);
void showDist(gType* g, int startNum);



int main(int argc, char* argv[])
{
 	
	int vNode=0, sNode=0, eNode=0,w=0, index=1;
	char ch;
	gType graph;
	//graph init.
	graph_init(&graph);
	
	char* inVal = argv[2];


	FILE* fi = fopen(argv[1], "r");
	
	do
	{
		fscanf(fi,"%d",&vNode);
		ch = fgetc(fi);
		insertVertex(&graph, vNode, index); 
		printf("%d ", vNode);
		index++;
	}
	while(ch != '\n' && ch != '\r');
	
	printf("\n");
	while(!feof(fi))
	{
		fscanf(fi, "%d-%d-%d ", &sNode,&eNode,&w);
		insertEdge(&graph, sNode, eNode, w);
		printf("%d-%d-%d ",sNode,eNode,w);
	}
	printf("\n");

	printMat(&graph);
	shortest_path(&graph,atoi(inVal));
	showDist(&graph, atoi(inVal));
	
	fclose(fi);
	return 0;
}

//insert input's val in matrix.
void insertVertex(gType* g, int input, int index)
{
	g->cnt++;
	g->matrix[0][index] = input;
	g->matrix[index][0] = input;

}

//insert weight's value in matrix.
void insertEdge(gType* g, int u, int v, int w)
{
	int row=0, col=0;
	row = findIndex(g,u);
	col = findIndex(g,v);
	g->matrix[row][col] = w;
}
void graph_init(gType* g)
{
	int row=0, col=0,i=0;
	g->cnt = 0;	
	for(row=0;row<=MAX_VERTICES;row++)
	{
		for(col=0;col<=MAX_VERTICES;col++)
		{
			g->matrix[row][col] = INF; 
			//INF is infinite value.
		}
	}
	g->matrix[0][0]=0;
	for(i=0 ; i< MAX_VERTICES; i++)
	{
		g->distance[i] = 0;
		g->found[i] = 0;
	}

}

void printMat(gType* g)
{
	int row=0, col=0;
	for(row =0 ; row<=g->cnt ; row++)
	{
		for(col =0 ; col <= g->cnt ; col++)
		{
			printf("%5d", g->matrix[row][col]);
		}
		printf("\n");

	}

}


int findIndex(gType* g, int input)
{
	int i=0,j=0;
	
	for(i=1; i<=g->cnt; i++)
	{
		if(g->matrix[0][i] == input)
		{
			return i;
		}
	}

	return 0;
}

int chooseMin(gType* g)
{
	int i=0 , min =0, minpos=0;
	min = INTMAX;
	minpos = -1;
	
	for(i=1 ; i<= g->cnt; i++)
	{
		if(g->distance[i] < min && !g->found[i])
		{
			min = g->distance[i];
			minpos = i;
		}
	}
	return minpos;
}




void shortest_path(gType* g, int startNum)
{
	int i=0,u=0,w=0;
	
	for(i=1 ; i<= g->cnt ; i++)
	{
		if(g->matrix[0][i] == startNum)
		{
			u=i;
			break;
		}
	}

	//distance,found initiate.
	for(i=1 ; i<= g->cnt ; i++)
	{
		g->distance[i] = g->matrix[u][i];
		g->found[i] = FALSE;
	}

	g->found[u] = TRUE; //note start vertex's visit signal.
	g->distance[u] = 0;	

	for(i=1; i<=g->cnt; i++)
	{
		u = chooseMin(g);
		g->found[u] = TRUE;

		for(w=1;w<=g->cnt; w++)
		{
			if(!g->found[w])
			{
				if(g->distance[u]+g->matrix[u][w] < g->distance[w])
					g->distance[w] = g->distance[u]+g->matrix[u][w];
			}
		}


	}
}

void showDist(gType* g, int startNum)
{
	int i=0;

	for(i=1;i<=g->cnt; i++)
	{
		printf("%d to %d : cost(%d) \n", startNum, g->matrix[0][i], g->distance[i]);
	}
}



