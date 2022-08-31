#define MAXSIZE 20
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct arcNode		//边链表
{
	int vex_num;
	int weight;
	arcNode* next;
}arcNode;

typedef struct vexNode		//顶点表数据类型
{
	int in = 0;		//入度域
	char vex;
	arcNode* First;
}vexNode;

typedef struct ALGraph		//邻接表数据类型
{
	vexNode List[MAXSIZE];
	int vexNum;
	int	arcsNum;
}ALGraph;

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

int ToologicalSort(ALGraph *GL)
{
	arcNode* e;
	int i, k;
	int count = 0;

	int* stack = (int *) malloc (sizeof(int) * GL->vexNum);
	int top = 0;
	int getTop;
	
	for (int i = 0; i < GL->vexNum; i++)	
		if (GL->List[i].in == 0)		
			stack[++top] = i;
	while (top != 0)
	{
		getTop = stack[top--];
		printf("%d -> ", GL->List[getTop].vex);
		count++;
		for (e = GL->List[getTop].First; e; e = e->next)
		{
			k = e->vex_num;
			if (GL->List[k].in != 0)
			{
				GL->List[k].in--;
				stack[++top];
			}
		}
	}
	if (count < GL->vexNum)
		return 0;
	else
		return 1;
}

int main(int argc, char* argv[])
{
	ALGraph* GL = CreateALGraph();
	printALGraph(GL);
	return 0;
}


