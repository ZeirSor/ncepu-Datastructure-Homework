//120211080526 张烁 20220518
/*
*	题目2. 带权有向图（联通或者不联通都要支持）
*	采用邻接表进行存储，图中顶点的类型为字符串，完成以下操作：
*		1. 创建图的邻接矩阵
*		2. 输出图的邻接表
*		3. 从指定的源点出发进行深度优先遍历
*		4. 从指定的源点出发进行广度优先遍历
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

typedef struct Graph	//邻接矩阵
{
	char vexs[MAXSIZE];
	int arcs[MAXSIZE][MAXSIZE];
	int vexNum, arcNum;
}Graph;	

//邻接表存储代码
typedef struct arcNode		//边链表
{
	int vex_num;
	int weight;
	arcNode* next;
}arcNode;

typedef struct vexNode		//顶点表数据类型
{
	char vex;
	arcNode* First;
}vexNode;

typedef struct ALGraph		//邻接表数据类型
{
	vexNode List[MAXSIZE];
	int vexNum;
	int	arcsNum;
}ALGraph;		

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
	scanf("%d %d", &G->vexNum, &G->arcNum);
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

	printf("请依次输入弧头序号、弧尾序号、权值：\n");
	int start, end, w;
	for (int k = 0; k < G->arcNum; k++)
	{
		scanf("%d%d%d", &start, &end, &w);
		G->arcs[start][end] = w;
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

ALGraph* CreateALGraph()
{
	ALGraph* G = (ALGraph*)malloc(sizeof(ALGraph));
	printf("请输入顶点数和边数：");
	scanf("%d %d", &G->vexNum, &G->arcsNum);
	
	printf("请依次输入各顶点的值：\n");
	for (int v = 0; v < G->vexNum; v++)
	{
		getchar();
		scanf("%c", &G->List[v].vex);
		G->List[v].First = NULL;
	}

	printf("请依次输入弧头序号、弧尾序号、权值：\n");
	int start, end, w;
	for (int k = 0; k < G->arcsNum; k++)
	{
		scanf("%d%d%d", &start, &end, &w);
		arcNode* s = (arcNode*)malloc(sizeof(arcNode));
		s->vex_num = end;
		s->weight = w;
		s->next = G->List[start].First;
		G->List[start].First = s;
	}
	return G;
}

void printALGraph(ALGraph* LG)
{
	printf("\n图的邻接表为：\n");
	for (int i = 0; i < LG->vexNum; i++)
	{
		printf("\t____\n");
		printf("\t%c |-->", LG->List[i].vex);
		arcNode* s = LG->List[i].First;
		while (s)
		{
			arcNode* p = s->next;
			printf("%c ", LG->List[s->vex_num].vex);
			if (p)
				printf("-->");
			s = s->next;
		}
		printf("\n");
		printf("\t￣￣\n");
	}
}

void DFS_ALGraph(ALGraph* LG, int* visited, int index)
{
	printf("%c\t", LG->List[index].vex);
	visited[index] = 1;

	arcNode* p = LG->List[index].First;
	while (p)
	{
		if (visited[p->vex_num] == 0)
			DFS_ALGraph(LG, visited, p->vex_num);
		p = p->next;
	}
}

void BFS_ALGraph(ALGraph* LG, int* visited, int index)
{
	Queue* Q = initQueue();
	printf("%c\t", LG->List[index].vex);
	visited[index] = 1;
	enQueue(Q, index);
	while (!isEmpty(Q))
	{
		int i = deQueue(Q);
		arcNode* p = LG->List[index].First;
		while (p)
		{
			if (visited[p->vex_num] == 0)
			{
				printf("%c\t", LG->List[p->vex_num].vex);
				visited[p->vex_num] = 1;
				enQueue(Q, p->vex_num);
			}
			p = p->next;
		}
	}
}

int main()
{
	printf("——邻接矩阵\n");
	Graph* G = (Graph*)malloc(sizeof(Graph));
	CreateGraph(G);		//创建图的邻接矩阵
	printMGraph(G);		//输出图的邻接矩阵
	
	printf("——邻接表\n");
	ALGraph* LG = CreateALGraph();	//创建图的邻接表
	printALGraph(LG);				//输出图的邻接表

	printf("DFS——请输入遍历的源点：");		//从指定的源点出发进行深度优先遍历
	int index;
	scanf("%d", &index);
	int* visited = (int*)malloc(sizeof(int) * G->vexNum);
	for (int i = 0; i < G->vexNum; i++)
	{
		visited[i] = 0;
	}
	printf("深度优先遍历结果为：\n");
	DFS_ALGraph(LG, visited, index);
	for (int i = 0; i < G->vexNum; i++)
	{
		if (visited[i] == 0)
			DFS_ALGraph(LG, visited, i);
	}
	printf("\n\n");

	printf("BFS——请输入遍历的源点：");		//从指定的源点出发进行广度优先遍历
	scanf("%d", &index);
	for (int i = 0; i < G->vexNum; i++)
	{
		visited[i] = 0;
	}
	printf("广度优先遍历结果为：\n");
	BFS_ALGraph(LG, visited, index);
	for (int i = 0; i < G->vexNum; i++)
	{
		if (visited[i] == 0)
			BFS_ALGraph(LG, visited, i);
	}
	printf("\n\n");

	return 0;
}