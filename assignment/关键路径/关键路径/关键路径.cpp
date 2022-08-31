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

	printf("请依次输入弧头序号、弧尾序号以及弧的权值：\n");
	int start, end, w;
	for (int k = 0; k < G->arcsNum; k++)
	{
		scanf("%d%d%d", &start, &end, &w);
		arcNode* s = (arcNode*)malloc(sizeof(arcNode));
		s->vex_num = end;
		s->weight = w;
		s->next = G->List[start].First;
		G->List[start].First = s;
		G->List[end].in++;
	}
	return G;
}

void printALGraph(ALGraph* LG)
{
	printf("\n图的邻接表为：\n");
	printf("\tin | vex     vex   | weight\n");
	for (int i = 0; i < LG->vexNum; i++)
	{
		printf("\t________\n");
		printf("\t %d | V%d |-->", LG->List[i].in, (int)(LG->List[i].vex - 'a'));
		arcNode* s = LG->List[i].First;
		while (s)
		{
			arcNode* p = s->next;
			printf("  V%d   |  %d    ", (int)(LG->List[s->vex_num].vex - 'a'),s->weight);
			if (p)
				printf("-->");
			s = s->next;
		}
		printf("\n");
		printf("\t￣￣￣￣\n");
	}
}


int* VE;	//记录时间最早发生时间的数组
int* VL;	//记录时间最晚发生时间的数组
int* stack_TpOrder;//存储拓扑序列的栈
int top_TpOrder;

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

//******************************************************************
	top_TpOrder = -1;										//初始化
	VE = (int*)malloc(sizeof(int) * GL->vexNum);			//初始化
	for (int i = 0; i < GL->vexNum; i++)				 //初始化为0
		VE[i] = 0;
	stack_TpOrder = (int*)malloc(sizeof(int) * GL->vexNum);	//初始化
//******************************************************************

	arcNode* e;			//用来遍历顶点对应的边表
	int flag = 0;		//控制"->"的输出数量
	while (top != -1)	//栈非空
	{
		getTop = stack[top--];		//取栈顶值并出栈
		printf("V%d", (int)(GL->List[getTop].vex - 'a'));	//输出序列
		if (flag != GL->vexNum - 1)		//n个顶点应该有n-1个"->"
		{
			printf(" -> ");
			flag++;
		}
		count++;	//已输出顶点数++

//******************************************************************************
		stack_TpOrder[++top_TpOrder] = getTop;	//将弹出的顶点序号压入拓扑序列栈
//******************************************************************************

		for (e = GL->List[getTop].First; e; e = e->next)	//遍历边表
		{
			int k = e->vex_num;		//k记录当前顶点序号
			GL->List[k].in--;		//由于上个顶点以删除,故入度-1
			if (GL->List[k].in == 0)	//将入度为0的顶点入栈
				stack[++top] = k;

//***********************************************************************		
			if (VE[getTop] + e->weight > VE[k])		// 求各顶点时间的					
				VE[k] = VE[getTop] + e->weight;		//最早发生时间VE的值
//***********************************************************************

		}
	}
	printf("\n");
	printf("\n");

	printf("最早发生时间的数组VE：\n\n");
	printf("\t序号\t");
	for (int i = 0; i < GL->vexNum; i++)
		printf("%d\t", i);
	printf("\n\n\t\t");
	for (int i = 0; i < GL->vexNum; i++)
		printf("%d\t", VE[i]);
	printf("\n");

	if (count < GL->vexNum)		//输出顶点数量小于总顶点数说明存在环路
	{
		printf("\t有环！\n");
		return 0;
	}
	else
		return 1;
}

