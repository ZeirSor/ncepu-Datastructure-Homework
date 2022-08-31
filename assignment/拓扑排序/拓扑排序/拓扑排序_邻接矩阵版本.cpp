#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include<vector>
#include<iostream>

#define MAXSIZE 20
#define MAX 52725

typedef struct Graph
{
	char vexs[MAXSIZE];
	int arcs[MAXSIZE][MAXSIZE];
	int vexNum, arcNum;
}Graph;

void CreateGraph(Graph* G)
{
	printf("请输入顶点数和边数：");
	scanf("%d %d", &G->vexNum, &G->arcNum);

	for (int i = 0; i < G->vexNum; i++)
		for (int j = 0; j < G->vexNum; j++)		
			G->arcs[i][j] = MAX;

	printf("请依次输入弧头序号、弧尾序号、权值：");
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
			printf("\t%d", G->arcs[i][j]);
		}
		printf("\n\n");
	}
}

void DFS(Graph* G, int* visited, int index)
{
	printf("%d\t", index + 1);
	visited[index] = 1;
	for (int i = 0; i < G->vexNum; i++)
	{
		if (G->arcs[index][i] > 0 && G->arcs[index][i] != MAX && visited[i] != 1)
		{
			DFS(G, visited, i);
		}
	}
}

void DFS_Extended(Graph *G, int *visited)
{
	DFS(G, visited, 0);
	for (int i = 0; i < G->vexNum; i++)
	{
		if (visited[i] != 1)
		{
			DFS(G, visited, i);
		}
	}
}

typedef struct Stack
{
	int data;
	struct Stack* next;
}Stack, * StackPtr;

Stack* initStack()
{
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->data = 0;
	stack->next = NULL;
	return stack;
}

