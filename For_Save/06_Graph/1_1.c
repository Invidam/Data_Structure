#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct 
{
	int vn;
	int **matrix;	
}Graph;

Graph *MakeGraph(int);
Graph *NewGraph(int);
void AddEdge(Graph *,int, int);
void DeleteGraph(Graph *);
void ViewNeighbors(Graph *);
void ViewNeighbor(Graph *, int);

int main(void)
{
	Graph *graph;
	graph = MakeGraph(9);
	ViewNeighbors(graph);
	DeleteGraph(graph);
	return 0;
}

Graph *MakeGraph(int vn)
{
	Graph *graph;
	graph = NewGraph(vn);
	AddEdge(graph, 0, 1);
	AddEdge(graph, 0, 2);
	AddEdge(graph, 1, 2);
	AddEdge(graph, 1, 3);
	AddEdge(graph, 2, 4);
	AddEdge(graph, 3, 6);
	AddEdge(graph, 4, 5);
	AddEdge(graph, 4, 6);
	AddEdge(graph, 4, 7);
	AddEdge(graph, 6, 8);
	
	return graph;
}
Graph *NewGraph(int max_vn)
{
	Graph *graph;
	graph = (Graph *)malloc(sizeof(Graph));
	graph->vn = max_vn;
	graph->matrix = (int **)malloc(sizeof(int *)*max_vn);
	for(int i=0; i<max_vn; i++)
	{
		graph->matrix[i] = (int *)malloc(sizeof(int) * max_vn);
		memset(graph->matrix[i],0,sizeof(int) * max_vn);
	}
	return graph;
}
void AddEdge(Graph *graph,int start, int goal)
{
	graph->matrix[start][goal] = 1;
	graph->matrix[goal][start] = 1;
}
void DeleteGraph(Graph *graph)
{
	for(int i=0; i<graph->vn; i++)
	{
		free(graph->matrix[i]);
	}
	free(graph->matrix);
	free(graph);
}
void ViewNeighbors(Graph *graph)
{
	for(int i=0; i<graph->vn; i++)
	{
		printf("\nRow %d : ",i);
		ViewNeighbor(graph,i);
	}
}
void ViewNeighbor(Graph *graph, int row)
{
	for(int i=0; i<graph->vn; i++)
	{
		if(graph->matrix[row][i])	printf("%2d ",i);
	}
}
//http://ehpub.co.kr/%ec%95%8c%ea%b3%a0%eb%a6%ac%ec%a6%98-c%ec%96%b8%ec%96%b4-5-1-1-%ec%9d%b8%ec%a0%91-%ed%96%89%eb%a0%ac%eb%a1%9c-%eb%b0%a9%ed%96%a5%ec%84%b1-%ec%97%86%eb%8a%94-%ea%b7%b8%eb%9e%98%ed%94%84-%ec%86%8c/