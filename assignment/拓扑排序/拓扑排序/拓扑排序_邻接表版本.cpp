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
	int in;		//入度域
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

	for (int i = 0; i < G->vexNum; i++)
	{
		G->List[i].in = 0;
	}

	printf("请依次输入弧头序号、弧尾序号：\n");
	int start, end;
	for (int k = 0; k < G->arcsNum; k++)
	{
		scanf("%d%d", &start, &end);
		arcNode* s = (arcNode*)malloc(sizeof(arcNode));
		s->vex_num = end;
		s->next = G->List[start].First;
		G->List[start].First = s;
		G->List[end].in++;
	}
	return G;
}

void printALGraph(ALGraph* LG)
{
	printf("\n图的邻接表为：\n");
	printf("\tin  vex\n");
	for (int i = 0; i < LG->vexNum; i++)
	{
		printf("\t________\n");
		printf("\t %d | V%d |-->", LG->List[i].in, (int)(LG->List[i].vex - 'a'));
		arcNode* s = LG->List[i].First;
		while (s)
		{
			arcNode* p = s->next;
			printf("V%d ", (int)(LG->List[s->vex_num].vex - 'a'));
			if (p)
				printf("-->");
			s = s->next;
		}
		printf("\n");
		printf("\t￣￣￣￣\n");
	}
}

int ToologicalSort(ALGraph* GL)
{
	printf("拓扑序列为：\n\n\t");

	int count = 0;		//记录已经输出的顶点数量

	int* stack = (int*)malloc(sizeof(int) * GL->vexNum);	//顺序栈
	int top = -1;		//规定为-1,方便后续操作
	int getTop;			//取栈顶值
	//栈里的值为顶点对应的序号

	for (int i = 0; i < GL->vexNum; i++)
		if (GL->List[i].in == 0)		//将入度为0的顶点入栈
			stack[++top] = i;			//top记得++

	arcNode* e;			//用来遍历顶点对应的边表
	int flag = 0;		//控制"->"的输出数量
	while (top != -1)	//栈非空
	{
		getTop = stack[top--];		//取栈顶值并出栈
		printf("V%d", (int)(GL->List[getTop].vex - 'a') + 1);	//输出序列
		if (flag != GL->vexNum - 1)		//n个顶点应该有n-1个"->"
		{
			printf(" -> ");
			flag++;
		}
		count++;	//已输出顶点数++

		for (e = GL->List[getTop].First; e; e = e->next)	//遍历边表
		{
			int k = e->vex_num;		//k记录当前顶点序号
			GL->List[k].in--;		//由于上个顶点以删除,故入度-1
			if (GL->List[k].in == 0)	//将入度为0的顶点入栈
				stack[++top] = k;
		}
	}
	printf("\n");

	if (count < GL->vexNum)		//输出顶点数量小于总顶点数说明存在环路
	{
		printf("\t有环！\n");
		return 0;
	}
	else
		return 1;
}

int main(int argc, char* argv[])
{
	ALGraph* GL = CreateALGraph();
	printALGraph(GL);
	ToologicalSort(GL);
	return 0;
}