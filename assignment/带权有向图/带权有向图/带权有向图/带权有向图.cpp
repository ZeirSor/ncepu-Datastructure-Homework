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
#include <Windows.h>
#include <conio.h>

#define MAXSIZE 20
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

void CreateALGraph(ALGraph *G)
{
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
}

void printALGraph(ALGraph* GL)
{
	printf("\n图的邻接表为：\n");
	for (int i = 0; i < GL->vexNum; i++)
	{
		printf("\t____\n");
		printf("\t%c |-->", GL->List[i].vex);
		arcNode* s = GL->List[i].First;
		while (s)
		{
			arcNode* p = s->next;
			printf("%c ", GL->List[s->vex_num].vex);
			if (p)
				printf("-->");
			s = s->next;
		}
		printf("\n");
		printf("\t￣￣\n");
	}
}

void DFS_ALGraph(ALGraph* GL, int* visited, int index)
{
	printf("%c\t", GL->List[index].vex);
	visited[index] = 1;

	arcNode* p = GL->List[index].First;
	while (p)
	{
		if (visited[p->vex_num] == 0)
			DFS_ALGraph(GL, visited, p->vex_num);
		p = p->next;
	}
}

void DFS_PathExist(ALGraph* GL, int* visited, int index)
{
	visited[index] = 1;
	arcNode* p = GL->List[index].First;
	while (p)
	{
		if (visited[p->vex_num] == 0)
			DFS_PathExist(GL, visited, p->vex_num);
		p = p->next;
	}
}


void BFS_ALGraph(ALGraph* GL, int* visited, int index)
{
	Queue* Q = initQueue();
	printf("%c\t", GL->List[index].vex);
	visited[index] = 1;
	enQueue(Q, index);
	while (!isEmpty(Q))
	{
		int i = deQueue(Q);
		arcNode* p = GL->List[index].First;
		while (p)
		{
			if (visited[p->vex_num] == 0)
			{
				printf("%c\t", GL->List[p->vex_num].vex);
				visited[p->vex_num] = 1;
				enQueue(Q, p->vex_num);
			}
			p = p->next;
		}
	}
}

int main()
{
	Graph* G = (Graph*)malloc(sizeof(Graph));
	ALGraph* GL = (ALGraph*)malloc(sizeof(ALGraph));
	int* visited = (int*)malloc(sizeof(int) * MAXSIZE);
	int index;

	char fun;
	while (1)
	{
		printf("\n\n");
		printf("\t\t\t************************************************************\n");
		printf("\t\t\t*************************** 菜单 ***************************\n");
		printf("\t\t\t	| 1 |	创建并输出邻接矩阵\n");
		printf("\t\t\t	| 2 |	创建并输出邻接表\n");
		printf("\t\t\t	| 3 |	从指定的源点出发进行深度优先遍历\n");
		printf("\t\t\t	| 4 |	从指定的源点出发进行广度优先遍历\n");
		printf("\t\t\t	| 5 |	判断两点之间是否存在路径\n");
		printf("\t\t\t	| 0 |	退出程序\n");
		printf("\t\t\t************************************************************\n");
		printf("\t\t\t************************************************************\n");
		fun = _getch();
		switch ((int)(fun - '0'))
		{
			case 0:
				return 0;
			case 1:
				system("cls");
				printf("——邻接矩阵\n");
				CreateGraph(G);		//创建图的邻接矩阵
				printMGraph(G);		//输出图的邻接矩阵
				break;
			case 2:
				system("cls");
				printf("——邻接表\n");
				CreateALGraph(GL);	//创建图的邻接表
				printALGraph(GL);	//输出图的邻接表
				break;
			case 3:
				system("cls");
				printf("DFS——请输入遍历的源点：");		//从指定的源点出发进行深度优先遍历
				scanf("%d", &index);
				for (int i = 0; i < GL->vexNum; i++)
					visited[i] = 0;
				printf("深度优先遍历结果为：\n");
				DFS_ALGraph(GL, visited, index);
				for (int i = 0; i < GL->vexNum; i++)
				{
					if (visited[i] == 0)
						DFS_ALGraph(GL, visited, i);
				}
				printf("\n\n");
				break;
			case 4:
				system("cls");
				printf("BFS——请输入遍历的源点：");		//从指定的源点出发进行广度优先遍历
				scanf("%d", &index);
				for (int i = 0; i < GL->vexNum; i++)
				{
					visited[i] = 0;
				}
				printf("广度优先遍历结果为：\n");	
				BFS_ALGraph(GL, visited, index);
				for (int i = 0; i < GL->vexNum; i++)
				{
					if (visited[i] == 0)
						BFS_ALGraph(GL, visited, i);
				}
				printf("\n\n");
				break;
			case 5:
				system("cls");
				printf("IfPathExist——请输入两个顶点，判断他们之间是否存在路径：");		//判断两点之间是否存在路径
				int head, tail;
				scanf("%d%d", &head, &tail);
				for (int i = 0; i < GL->vexNum; i++)
					visited[i] = 0;
				DFS_PathExist(GL, visited, head);
				if (visited[tail] == 1)
					printf("V%d和V%d之间存在路径！\n", head, tail);
				else printf("不存在！\n");
				break;
			default:
				system("cls");
				printf("输入错误！\n");
			break;
		}
		printf("请按任意键继续！");
		getchar();
		getchar();
		system("cls");
	}

	return 0;
}


//printf("\t\t\t************************************************************\n");
//printf("\t\t\t*************************** 菜单 ***************************\n");
//printf("\t\t\t***	| 1 |	创建并输出邻接矩阵						   ***\n");
//printf("\t\t\t***	| 2 |	创建并输出邻接表						   ***\n");
//printf("\t\t\t***	| 3 |	从指定的源点出发进行深度优先遍历		   ***\n");
//printf("\t\t\t***	| 4 |	从指定的源点出发进行广度优先遍历		   ***\n");
//printf("\t\t\t***	| 5 |	判断两点之间是否存在路径				   ***\n");
//printf("\t\t\t***	| 0 |	退出程序								   ***\n");
//printf("\t\t\t************************************************************\n");
//printf("\t\t\t************************************************************\n");
//
//
//
//
//
//
//
//
//\t\t\t************************************************************\n
//\t\t\t************************************************************\n
//
//
//printf("****************************************************");

//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <windows.h>
//#include <conio.h>
//int main(int argc, char* argv[])
//{
//
//	return 0;
//}