void CriticalPath(ALGraph* GL)
{
	int ete, lte;		//声明活动最早发生时间和最晚发生时间的变量
	int getTop;			//取栈顶值
	ToologicalSort(GL);	//先进行拓扑排序，保存拓扑序列栈，计算各顶点最早发生时间VE数组的值
	
	VL = (int*)malloc(sizeof(int) * GL->vexNum);
	for (int i = 0; i < GL->vexNum; i++)
		VL[i] = VE[GL->vexNum - 1];

	while (top_TpOrder != -1)
	{
		getTop = stack_TpOrder[top_TpOrder--];
		for (arcNode* e = GL->List[getTop].First ; e; e = e->next)
		{
			int k = e->vex_num;
			if (VL[k] - e->weight < VL[getTop])
				VL[getTop] = VL[k] - e->weight;
		}
	}

	printf("最晚发生时间的数组VL：\n\n");
	printf("\t序号\t");
	for (int i = 0; i < GL->vexNum; i++)
		printf("%d\t", i);
	printf("\n\n\t\t");
	for (int i = 0; i < GL->vexNum; i++)
		printf("%d\t", VL[i]);
	printf("\n");

	printf("\n关键路径为：\n\t");
	for (int j = 0; j < GL->vexNum; j++)
	{
		for (arcNode* e = GL->List[j].First; e; e = e->next)
		{
			int k = e->vex_num;
			ete = VE[j];
			lte = VL[k] - e->weight;
			if (ete == lte)
			{
				if (j == 0)
					printf("V%d ", (int)(GL->List[j].vex - 'a'));
				printf("-->");
				printf(" V%d ", (int)(GL->List[k].vex - 'a'));
			}
		}
	}
	printf("\n");
}


int main(int argc, char* argv[])
{
	ALGraph* GL = CreateALGraph();
	printALGraph(GL);
	CriticalPath(GL);
	return 0;
}

// IMPUT
// ******************
// ******************
//		10 13	   **
//		a		   **
//		b		   **
//		c		   **
//		d		   **
//		e		   **
//		f		   **
//		g		   **
//		h		   **
//		i		   **
//		j		   **
//		0 2 4	   **
//		0 1 3	   **
//		1 4 6	   **
//		1 3 5	   **
//		2 5 7	   **
//		2 3 8	   **
//		3 4 3	   **
//		4 7 4	   **
//		4 6 9	   **
//		5 7 6	   **
//		6 9 2	   **
//		7 8 5	   **
//		8 9 3	   **
//*******************				
// 
//	OUTPUT
//***********************************************************************************************
//***********************************************************************************************
//		图的邻接表为：																		  ***
//		in | vex     vex | weight															  ***
//		________																			  ***
//		0 | V0 | -- > V1 | 3    -- > V2 | 4													  ***
//		￣￣￣￣																			  ***
//		________																			  ***
//		1 | V1 | -- > V3 | 5    -- > V4 | 6													  ***
//		￣￣￣￣																			  ***
//		________																			  ***
//		1 | V2 | -- > V3 | 8    -- > V5 | 7													  ***
//		￣￣￣￣																			  ***
//		________																			  ***
//		2 | V3 | -- > V4 | 3																  ***
//		￣￣￣￣																			  ***
//		________																			  ***
//		2 | V4 | -- > V6 | 9    -- > V7 | 4													  ***
//		￣￣￣￣																			  ***
//		________																			  ***
//		1 | V5 | -- > V7 | 6																  ***
//		￣￣￣￣																			  ***
//		________																			  ***
//		1 | V6 | -- > V9 | 2																  ***
//		￣￣￣￣																			  ***
//		________																			  ***
//		2 | V7 | -- > V8 | 5																  ***
//		￣￣￣￣																			  ***
//		________																			  ***
//		1 | V8 | -- > V9 | 3																  ***
//		￣￣￣￣																			  ***
//		________																			  ***
//		2 | V9 | -- >																		  ***
//		￣￣￣￣																			  ***
//		拓扑序列为：																		  ***
//																							  ***
//					V1->V3->V6->V2->V4->V5->V8->V9->V7->V10						        	  ***
//																							  ***
//		最早发生时间的数组VE：																  ***
//																							  ***
//		序号    0       1       2       3       4       5       6       7       8       9	  ***
//																							  ***
//				0       3       4       12      15      11      24      19      24      27	  ***
//		最晚发生时间的数组VL：																  ***
//																							  ***
//		序号    0       1       2       3       4       5       6       7       8       9	  ***
//																							  ***
//				0       7       4       12      15      13      25      19      24      27	  ***
//																							  ***
//		关键路径为：																		  ***
//					V0-- > V2-- > V3-- > V4-- > V7-- > V8-- > V9							  ***
//																							  ***
//***********************************************************************************************
//***********************************************************************************************