//120211080526 张烁 20220517
/*
*	题目1. 带权无向图（联通或者不联通都要支持）
*	采用邻接矩阵进行存储，图中顶点的类型为字符串，完成以下操作：
*		1. 创建图的邻接矩阵
*		2. 输出图的顶点和邻接矩阵
*		3. 从指定的源点出发进行深度优先遍历
*		4. 从指定的源点出发进行广度优先遍历
*		5. 基于PRIM算法构造图的最小生成树
*/
/*
*		测试样例
*                MAX 4 3 MAX MAX MAX MAX MAX
*                4 MAX 5 5 9 MAX MAX MAX
*                3 5 MAX 5 MAX MAX MAX 5
*                MAX 5 5 MAX 7 6 5 4
*                MAX 9 MAX 7 MAX 3 MAX MAX
*                MAX MAX MAX 6 3 MAX 2 MAX
*                MAX MAX MAX 5 MAX 2 MAX 6
*                MAX MAX 5 4 MAX MAX 6 MAX
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 8
#define MAX 527725

typedef struct Graph
{
	char vexs[MAXSIZE];
	int arcs[MAXSIZE][MAXSIZE];
	int vexNum, arcNum;
}Graph;

typedef struct Edge
{
	char vex;
	int weight;
}Edge;

typedef struct QNode
{
	int data;
	struct QNode* next;
}QNode;

typedef struct Queue
{
	QNode* front;
	QNode* rear;
}Queue;

Queue* initQueue()
{
	Queue* Q = (Queue*)malloc(sizeof(Queue));
	Q->front = Q->rear = (QNode*)malloc(sizeof(QNode));
	Q->front->next = NULL;
	return Q;
}

int isEmpty(Queue* Q)
{
	if (Q->front == Q->rear)
		return 1;
	else
		return 0;
}

void enQueue(Queue* Q, int data)
{
	QNode* p = (QNode*)malloc(sizeof(QNode));
	p->data = data;
	p->next = Q->rear->next;
	Q->rear->next = p;
	Q->rear = p;
}

int deQueue(Queue* Q)
{
	if (isEmpty(Q))
		return 0;
	QNode* p = Q->front->next;
	Q->front->next = p->next;
	if (Q->rear == p)
		Q->rear = Q->front;
	int i = p->data;
	free(p);
	return i;
}

void CreateGraph(Graph* G)
{
	printf("请输入顶点数和边数：");
	scanf("%d %d",&G->vexNum, &G->arcNum);
	printf("请依次输入各顶点的值：\n");
	for (int v = 0; v < G->vexNum; v++)
	{
		getchar();
		scanf("%c", &G->vexs[v]);
	}

	for (int i = 0; i < G->vexNum; i++)
	{
		for (int j = 0; j < G->vexNum; j++)
		{
			G->arcs[i][j] = MAX;
		}	
	}

	printf("请依次输入弧头序号、弧尾序号、权值：");
	int start, end, w;
	for (int k = 0; k < G->arcNum; k++)
	{
		scanf("%d%d%d", &start, &end, &w);
		G->arcs[start-1][end-1] = w;
		G->arcs[end - 1][start - 1] = w;
	}
}

void printMGraph(Graph* G)
{
	printf("图的邻接矩阵为：\n");			//输出图的邻接矩阵
	for (int i = 0; i < G->vexNum; i++)
	{
		for (int j = 0; j < G->vexNum; j++)
		{
			if (j == 0)
			{
				printf("\t");
			}
			printf("%-10d", G->arcs[i][j]);
		}
		printf("\n\n");
	}
}

void DFS(Graph* G, int* visited, int index)
{
	printf("%c\t", G->vexs[index]);
	visited[index] = 1;
	for (int i = 0; i < G->vexNum; i++)
	{
		if (G->arcs[index][i] > 0 && G->arcs[index][i] != MAX && visited[i] != 1)
		{
			DFS(G, visited, i);
		}
	}
}

void BFS(Graph* G, int* visited, int index)
{
	Queue *Q = initQueue();
	printf("%c\t", G->vexs[index]);
	visited[index] = 1;
	enQueue(Q, index);
	while (!isEmpty(Q))
	{
		int i = deQueue(Q);
		for (int j = 0; j < G->vexNum; j++)
		{
			if (G->arcs[i][j] > 0 && G->arcs[i][j] != MAX && visited[j] == 0)
			{
				printf("%c\t", G->vexs[j]);
				visited[j] = 1;
				enQueue(Q, j);
			}
		}
	}
}

Edge* initEdge(Graph* G, int index)
{
	Edge* edge = (Edge*)malloc(sizeof(Edge));
	for (int i = 0; i < G->vexNum; i++)
	{
		edge[i].vex = G->vexs[index];
		edge[i].weight = G->arcs[index][i];
	}
	return edge;
}

int getMinEdge(Graph* G, Edge* edge)
{
	int index;
	int min = MAX;
	for (int i = 0; i < G->vexNum; i++)
	{
		if (edge[i].weight != 0 && edge[i].weight < min)
		{
			min = edge[i].weight;
			index = i;
		}
	}
	return index;
}

int* Prim(Graph* G, int index)
{
	int min;
	int seleted[MAXSIZE] = { 0 };		//用于标记已选上的顶点，避免重复选出同一条边
	seleted[index] = 1;
	Edge* edge = initEdge(G, index);
	for (int i = 0; i < G->vexNum - 1; i++)
	{
		min = getMinEdge(G, edge);
		printf("\t%c --> %c\tweight = %d\n", edge[min].vex, G->vexs[min], edge[min].weight);
		edge[min].weight = 0;
		seleted[min] = 1;
		for (int j = 0; j < G->vexNum; j++) {
			if (G->arcs[min][j] < edge[j].weight && seleted[j] == 0) {
				edge[j].weight = G->arcs[min][j];
				edge[j].vex = G->vexs[min];
			}
		}
	}
	return seleted;
}

int main()
{
	Graph* G = (Graph*)malloc(sizeof(Graph));
	CreateGraph(G);							//创建图的邻接矩阵
	printf("图的所有顶点为：");			//输出图的顶点
	for (int i = 0; i < G->vexNum; i++)
	{
		printf("%c ",G->vexs[i]);
	}
	printf("\n\n");

	printMGraph(G);			//输出图的邻接矩阵

	printf("DFS——请输入遍历的源点：");
	int index;
	scanf("%d", &index);
	int* visited = (int*)malloc(sizeof(int) * G->vexNum);
	for (int i = 0; i < G->vexNum; i++)
	{
		visited[i] = 0;
	}
	printf("深度优先遍历结果为：\n");
	for (int i = 0; i < G->vexNum; i++)
	{
		if(visited[i] == 0 && i == 0)
			DFS(G, visited, index);
		else if(visited[i] == 0)
			DFS(G, visited, i);
	}
	printf("\n\n");

	printf("BFS——请输入遍历的源点：");
	scanf("%d", &index);
	for (int i = 0; i < G->vexNum; i++)
	{
		visited[i] = 0;
	}
	printf("广度优先遍历结果为：\n");
	for (int i = 0; i < G->vexNum; i++)
	{
		if (visited[i] == 0 && i == 0)
			BFS(G, visited, index);
		else if (visited[i] == 0)
			BFS(G, visited, i);
	}
	printf("\n\n");

	printf("请输入构造最小生成树源点：");
	int source;
	scanf("%d", &source);
	printf("由Prim算法构造最小生成树过程为：\n");
	visited = Prim(G, source);
	printf("\n\n");
	return 0;
}