int isEmpty(Stack* stack)
{
	if (stack->next == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void push(Stack* stack, int data)
{
	Stack* s = (Stack*)malloc(sizeof(Stack));
	s->data = data;
	s->next = stack->next;
	stack->next = s;
}

int pop(Stack* stack)
{
	if (!isEmpty(stack))
	{
		Stack* s = stack->next;
		stack->next = s->next;
		return s->data;
	}
	else
	{
		return -1;
	}
}

int* FindInDegrees(Graph* G)
{
	int* inDegrees = (int*)malloc(sizeof(int) * G->vexNum);
	for (int i = 0; i < G->vexNum; i++)
	{
		inDegrees[i] = 0;
	}
	for (int i = 0; i < G->vexNum; i++)
	{
		for (int j = 0; j < G->vexNum; j++)
		{
			if ( G->arcs[i][j] > 0 && G->arcs[i][j] != MAX)
			{
				inDegrees[j]++;
			}
		}
	}
	return inDegrees;
}

void ToologicalSort(Graph* G, int *inDegrees, int *tp)
{
	int index = 0;
	Stack* stack = initStack();
	for (int i = 0; i < G->vexNum; i++)
	{
		if (inDegrees[i] == 0)
		{
			push(stack, i); 
			inDegrees[i]--;		//已经入栈准备输出，置为-1，避免再次入栈
		}
	}
	while (!isEmpty(stack))
	{
		int top = pop(stack);
		tp[index++] = top;
		printf("%d\t", top + 1);
		for (int k = 0; k < G->vexNum; k++)
		{
			if (G->arcs[top][k] > 0 && G->arcs[top][k] != MAX)
			{
				inDegrees[k]--;
			}
		}
		for (int m = 0; m < G->vexNum; m++)
		{
			if (inDegrees[m] == 0)
			{
				push(stack, m);
				inDegrees[m]--;
			}
		}
	}
}

void ToologicalSort2(Graph* G, int* inDegrees)
{
	Stack* stack = initStack();
	for (int i = 0; i < G->vexNum; i++)	
		if (inDegrees[i] == 0)		
			push(stack, i);		
	
	while (!isEmpty(stack))
	{
		int top = pop(stack);
		printf("%d\t", top + 1);
		for (int k = 0; k < G->vexNum; k++)
		{
			if (G->arcs[top][k] > 0 && G->arcs[top][k] != MAX)
			{
				inDegrees[k]--;
				if (inDegrees[k] == 0)
					push(stack, k);
			}
		}						
	}
}

int getIndex(int* tp, int i, Graph *G)
{
	int index;
	for (int j = 0; j < G->vexNum; j++)
	{
		if (tp[j] == i)
		{
			index = j;
			break;
		}
	}
	return index;
}

void CriticalPath(Graph* G, int* tp)
{
	int* early = (int*)malloc(sizeof(int) * G->vexNum);
	int* late = (int*)malloc(sizeof(int) * G->vexNum);
	for (int i = 0; i < G->vexNum; i++)
		early[i] = late[i] = 0;

	for (int i = 1; i < G->vexNum; i++)
	{
		int index = getIndex(tp, i, G);
		int max = 0;
		for (int j = 0; j < index; j++)
		{
			if (G->arcs[tp[j]][i] > 0 && G->arcs[tp[j]][i] != MAX)
			{
				if (G->arcs[tp[j]][i] + early[tp[j]] > max)
				{
					max = G->arcs[tp[j]][i] + early[tp[j]];
				}
			}
		}
		early[i] = max;
	}

	printf("early[]:\n\t");
	for (int i = 0; i < G->vexNum; i++)
		printf("\t%d", early[i]);

	late[(G->vexNum) - 1] = early[(G->vexNum) - 1];
	for (int i = G->vexNum - 2; i >= 0; i--)
	{
		int min = late[(G->vexNum) - 1];
		int index2 = getIndex(tp, i, G);
		for (int j = (G->vexNum) - 1; j  > index2; j--)
		{
			if (G->arcs[i][tp[j]] > 0 && G->arcs[i][tp[j]] != MAX)
			{
				if (late[tp[j]] - G->arcs[i][tp[j]] < min)
				{
					min = late[tp[j]] - G->arcs[i][tp[j]];
				}
			}
		}
		late[i] = min;
	}

	printf("\nlate[]:\n\t");
	for (int i = 0; i < G->vexNum; i++)
		printf("\t%d", late[i]);

	printf("\n关键路径：\n\t");
	for (int i = 0; i < G->vexNum; i++) {
		int index_c = getIndex(tp, i, G);
		for (int j = 0; j < index_c; j++) {
			if (G->arcs[tp[j]][i] > 0 && G->arcs[tp[j]][i] != MAX) {
				if (late[i] - G->arcs[tp[j]][i] == early[tp[j]]) {
					printf("\t%d -(%d)-> %d", tp[j], G->arcs[tp[j]][i], i);
				}
			}
		}
	}
	printf("\n" );
}

     
int main(int argc, char* argv[])
{
	Graph* G = (Graph*)malloc(sizeof(Graph));
	CreateGraph(G);
	printf("序号:\t");
	for (int i = 0; i < G->vexNum; i++) {
		printf("\t%d", i);
	}
	printf("\n");
	printMGraph(G);
	int* visited = (int*)malloc(sizeof(int) * G->vexNum);
	for (int i = 0; i < G->vexNum; i++)
		visited[i] = 0;
	printf("DFS:\t\t");
	DFS_Extended(G, visited);
	printf("\n");
	
	int* tp = (int*)malloc(sizeof(int) * G->vexNum);
	int* inDegrees = FindInDegrees(G);
	printf("\ninDegrees[]:\n\t");
	for (int i = 0; i < G->vexNum; i++)
	{
		printf("\t%d", inDegrees[i]);
	}
	printf("\n\nTopological Order:\n\t\t");
	ToologicalSort(G, inDegrees, tp);
	
	printf("\ntp[]:\n\t");
	for (int i = 0; i < G->vexNum; i++)
		printf("\t%d", tp[i]+1);
	printf("\n");
	
	CriticalPath(G, tp);

	//int* inDegrees2 = FindInDegrees(G);
	//printf("\ninDegrees2[]:\n\t");
	//for (int i = 0; i < G->vexNum; i++)
	//{
	//	printf("\t%d", inDegrees2[i]);
	//}
	//printf("\n\nTopological Order 2:\n\t\t");
	//ToologicalSort(G, inDegrees2);
	return 0;
}

//
//int main()
//{
//	using std::vector;
//	vector<char> v;
//	char s;
//	for (auto i = v.begin(); i < v.end(); i++) 		
//	{
//		v.push_back(s);
//	}
//
//}

// IMPUT
// ******************
// ******************
//		10 13	   **
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
// 
// OUTPUT
//*********************************************************************************************************************
//*********************************************************************************************************************
//																												    ***
// 																												    ***
//		序号:           0       1       2       3       4       5       6       7       8       9				    *** 
//		图的邻接矩阵为：																						    ***
//						52725   3       4       52725   52725   52725   52725   52725   52725   52725			    ***
//																												    ***
//						52725   52725   52725   5       6       52725   52725   52725   52725   52725			    ***
//																												    ***
//						52725   52725   52725   8       52725   7       52725   52725   52725   52725			    ***
//																												    ***
//						52725   52725   52725   52725   3       52725   52725   52725   52725   52725			    ***
//																												    ***
//						52725   52725   52725   52725   52725   52725   9       4       52725   52725			    ***
//																												    ***
//						52725   52725   52725   52725   52725   52725   52725   6       52725   52725			    ***
//																												    ***
//						52725   52725   52725   52725   52725   52725   52725   52725   52725   2				    ***
//																												    ***
//						52725   52725   52725   52725   52725   52725   52725   52725   5       52725			    ***
//																												    ***
//						52725   52725   52725   52725   52725   52725   52725   52725   52725   3				    ***
//																												    ***
//						52725   52725   52725   52725   52725   52725   52725   52725   52725   52725			    ***
//																												    ***
//		DFS:            1       2       4       5       7       10      8       9       3       6				    ***
//																												    ***
//		inDegrees[] :																							    ***
//						0       1       1       2       2       1       1       2       1       2				    ***
//																												    ***
//		Topological Order :																						    ***
//						1       3       6       2       4       5       8       9       7       10				    ***
//		tp[] :																									    ***
//						1       3       6       2       4       5       8       9       7       10				    ***
//		early[] :																								    ***
//						0       3       4       12      15      11      24      19      24      27				    ***
//		late[] :																								    ***
//						0       7       4       12      15      13      25      19      24      27				    ***
//		关键路径：																								    ***
//						0 -(4)-> 2      2 -(8)-> 3      3 -(3)-> 4      4 -(4)-> 7      7 -(5)-> 8      8 -(3)-> 9  ***
//																													***
//*********************************************************************************************************************
//*********************************************************************************************************************