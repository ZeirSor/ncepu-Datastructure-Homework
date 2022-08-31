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
#define MAX 666

typedef struct Graph
{
	char* vexs;
	int** arcs;
	int vexNum, arcNum;
}Graph;

Graph* initGraph(int vexNum)
{
	Graph* G = (Graph*)malloc(sizeof(Graph));
	G->vexs = (char*)malloc(sizeof(char) * vexNum);
	G->arcs = (int**)malloc(sizeof(int*) * vexNum);
	for (int i = 0; i < vexNum; i++)
	{
		G->arcs[i] = (int*)malloc(sizeof(int) * vexNum);
	}
	G->vexNum = vexNum;
	G->arcNum = 0;
	return G;
}

void CreateGraph(Graph* G,const char* vex, int* arcs)
{
	for (int i = 0; i < G->vexNum; i++)
	{
		G->vexs[i] = vex[i];
		for (int j = 0; j < G->vexNum; j++)
		{
			G->arcs[i][j] = *(arcs + i*G->vexNum + j);
			if (G->arcs[i][j] > 0 && G->arcs[i][j] != MAX)
				G->arcNum++;
		}
		G->arcNum /= 2;
	}
}

int main()
{
	Graph* G = initGraph(8);
	int arcs[MAXSIZE][MAXSIZE] = {
		MAX,4,3,MAX,MAX,MAX,MAX,MAX,
		4,MAX,5,5,9,MAX,MAX,MAX,
		MAX,5,5,MAX,7,6,5,4,
		MAX,9,MAX,7,MAX,3,MAX,MAX,
		MAX,MAX,MAX,6,3,MAX,2,MAX,
		MAX,MAX,MAX,5,MAX,2,MAX,6,
		MAX,MAX,5,4,MAX,MAX,6,MAX
	};
	CreateGraph(G, "abcdefgh", (int*)arcs);		//创建图的邻接矩阵
	for (int i = 0; i < G->vexNum; i++)
	{
		printf("")
	}
	
	for (int i = 0; i < G->vexNum; i++)
	{
		for (int j = 0; j < G->vexNum; j++)
		{
			printf("%-5d", G->arcs[i][j]);
		}
		printf("\n\n");
	}

	return 0;
}
